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

#include <cstddef>   // EXIT_*
#include <cstdlib>   // EXIT_FAILURE
#include <stdexcept> // std::exception
#include <windows.h> // win32 stuff

// includes, project

#include <win/utilities.hpp>

#define UKACHULLDCS_USE_TRACE
//#undef UKACHULLDCS_USE_TRACE
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
    TRACE("win::application::execute<" + support::demangle(typeid(T)) + ">");
    
    T::setup();
    
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
    TRACE("win::application::execute<" + support::demangle(typeid(T)) + ">(std::nothrow_t)");
      
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

#pragma comment(linker, "/ENTRY:mainCRTStartup")
#if defined(_DEBUG) || defined(DEBUG)
#  pragma comment(linker, "/SUBSYSTEM:console ")
#  pragma message(__FILE__ ": /SUBSYSTEM:console /ENTRY:mainCRTStartup")
#else
#  pragma comment(linker, "/SUBSYSTEM:windows")
#  pragma message(__FILE__ ": /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#endif // #if !defined(UKACHULLDCS_0896X_WIN_APPLICATION_INL)
