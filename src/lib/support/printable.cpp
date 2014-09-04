// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/printable.cpp                                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/printable.hpp"

// includes, system

#include <ostream>   // std::ostream
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error

// includes, project

#include <support/string.hpp>

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

  /* virtual */
  printable::~printable()
  {
    TRACE("support::printable::~printable");
  }
  
  /* virtual */ void
  printable::print_on(std::ostream&) const
  {
    TRACE_NEVER("support::printable::print_on(std::ostream)");

    throw std::logic_error("pure virtual function 'support::printable::print_on' called");
  }

  /* virtual */ void
  printable::print_on(std::wostream& wos) const
  {
    TRACE_NEVER("support::printable::print_on(std::wostream)");

    std::ostringstream ostr;
    
    print_on(ostr);

    wos << string_to_wstring(ostr.str());
  }
  
} // namespace support {
