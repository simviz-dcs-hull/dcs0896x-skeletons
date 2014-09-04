// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/test/application.cpp                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <support/application.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  template <typename T, bool B>
  class app_skeleton : public T {

  public:

    explicit app_skeleton(int argc, char* argv[])
      : T(argc, argv)
    {}
    
    virtual signed run()
    {
      if (B) {
        throw std::runtime_error("run-time error");
      }
      
      return EXIT_SUCCESS;
    }
    
  };

  typedef app_skeleton<support::application::multi_instance,  false> appmin;
  typedef app_skeleton<support::application::multi_instance,  true>  appmit;
  typedef app_skeleton<support::application::single_instance, false> appsin;
  typedef app_skeleton<support::application::single_instance, true>  appsit;
  
  // variables, internal

  int   argc(1);
  char* argv[] = { "dummy" };
  
  // functions, internal

} // namespace {

// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_support_application_execute)
{
  using support::application::execute;
  
  BOOST_CHECK(EXIT_SUCCESS == execute<appmin>(argc, argv));
  BOOST_CHECK(EXIT_SUCCESS == execute<appsin>(argc, argv));
}

BOOST_AUTO_TEST_CASE(test_support_application_execute_nothrow)
{
  using support::application::execute;
  
  BOOST_CHECK(EXIT_SUCCESS != execute<appmit>(argc, argv, std::nothrow));
  BOOST_CHECK(EXIT_SUCCESS != execute<appsit>(argc, argv, std::nothrow));
}

BOOST_AUTO_TEST_CASE(test_support_application_execute_single_instance_fail)
{
  using support::application::single_instance;
  
  class app_single_instance_fail : public single_instance {

  public:

    explicit app_single_instance_fail(int argc, char* argv[])
      : single_instance(argc, argv) {}
    
    virtual signed run() { return EXIT_SUCCESS; }
    
  } instance(1, nullptr);

  using support::application::execute;
  
  BOOST_CHECK_THROW(execute<app_single_instance_fail>(argc, argv), std::exception);
}

BOOST_AUTO_TEST_CASE(test_support_application_execute_single_instance_fail_nothrow)
{
  using support::application::single_instance;
  
  class app_single_instance_fail : public single_instance {

  public:

    explicit app_single_instance_fail(int argc, char* argv[])
      : single_instance(argc, argv) {}
    
    virtual signed run() { return EXIT_SUCCESS; }
    
  } instance(1, nullptr);

  using support::application::execute;
  
  BOOST_CHECK(EXIT_SUCCESS != execute<app_single_instance_fail>(argc, argv, std::nothrow));
}
