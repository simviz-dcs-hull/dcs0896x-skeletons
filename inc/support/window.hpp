// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/window.hpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_WINDOW_HPP)

#define UKACHULLDCS_0896X_SUPPORT_WINDOW_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable

// includes, project

#include <support/printable.hpp>

namespace support {

  namespace window {
    
    // types, exported (class, enum, struct, union, typedef)

    class base : private boost::noncopyable,
                 public support::printable {

    public:

      virtual ~base() =0;
      
      virtual void print_on(std::ostream&) const;
    
    protected:

      std::string title_;

      explicit base(std::string const& /* title */);
      
    };
    
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

  } // namespace window {
  
} // namespace support {

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_WINDOW_HPP)
