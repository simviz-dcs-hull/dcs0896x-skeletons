// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/type_info.hpp                                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_TYPE_INFO_HPP)

#define UKACHULLDCS_0896X_SUPPORT_TYPE_INFO_HPP

// includes, system

#include <new>    // std::nothrow_t, std::nothrow (for caller convenience)
#include <string> // std::string

// includes, project

// #include <>

namespace std {

  class type_info;

}

namespace support {
  
  // types, exported (class, enum, struct, union, typedef)

  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)

  /**
   * \brief returns the demangled type name of an object
   *
   * returns the demangled type name of an object represented by an \c std::type_info object
   *
   * \param  tinfo \c std::type_info object of an actual object
   *
   * \return demangled type name
   *
   * \throws \c std::bad_alloc or \c std::domain_error or \c std::invalid_argument
   */
  std::string demangle(std::type_info const&);

  /**
   * \brief returns the demangled type name of an object
   *
   * returns the demangled type name of an object represented by an \c std::type_info object
   * this version internally calls the throwing \c support::demangle function and catches any
   * \c std::exceptions. in such a case the unmangled type name is returned.
   *
   * \param  tinfo           \c std::type_info object of an actual object
   * \param  \c std::nothrow signature disambiguation tag
   *
   * \return demangled type name or unmangled name if demangling fails
   *
   * \throws nothing
   */
  std::string demangle(std::type_info const&, std::nothrow_t const&);
  
} // namespace support {

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_TYPE_INFO_HPP)
