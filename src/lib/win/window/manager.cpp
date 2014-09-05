// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/window/manager.cpp                                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "win/window/manager.hpp"

// includes, system

//#include <>

// includes, project

//#include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

  win::window::manager::display_list_type
  enumerate_displays()
  {
    TRACE("win::window::<unnamed>::enumerate_displays");

    using namespace win::window;

    manager::display_list_type result;
    DISPLAY_DEVICE             dd;

    memset(&dd, 0, sizeof(DISPLAY_DEVICE));

    dd.cb = sizeof(DISPLAY_DEVICE);

    unsigned const flags(0);
    unsigned       i(0);

    while (::EnumDisplayDevices(nullptr, i, &dd, flags)) {
      if (DISPLAY_DEVICE_ACTIVE & dd.StateFlags) {
        manager::display_devmode_pair_type ddev_pair(std::make_pair(dd,
                                                                    manager::devmode_list_type()));
        DEVMODE                            ddmode;

        ddmode.dmSize        = sizeof(DEVMODE);
        ddmode.dmDriverExtra = 0;

        // idx0: current
        if (::EnumDisplaySettingsEx(ddev_pair.first.DeviceName, ENUM_CURRENT_SETTINGS, &ddmode,
                                    flags)) {
          ddev_pair.second.push_back(ddmode);
        }

        unsigned const flags(0);
        unsigned       j(0);

        // idx1-n:supported
        while (::EnumDisplaySettingsEx(ddev_pair.first.DeviceName, j, &ddmode, flags)) {
          if (32 <= ddmode.dmBitsPerPel) {
            ddev_pair.second.push_back(ddmode);
          }

          ++j;
        }

        // idx:n+1: registry
        if (::EnumDisplaySettingsEx(ddev_pair.first.DeviceName, ENUM_REGISTRY_SETTINGS, &ddmode,
                                    flags)) {
          ddev_pair.second.push_back(ddmode);
        }
        // idx1-n:supported
        while (::EnumDisplaySettingsEx(ddev_pair.first.DeviceName, j, &ddmode, flags)) {
          if (32 <= ddmode.dmBitsPerPel) {
            ddev_pair.second.push_back(ddmode);
          }

          ++j;
        }

        // idx:n+1: registry
        if (::EnumDisplaySettingsEx(ddev_pair.first.DeviceName, ENUM_REGISTRY_SETTINGS, &ddmode,
                                    flags)) {
          ddev_pair.second.push_back(ddmode);
        }

        result.push_back(ddev_pair);
      }

      ++i;
    }

    return result;
  }

  BOOL CALLBACK
  enumerate_monitor_cb(HMONITOR hMon, HDC /* hdcMon */, LPRECT /* lprcMon */, LPARAM dwData)
  {
    TRACE("win::window::<unnamed>::enumerate_monitor_cb");

    MONITORINFOEX minfo;

    minfo.cbSize = sizeof(MONITORINFOEX);

    BOOL const result(::GetMonitorInfo(hMon, &minfo));

    if (result) {
      auto monitor_list(reinterpret_cast<win::window::manager::monitor_list_type*>(dwData));

      if (monitor_list) {
        monitor_list->push_back(minfo);
      }
    }

    return result;
  }

  win::window::manager::monitor_list_type
  enumerate_monitors()
  {
    TRACE("win::window::<unnamed>::enumerate_monitors");

    using namespace win::window;

    manager::monitor_list_type result;

    if (!::EnumDisplayMonitors(nullptr, nullptr, enumerate_monitor_cb,
                               reinterpret_cast<LPARAM>(&result)))
      result = manager::monitor_list_type();

    return result;
  }
  
} // namespace {

namespace win {

  namespace window {
    
    // variables, exported

    /* static */ manager::display_list_type manager::display_list_;
    /* static */ manager::monitor_list_type manager::monitor_list_;

    // XXX this is a clutch to keep 'manager::window_list_' around even in the presence of an
    // exception; otherwise it might be deconstructed before 'main' finishes
    /* static */ manager::window_list_type* manager::window_list_(new manager::window_list_type);
    
    // functions, exported

    /* static */ manager::display_list_type const&
    manager::display_list(bool a)
    {
      TRACE("win::window::manager::display_list");

      if (a || display_list_.empty()) {
        display_list_ = enumerate_displays();
      }

      return display_list_;
    }

    /* static */ manager::monitor_list_type const&
    manager::monitor_list(bool a)
    {
      TRACE("win::window::manager::monitor_list");

      if (a || monitor_list_.empty()) {
        monitor_list_ = enumerate_monitors();
      }

      return monitor_list_;
    }

    /* static */ unsigned
    manager::count()
    {
      TRACE_NEVER("win::window::manager::count");

      // XXX an alternative iff strict RAII idiom were used
      // return register_class::count();

      return unsigned(window_list_->size());
    }

    /* static */ bool
    manager::add(base* a)
    {
      TRACE("win::window::manager::add");

      bool const result(window_list_->insert(a).second);

#if defined(UKACHULLDCS_USE_TRACE)
      std::cout << support::trace::prefix() << "win::window::manager::add: "
                << "count: " << count()
                << std::endl;
#endif

      return result;
    }

    /* static */ bool
    manager::sub(base* a)
    {
      TRACE("win::window::manager::sub");

      bool result(false);
      auto found(std::find(window_list_->begin(), window_list_->end(), a));

      if (window_list_->end() != found) {
        window_list_->erase(found);

        result = true;
      }

#if defined(UKACHULLDCS_USE_TRACE)
      std::cout << support::trace::prefix() << "win::window::manager::sub: "
                << "count: " << count()
                << std::endl;
#endif

      return result;
    }

  } // namespace window {
  
} // namespace win {
