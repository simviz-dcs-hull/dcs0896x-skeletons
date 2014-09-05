// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/application.inl                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_WIN_APPLICATION_INL)

#define UKACHULLDCS_0896X_WIN_APPLICATION_INL

// includes, system

#include <csignal>   // getenv, signal, SIG*
#include <cstddef>   // EXIT_*
#include <cstdlib>   // EXIT_FAILURE
#include <stdexcept> // std::exception
#include <windows.h> // win32 stuff

// includes, project

#include <win/utilities.hpp>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>
#if defined(UKACHULLDCS_USE_TRACE) || defined(UKACHULLDCS_ALL_TRACE)
#  include <typeinfo>
#  include <support/type_info.hpp>
#endif

namespace win {
  
  // functions, inlined (inline)

  template <typename T>
  inline signed
  execute(int argc, char* argv[])
  {
    TRACE("win::application::execute<" + demangle(typeid(T)) + ">");

    static signed msg_loop_thr_id(::GetCurrentThreadId());

    struct signal_handler {

    public:

      static void handle(signed signum)
      {
        TRACE("win::application::execute<" + demangle(typeid(T)) +
              ">::<local>::signal_handler::handle");

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
          std::cout << support::trace::prefix() << "win::application::execute<"
                    << demangle(typeid(T)) << ">::<local>::signal_handler::handle: "
                    << "sending WM_APP/WM_QUIT to thread 0x" << std::hex << msg_loop_thr_id
                    << std::endl;
#endif
          
          ::PostThreadMessage(msg_loop_thr_id, WM_APP, exit_code, WM_QUIT);
        }
      }
      
    };
    
    ::signal(SIGINT,  signal_handler::handle);
    ::signal(SIGTERM, signal_handler::handle);
  
#if defined(_DEBUG) || defined(DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
  
    signed result(EXIT_FAILURE);
    
    try {
      result = support::application::executor<T>(argc, argv).run();
    }

    catch (std::exception& ex) {
      std::ostringstream msg;

      msg << "Exception of type '" << typeid(ex).name() << "' caught: "
          << "'" << ex.what() << "'; last error:  " << win::last_error_message();

      ::MessageBox(nullptr, msg.str().c_str(), "Exception", MB_ICONEXCLAMATION | MB_OK);

      throw std::runtime_error(msg.str().c_str());
    }
  
    catch (...) {
      std::ostringstream msg;

      msg << "Unknown exception caught; last error: " << win::last_error_message();
    
      ::MessageBox(nullptr, msg.str().c_str(), "Exception", MB_ICONEXCLAMATION | MB_OK);

      throw std::runtime_error(msg.str().c_str());
    }
  
    return result;
  }

  template <typename T>
  inline signed
  execute(int argc, char* argv[], std::nothrow_t const&)
  {
    TRACE("win::application::execute<" + demangle(typeid(T)) + ">(std::nothrow_t)");
      
    signed result(EXIT_FAILURE);
      
    try {
      result = execute<T>(argc, argv);
    }
      
    catch (std::exception&) { /* sink only */ }
      
    return result;
  }
  
} // namespace win {

#if defined(UKACHULLDCS_USE_TRACE)
#  undef UKACHULLDCS_USE_TRACE
#endif

#endif // #if !defined(UKACHULLDCS_0896X_WIN_APPLICATION_INL)
