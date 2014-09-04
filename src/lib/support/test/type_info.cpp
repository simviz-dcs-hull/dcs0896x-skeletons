// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/test/type_info.cpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <string>   // std::string
#include <typeinfo> // typeid usage
#include <vector>   // std::vector<>

// includes, project

#include <support/type_info.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  class udt_base {
  };

  class udt_derived : public udt_base {
  };

  typedef std::vector<std::string> string_list_type;
  
  // variables, internal
  
  // functions, internal
  
} // namespace {
  
// variables, exported
  
// functions, exported  

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<bool,
                         char,
                         int,
                         float,
                         double,
                         udt_derived,
                         string_list_type> types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_support_type_info_demangle, T, types)
{
  BOOST_CHECK(typeid(T) == typeid(T));

  BOOST_MESSAGE(support::demangle(typeid(T)) << "\t: " << typeid(T).name());
}
