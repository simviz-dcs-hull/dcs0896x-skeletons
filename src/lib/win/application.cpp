// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/application.cpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "win/application.hpp"

// includes, system

#include <csignal> // signal, SIG*

// includes, project

#include <win/window/manager.hpp>

#define UKACHULLDCS_USE_TRACE
//#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace win {
  
  // variables, exported

  /* static */ bool application::use_window_manager_count_(true);
  
  // functions, exported

  /* virtual */ signed
  application::run()
  {
    TRACE("win::application::run");

    return message_loop();
  }
  
  /* virtual */ void
  application::print_on(std::ostream& os) const
  {
    TRACE_NEVER("win::application::print_on");
      
    support::application::single_instance::print_on(os);
  }

  /* explicit */
  application::application(int a, char* b[])
    : support::application::single_instance(a, b)
  {
    TRACE("win::application::application");
  }
  
  /* virtual */
  application::~application()
  {
    TRACE("win::application::~application");
  }
  
  /* virtual */ void
  application::message_wait()
  {
    TRACE("win::application::message_wait");
    
    ::WaitMessage();
  }
  
  /* virtual */ signed
  application::message_loop()
  {
    TRACE("win::application::message_loop");

    bool done(false);
    MSG  msg = { 0 };

    while (!done && (!use_window_manager_count_ || win::window::manager::count())) {
      message_wait();
      
      if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        ::TranslateMessage(&msg);
        ::DispatchMessage (&msg);

        if (WM_QUIT == msg.message) {
          if (99 <= verbose_level_) {
            std::cout << support::trace::prefix() << "win::application::message_loop: "
                      << "received WM_QUIT" << std::endl;
          }

          done = true;          
        }

        if ((WM_APP == msg.message) && (WM_QUIT == msg.lParam)) {
          if (99 <= verbose_level_) {
            std::cout << support::trace::prefix() << "win::application::message_loop: "
                      << "received WM_APP/WM_QUIT, sending WM_QUIT" << std::endl;
          }
          
          ::PostQuitMessage(signed(msg.wParam));
        }
      }
    }

    return signed(msg.wParam);
  }

  namespace {

    signed msg_loop_thr_id(-1);
    
    void
    signal_handler(signed signum)
    {
      TRACE("win::<unnamed>::signal_handler");
    
      signed exit_code(EXIT_FAILURE);
    
      switch (signum) {
      case SIGINT:
      case SIGTERM:
        exit_code = EXIT_SUCCESS;
        break;
      
      default:
        break;
      }
    
      if (-1 != msg_loop_thr_id) {
#if defined(UKACHULLDCS_USE_TRACE)
        std::cout << support::trace::prefix() << "win::signal_handler::handler: "
                  << "sending WM_APP/WM_QUIT to thread 0x" << std::hex << msg_loop_thr_id
                  << std::endl;
#endif
      
        ::PostThreadMessage(msg_loop_thr_id, WM_APP, exit_code, WM_QUIT);
      }
    }
    
  }
  
  /* static */ void
  application::setup()
  {
    TRACE("win::application::setup");
    
    msg_loop_thr_id = ::GetCurrentThreadId();
    
    ::signal(SIGINT,  signal_handler);
    ::signal(SIGTERM, signal_handler);
  }
  
} // namespace win {
