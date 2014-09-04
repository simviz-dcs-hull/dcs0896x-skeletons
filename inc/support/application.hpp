// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/application.hpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_APPLICATION_HPP)

#define UKACHULLDCS_0896X_SUPPORT_APPLICATION_HPP

// includes, system

#include <boost/noncopyable.hpp>     // boost::noncopyable
#include <boost/program_options.hpp> // boost::program_options::options_description,
                                     // boost::program_options::positional_options_description,
                                     // boost::program_options::variables_map

// includes, project

#include <support/printable.hpp>

namespace support {

  namespace application {
    
    // types, exported (class, enum, struct, union, typedef)

    class base : private boost::noncopyable,
                 public support::printable {

    public:

      virtual signed run() =0;

      virtual void print_on(std::ostream&) const;
    
    protected:
    
      boost::program_options::options_description            cmdline_options_;
      boost::program_options::positional_options_description cmdline_positionals_;
      unsigned                                               verbose_level_;
    
      explicit base(int /* argc */, char* /* argv */[]);
      virtual ~base() =0;

      virtual void cmdline_eval   (boost::program_options::variables_map&);
      virtual void cmdline_process(int /* argc */, char* /* argv */[]);
    
    };

    class multi_instance : public base {

    protected:

      explicit multi_instance(int /* argc */, char* /* argv */[]);
      virtual ~multi_instance();
    
    };
  
    class single_instance : public base {

    protected:

      static single_instance* instance_;
      
      explicit single_instance(int /* argc */, char* /* argv */[]);
      virtual ~single_instance();

      virtual void print_on(std::ostream&) const;
    
    };
  
    template <typename T>
    class executor : private boost::noncopyable {

    public:

      explicit executor(int, char* []);
              ~executor();
      
      signed run();
    
    private:

      std::unique_ptr<T> instance_;
    
    };
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    template <typename T> signed execute(int, char* []);
    template <typename T> signed execute(int, char* [], std::nothrow_t const&);
    
  } // namespace application {
  
} // namespace support {

#include <support/application.inl>

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_APPLICATION_HPP)
