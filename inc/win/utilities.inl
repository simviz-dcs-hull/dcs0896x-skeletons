// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/utilities.inl                                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_WIN_UTILITIES_INL)

#define UKACHULLDCS_0896X_WIN_UTILITIES_INL

// includes, system

//#include <>

// includes, project

//#include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>
//#if defined(UKACHULLDCS_USE_TRACE) || defined(UKACHULLDCS_ALL_TRACE)
//#  include <typeinfo>
//#  include <support/type_info.hpp>
//#endif

namespace win {
  
  // functions, inlined (inline)

  template <class T>
  inline T
  window_long(HWND a, signed b)
  {
    return reinterpret_cast<T>(::GetWindowLong(a, b));
  }

  template <class T>
  inline T
  window_long(HWND a, T b, signed c)
  {
    return reinterpret_cast<T>(::SetWindowLong(a, c, reinterpret_cast<LONG>(b)));
  }

  template <class T>
  inline T*
  window_long_ptr(HWND a, signed b)
  {
    return reinterpret_cast<T*>(::GetWindowLongPtr(a, b));
  }

  template <class T>
  inline T*
  window_long_ptr(HWND a, T* b, signed c)
  {
    return reinterpret_cast<T*>(::SetWindowLongPtr(a, c, reinterpret_cast<LONG_PTR>(b)));
  }

  template <>
  inline DWORD
  window_long<DWORD>(HWND a, signed b)
  {
    return static_cast<DWORD>(::GetWindowLong(a, b));
  }

  template <>
  inline DWORD
  window_long<DWORD>(HWND a, DWORD b, signed c)
  {
    return static_cast<DWORD>(::SetWindowLong(a, c, static_cast<LONG>(b)));
  }

  template <class T>
  inline T
  class_long(HWND a, signed b)
  {
    return reinterpret_cast<T>(::GetClassLong(a, b));
  }

  template <class T>
  inline T
  class_long(HWND a, T b, signed c)
  {
    return reinterpret_cast<T>(::SetClassLong(a, c, reinterpret_cast<LONG>(b)));
  }

  template <class T>
  inline T*
  class_long_ptr(HWND a, signed b)
  {
    return reinterpret_cast<T*>(::GetClassLongPtr(a, b));
  }

  template <class T>
  inline T*
  class_long_ptr(HWND a, T* b, signed c)
  {
    return reinterpret_cast<T*>(::SetClassLongPtr(a, c, reinterpret_cast<LONG_PTR>(b)));
  }

  template <>
  inline DWORD
  class_long<DWORD>(HWND a, signed b)
  {
    return static_cast<DWORD>(::GetClassLong(a, b));
  }

  template <>
  inline DWORD
  class_long<DWORD>(HWND a, DWORD b, signed c)
  {
    return static_cast<DWORD>(::SetClassLong(a, c, static_cast<LONG>(b)));
  }

} // namespace win {

#if defined(UKACHULLDCS_USE_TRACE)
#  undef UKACHULLDCS_USE_TRACE
#endif

#endif // #if !defined(UKACHULLDCS_0896X_WIN_UTILITIES_INL)
