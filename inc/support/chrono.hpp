// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/chrono.hpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_CHRONO_HPP)

#define UKACHULLDCS_0896X_SUPPORT_CHRONO_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <chrono>                // std::chrono::*
#include <iosfwd>                // std::ostream (fwd)
#include <string>                // std::string

// includes, project

// #include <>

namespace support {
  
  // types, exported (class, enum, struct, union, typedef)

  class clock : private boost::noncopyable {

  public:

    typedef std::chrono::nanoseconds                 duration;
    typedef duration::rep                            rep;
    typedef duration::period                         period;
    typedef std::chrono::time_point<clock, duration> time_point;

    static bool const     is_monotonic; // = true
    static duration const resolution;
    
    static time_point now() throw();
    
  };

  class timer : private boost::noncopyable {

  public:

    typedef clock::duration   duration;
    typedef clock::time_point time_point;

    explicit timer();
            ~timer();

    time_point reset();
    duration   lapse() const;

  private:
    
    time_point start_;

  };
  
  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)

  void        sleep(clock::duration const&);
  std::string date_time_iso8601();

  std::ostream& operator<<(std::ostream&, clock::time_point const&);
  
} // namespace support {

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_CHRONO_HPP)
