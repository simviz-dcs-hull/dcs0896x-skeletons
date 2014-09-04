// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/printable.hpp                                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_PRINTABLE_HPP)

#define UKACHULLDCS_0896X_SUPPORT_PRINTABLE_HPP

// includes, system

#include <iosfwd> // std::basic_ostream<> (fwd)

// includes, project

// #include <>

namespace support {

  // types, exported (class, enum, struct, union, typedef)

  class printable {

  public:

    virtual ~printable();
    
    virtual void print_on(std::ostream&)  const =0;
    virtual void print_on(std::wostream&) const;
    
  };

  // variables, exported (extern)

  // functions, inlined (inline)

  // functions, exported (extern)

  template <typename CTy, typename CTr>
  std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, printable const&);

} // namespace support {

#include <support/printable.inl>

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_PRINTABLE_HPP)
