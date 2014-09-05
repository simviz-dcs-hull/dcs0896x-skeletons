// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/application.inl                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_APPLICATION_INL)

#define UKACHULLDCS_0896X_SUPPORT_APPLICATION_INL

// includes, system

#include <cstdlib> // EXIT_FAILURE

// includes, project

//#include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>
#if defined(UKACHULLDCS_USE_TRACE) || defined(UKACHULLDCS_ALL_TRACE)
#  include <typeinfo>
#  include <support/type_info.hpp>
#endif

namespace support {

  namespace application {
  
    // functions, inlined (inline)

    template <typename T>
    inline /* explicit */
    executor<T>::executor(int argc, char* argv[])
      : boost::noncopyable(),
        instance_         (new T(argc, argv))
    {
      TRACE("support::application::executor<" + demangle(typeid(T)) + ">::executor");
    }

    template <typename T>
    inline /* explicit */
    executor<T>::~executor()
    {
      TRACE("support::application::executor<" + demangle(typeid(T)) + ">::~executor");
    }
    
    template <typename T>
    inline signed
    executor<T>::run()
    {
      TRACE("support::application::executor<" + demangle(typeid(T)) + ">::run");
      
      return instance_->run();
    }

    template <typename T>
    inline signed
    execute(int argc, char* argv[])
    {
      TRACE("support::application::execute<" + demangle(typeid(T)) + ">");
      
      return executor<T>(argc, argv).run();
    }

    template <typename T>
    inline signed
    execute(int argc, char* argv[], std::nothrow_t const&)
    {
      TRACE("support::application::execute<" + demangle(typeid(T)) + ">(std::nothrow_t)");
      
      signed result(EXIT_FAILURE);
      
      try {
        result = execute<T>(argc, argv);
      }
      
      catch (std::exception&) { /* sink only */ }
      
      return result;
    }
    
  } // namespace application {
  
} // namespace support {

#if defined(UKACHULLDCS_USE_TRACE)
#  undef UKACHULLDCS_USE_TRACE
#endif

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_APPLICATION_INL)
