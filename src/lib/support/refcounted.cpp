// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/refcounted.cpp                                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/refcounted.hpp"

// includes, system

// #include <>

// includes, project

// #include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal

  std::memory_order const default_memory_order(std::memory_order_relaxed);

  // functions, internal

} // namespace {

namespace support {
  
  // variables, exported
  
  // functions, exported

  /* explicit */
  refcounted::guard::guard(refcounted const* a)
    : boost::noncopyable(),
      refcnt_           (a)
  {
    TRACE("support::refcounted::guard::guard");

    refcnt_->add_ref();
  }
  
  refcounted::guard::~guard()
  {
    TRACE("support::refcounted::guard::~guard");

    refcnt_->sub_ref();
  }
  
  void
  refcounted::add_ref() const
  {
    TRACE("support::refcounted::add_ref");
    
    std::atomic_fetch_add_explicit(&count_, 1, default_memory_order);
  }

  void
  refcounted::sub_ref() const
  {
    TRACE("support::refcounted::sub_ref");
    
    // atomic decrement by 1 and return old value, i.e. new current value of
    // zero will return old value one!
    if (1 == std::atomic_fetch_sub_explicit(&count_, 1, default_memory_order)) {
      delete this;
    }
  }

  signed
  refcounted::get_ref() const
  {
    TRACE("support::refcounted::get_ref");
    
    return std::atomic_load_explicit(&count_, default_memory_order);
  }
  
  /* explicit */
  refcounted::refcounted()
    : boost::noncopyable(),
      count_            (0) /* should be ATOMIC_VAR_INIT(0), but MSVC cannot compile this */
  {
    TRACE("support::refcounted::refcounted");
  }

  /* virtual */
  refcounted::~refcounted()
  {
    TRACE("support::refcounted::~refcounted");
  }

  void
  intrusive_ptr_add_ref(refcounted const* p)
  {
    TRACE("support::intrusive_ptr_add_ref");
    
    p->add_ref();
  }

  void
  intrusive_ptr_release(refcounted const* p)
  {
    TRACE("support::intrusive_ptr_release");
    
    p->sub_ref();
  }
  
} // namespace support {
