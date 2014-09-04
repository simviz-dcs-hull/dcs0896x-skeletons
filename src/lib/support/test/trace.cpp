// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/test/trace.cpp                                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

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

  struct static_init_test {
    
    static_init_test()
    {
      TRACE("<unnamed>::static_init_test::static_init_test");
    }
  
    ~static_init_test()
    {
      TRACE("<unnamed>::static_init_test::~static_init_test");
    }
    
  } static_init_test_instance;

  struct dynamic_init_test {
    
    dynamic_init_test()
    {
      TRACE("<unnamed>::dynamic_init_test::dynamic_init_test");
    }
  
    ~dynamic_init_test()
    {
      TRACE("<unnamed>::dynamic_init_test::~dynamic_init_test");
    }
    
  };
  
  // variables, internal
  
  // functions, internal

  void
  test_func()
  {
    TRACE("<unnamed>::test_func");
    
    {
      TRACE("<unnamed>::test_func: scope");
      
      static_init_test  static_init_test_instance;
      dynamic_init_test dynamic_init_test_instance;
    }  
  }

} // namespace {

// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_support_trace)
{
  TRACE_FUNC;

  dynamic_init_test dynamic_init_test_instance;
  
  test_func();

  BOOST_CHECK(true);
}
