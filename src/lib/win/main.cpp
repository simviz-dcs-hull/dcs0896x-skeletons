// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/main.cpp                                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <>

// includes, project

#include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

// internal unnamed namespace

#pragma comment(linker, "/ENTRY:mainCRTStartup")
#if defined(_DEBUG) || defined(DEBUG)
#  pragma comment(linker, "/SUBSYSTEM:console ")
#  pragma message(__FILE__ ": /SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else
#  pragma comment(linker, "/SUBSYSTEM:windows")
#  pragma message(__FILE__ ": /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal

  signed msg_loop_thr_id(-1);
  
  // functions, internal

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
#if defined(DCS08961D3D_USE_TRACE)
      std::cout << support::trace::prefix() << "win::<unnamed>::signal_handler: "
                << "sending WM_APP/WM_QUIT to thread 0x" << std::hex << msg_loop_thr_id
                << std::endl;
#endif
      
      ::PostThreadMessage(msg_loop_thr_id, WM_APP, exit_code, WM_QUIT);
    }
  }
  
} // namespace {

int
main(int argc, char* argv[])
{
  TRACE("win::main");

  msg_loop_thr_id = ::GetCurrentThreadId();
  
  ::signal(SIGINT,  signal_handler);
  ::signal(SIGTERM, signal_handler);
  
#if defined(_DEBUG) || defined(DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
  
  int result(EXIT_FAILURE);
  
  try {
    result = support::execute<>(argc, argv, std::nothrow);    
  }

  catch (std::exception& ex) {
    std::ostringstream msg;

    msg << "Exception of type '" << typeid(ex).name() << "' caught: "
        << "'" << ex.what() << "'; last error:  " << win::last_error_message();

    ::MessageBox(nullptr, msg.str().c_str(), "Exception", MB_ICONEXCLAMATION | MB_OK);
  }
  
  catch (...) {
    std::ostringstream msg;

    msg << "Unknown exception caught; last error: " << win::last_error_message();
    
    ::MessageBox(nullptr, msg.str().c_str(), "Exception", MB_ICONEXCLAMATION | MB_OK);
  }
  
  return result;
}
