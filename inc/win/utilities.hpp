// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win_utilities.hpp                                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_WIN_UTILITIES_HPP)

#define UKACHULLDCS_0896X_WIN_UTILITIES_HPP

// includes, system

#include <string>
#include <windows.h>

// includes, project

//#include <>

namespace win {
  
  // types, exported (class, enum, struct, union, typedef)

  // variables, exported (extern)

  // functions, inlined (inline)

  template <class T> T  window_long (HWND, signed);
  template <class T> T  window_long (HWND, T, signed);

  template <class T> T* window_long_ptr(HWND, signed);
  template <class T> T* window_long_ptr(HWND, T*, signed);

  template <class T> T  class_long (HWND, signed);
  template <class T> T  class_long (HWND, T, signed);

  template <class T> T* class_long_ptr(HWND, signed);
  template <class T> T* class_long_ptr(HWND, T*, signed);
  
  // functions, exported (extern)

  std::string module_path(HMODULE module);
  std::string last_error_message();
  
} // namespace win {

#include <win/utilities.inl>

#endif // #if !defined(UKACHULLDCS_0896X_WIN_UTILITIES_HPP)
