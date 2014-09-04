// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/type_info.cpp                                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/type_info.hpp"

// includes, system

#if defined(__GNUC__)
#  include <cstdlib>   // std::free
#  include <cxxabi.h>  // abi::__cxa_demangle
#  include <new>       // std::bad_alloc
#  include <stdexcept> // std::domain_error, std::invalid_argument
#endif // defined(__GNUC__)

#include <typeinfo>    // std::type_info

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
  demangle(std::type_info const& tinfo)
  {
    TRACE("support::demangle");

    std::string result(tinfo.name());
    
#if defined(__GNUC__)
    {
      signed      status(0);
      char* const demangled_name(abi::__cxa_demangle(tinfo.name(), 0, 0, &status));
      
      result = demangled_name;
      
      std::free(demangled_name);
      
      switch (status) {
      case -1: // memory allocation failure
        throw std::bad_alloc();
        break;
        
      case -2: // not a valid name under the C++ ABI mangling rules
        throw std::domain_error("<support::demangle/abi::__cxa_demangle>: "
                                "invalid mangled type name");
        break;
        
      case -3: // One of the arguments is invalid
        throw std::invalid_argument("<support::demangle/abi::__cxa_demangle>: "
                                    "invalid arguments");
        break;
      }
    }
#endif

    return result;
  }

  std::string
  demangle(std::type_info const& tinfo, std::nothrow_t const&)
  {
    TRACE("support::demangle(std::nothrow_t)");
    
    std::string result(tinfo.name());
    
    try {
      result = demangle(tinfo);
    }

    catch (std::exception const&) { /* do nothing */}

    return result;
  }
  
} // namespace support {
