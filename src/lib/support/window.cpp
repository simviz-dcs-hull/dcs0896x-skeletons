// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/window.cpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/window.hpp"

// includes, system

//#include <>

// includes, project

//#include <>

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

  namespace window {
  
    // variables, exported
  
    // functions, exported

    /* virtual */
    base::~base()
    {
      TRACE("support::base::");
    }
    
    /* virtual */ void
    base::print_on(std::ostream& os) const
    {
      TRACE_NEVER("support::base::print_on");

      os << '[' << title_ << ']';
    }
    
    /* explicit */
    base::base(std::string const& a)
      : boost::noncopyable(),
        support::printable(),
        title_            (a)
    {
      TRACE("support::base::base");
    }
  
  } // namespace window {
  
} // namespace support {
