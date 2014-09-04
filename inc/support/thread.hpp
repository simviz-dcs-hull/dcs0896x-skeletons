// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/thread.hpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_THREAD_HPP)

#define UKACHULLDCS_0896X_SUPPORT_THREAD_HPP

// includes, system

#include <iosfwd>             // std::ostream (fwd)
#include <mutex>              // std::mutex, std::lock_guard<>
#include <string>             // std::string
#include <thread>             // std::this_thread, std::thread

// includes, project

#include <support/chrono.hpp> // support::clock::duration

#if defined(__GNUC__)
// 'thread_local' != '__thread'
// #  define thread_local __thread
#elif defined(_MSC_VER)
#  define thread_local __declspec(thread)
#else
#  error "unable to determine 'thread_local' keyword workaround"
#endif

namespace support {
  
  // types, exported (class, enum, struct, union, typedef)

  namespace this_thread = std::this_thread;
  
  typedef std::mutex                   simple_lock;
  typedef std::lock_guard<simple_lock> simple_lock_guard;
  
  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)

  void dump_thread_stats(std::ostream&          /* output_stream     */,
                         std::string const&     /* context_string    */,
                         clock::duration const& /* timeout/interval  */,
                         clock::duration const& /* actual activity   */,
                         bool                   /* thread_was_paused */,
                         unsigned               /* dump modulo       */ = 10);

} // namespace support {

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_THREAD_HPP)
