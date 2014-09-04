// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/trace.cpp                                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/trace.hpp"

// includes, system

#include <iomanip>  // std::dec, std::hex, std::setfill
#include <ostream>  // std::ostream
#include <sstream>  // std::ostringstream

// includes, project

#include <support/chrono.hpp> // support::clock, support::timer
#include <support/thread.hpp> // support::lock_guard<>, support::mutex, thread_local

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal
  
  thread_local unsigned              trace_depth(0);       // per thread indentation depth
               support::simple_lock* trace_lock (nullptr); // intra-thread output lock
               support::timer*       trace_timer(nullptr);
  
  // functions, internal

  void
  init_local_statics()
  {
    static bool initialized(false);

    if (!initialized) {
      std::ios_base::Init _;
      
      trace_lock  = new support::simple_lock;
      trace_timer = new support::timer;
      
      initialized = true;
    }
  }
  
} // namespace {

namespace support {
  
  // variables, exported
  
  // functions, exported

  /* explicit */
  trace::trace(std::string const& msg, std::ostream& os)
    : boost::noncopyable(),
      msg_(msg),
      os_ (os)
  {
    enter(msg_, os_);
  }

  trace::~trace()
  {
    leave(msg_, os_);
  }

  /* static */ void
  trace::enter(std::string const& msg, std::ostream& os)
  {
    init_local_statics();
    
    support::simple_lock_guard const lg(*trace_lock);
    
    os << prefix() << "-> " << msg << '\n';

    ++trace_depth;
  }

  /* static */ void
  trace::leave(std::string const& msg, std::ostream& os)
  {
    init_local_statics();
    
    support::simple_lock_guard const lg(*trace_lock);
    
    --trace_depth;

    os << prefix() << "<- " << msg << '\n';
  }

  /* static */ std::string
  trace::prefix()
  {
    init_local_statics();
    
    using std::chrono::duration_cast;
    using std::chrono::microseconds;
    
    std::ostringstream ostr;
    
    ostr << '['
         << std::setfill('0')
         << "0x"
         << std::hex << std::setw(8) << support::this_thread::get_id()
         << ':'
         << std::dec << std::setw(12) << duration_cast<microseconds>(trace_timer->lapse()).count()
         << "us"
         << ']'
         << std::string((trace_depth * 3) + 1, ' ');

    return ostr.str();
  }
  
} // namespace support {
