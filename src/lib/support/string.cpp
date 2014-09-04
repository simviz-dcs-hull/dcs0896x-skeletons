// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/string.cpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/thread.hpp"

// includes, system

#define GLIBCXX_NO_CODECVT 20140624

#if !defined(__GLIBCXX__) || (defined(__GLIBCXX__) && (__GLIBCXX__ > GLIBCXX_NO_CODECVT))
#  include <codecvt> // std::codecvt_utf8<>
#endif

#include <locale>    // std::wstring_convert<>

// includes, project

// #include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal
  
  // functions, internal

} // namespace {

namespace support {
  
  // variables, exported
  
  // functions, exported

  std::string
  wstring_to_string(std::wstring const& a)
  {
    TRACE("support::wstring_to_string");

#if defined(__GLIBCXX__) && (__GLIBCXX__ <= GLIBCXX_NO_CODECVT)
    return std::string(a.begin(), a.end());
#else
    return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(a);
#endif
  }
  
  std::wstring
  string_to_wstring(std::string const& a)
  {
    TRACE("support::string_to_wstring");
    
    return std::wstring(a.begin(), a.end());
  }
  
} // namespace support {
