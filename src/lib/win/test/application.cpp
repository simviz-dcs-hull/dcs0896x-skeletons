// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/test/application.cpp                                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <support/chrono.hpp>
#include <win/application.hpp>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

#if defined(_MSC_VER)
#  pragma warning(disable:4127)
#endif

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  template <typename T, bool B>
  class app_skeleton : public T {
    
  public:
    
    explicit app_skeleton(int a, char* b[])
      : T(a, b)
    {
      use_window_manager_count_ = false;
    }    

  private:

    virtual void message_wait()
    {
      TRACE("win::application::message_wait");

      if (B) {
        throw std::runtime_error("run-time error");
      }
      
      T::message_wait();
    }
    
  };
  
  typedef app_skeleton<win::application, false>    appsin;
  typedef app_skeleton<win::application, true>     appsit;
  
  // variables, internal

  int   argc(1);
  char* argv[] = { "dummy\0" };
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_support_application_execute)
{
  using win::execute;

  BOOST_CHECK(EXIT_SUCCESS == execute<appsin>(argc, argv));
}

BOOST_AUTO_TEST_CASE(test_support_application_execute_nothrow)
{
  using win::execute;

  BOOST_CHECK(EXIT_SUCCESS != execute<appsit>(argc, argv, std::nothrow));
}

#if defined(_MSC_VER)
#  pragma warning(default:4127)
#endif
