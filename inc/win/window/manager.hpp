// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/window/manager.hpp                                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_WIN_WINDOW_MANAGER_HPP)

#define UKACHULLDCS_0896X_WIN_WINDOW_MANAGER_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <unordered_set>         // std::unordered_set<>
#include <vector>                // std::vector<>
#include <windows.h>             // win32 stuff>

// includes, project

//#include <>

namespace win {

  namespace window {
    
    // types, exported (class, enum, struct, union, typedef)

    class base;

    class manager : private boost::noncopyable {

    public:

      typedef std::vector<DEVMODE>                         devmode_list_type;
      typedef std::pair<DISPLAY_DEVICE, devmode_list_type> display_devmode_pair_type;
      typedef std::vector<display_devmode_pair_type>       display_list_type;
      typedef std::vector<MONITORINFOEX>                   monitor_list_type;

      static display_list_type const& display_list(bool /* re-scan */ = false);
      static monitor_list_type const& monitor_list(bool /* re-scan */ = false);
      static unsigned                 count();

    private:

      friend class base;

      typedef std::unordered_set<base*> window_list_type;

      static display_list_type display_list_;
      static monitor_list_type monitor_list_;
      static window_list_type* window_list_;

      static bool add(base*);
      static bool sub(base*);

    };

    // variables, exported (extern)

    // functions, inlined (inline)

    // functions, exported (extern)

  } // namespace window {

} // namespace win {

#endif // #if !defined(UKACHULLDCS_0896X_WIN_WINDOW_MANAGER_HPP)
