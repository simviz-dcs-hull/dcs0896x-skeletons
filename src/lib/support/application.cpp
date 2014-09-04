// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/application.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/application.hpp"

// includes, system

#include <boost/concept_check.hpp> // boost::ignore_unused_variable_warning<>
#include <boost/filesystem.hpp>    // boost::filesystem::path
#include <stdexcept>               // std::logic_error

// includes, project

// #include <>

#define UKACHULLDCS_USE_TRACE
#undef UKACHULLDCS_USE_TRACE
#include <support/trace.hpp>

#if defined(UKACHULLDCS_USE_TRACE)
#  include <iomanip>
#endif

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace support {

  namespace application {
    
    // variables, exported

    /* static */ single_instance* single_instance::instance_(nullptr);
    
    // functions, exported  
  
    /* virtual */ signed
    base::run()
    {
      TRACE("support::application::base::run");

      throw std::logic_error("pure virtual function 'support::application::base::run' called");
    
      return EXIT_FAILURE;
    }

    /* virtual */ void
    base::print_on(std::ostream& os) const
    {
      TRACE_NEVER("support::application::base::print_on");
      
      os << '['
         << "@0x"      << this << ','
         << "verbose:" << verbose_level_
         << ']';
    }
  
    /* explicit */
    base::base(int /* argc */, char* /* argv */[])
      : boost::noncopyable  (),
        support::printable  (),
        cmdline_options_    (),
        cmdline_positionals_(),
        verbose_level_      (0)
    {
      TRACE("support::application::base::application");
      
      namespace po = boost::program_options;

      po::options_description global("Global Options");
      
      global.add_options()
        ("help,h", "display command-line help and exit");
      
      global.add_options()
        ("verbose,v",
         po::value<unsigned>(&verbose_level_)
         ->implicit_value(verbose_level_ + 1)
         ->default_value (verbose_level_),
         "verbosity level");
      
      cmdline_options_.add(global);
    }
  
    /* virtual */
    base::~base()
    {
      TRACE("support::application::base::~application");
    }

    /* virtual */ void
    base::cmdline_eval(boost::program_options::variables_map&)
    {
      TRACE("support::application::base::cmdline_eval");
    }
  
    /* virtual */ void
    base::cmdline_process(int argc, char* argv[])
    {
      TRACE("support::application::base::cmdline_process");
    
      namespace po = boost::program_options;

      std::string const base_name   (boost::filesystem::path(argv[0]).filename().string());
      bool              print_help  (false);
      signed            return_value(EXIT_SUCCESS);
      po::variables_map vm;
    
      try {
        po::store(po::command_line_parser(argc, argv)
                  .options   (cmdline_options_)
                  .positional(cmdline_positionals_)
                  .run       (),
                  vm);

        po::notify(vm);
      }
    
      catch (std::exception const& ex) {
        std::cerr << '\n' /* << base_name << ' ' */
                  << "command-line problem: " << ex.what() << std::endl;
      
        print_help   = true;
        return_value = EXIT_FAILURE;
      }
    
      if (vm.count("help") || print_help) {
        std::cerr << "\nusage: " << base_name << " [OPTIONS] [POSITIONALS ...]\n"
                  << cmdline_options_
                  << std::endl;
      
        std::exit(return_value);
      }

      cmdline_eval(vm);
    }

    /* explicit */
    multi_instance::multi_instance(int argc, char* argv[])
      : base(argc, argv)
    {
      TRACE("support::application::multi_instance::multi_instance");
    }
    
    /* virtual */
    multi_instance::~multi_instance()
    {
      TRACE("support::application::multi_instance::~multi_instance");
    }
    
    /* explicit */
    single_instance::single_instance(int argc, char* argv[])
      : base(argc, argv)
    {
      TRACE("support::application::single_instance::single_instance");

      if (!instance_) {
        instance_ = this;
      } else {
        throw std::logic_error("'support::application::single_instance' already initialized");
      }
    }
    
    /* virtual */
    single_instance::~single_instance()
    {
      TRACE("support::application::single_instance::~single_instance");

      if (this == instance_) {
        instance_ = nullptr;
      }
    }
    
    /* virtual */ void
    single_instance::print_on(std::ostream& os) const
    {
      TRACE_NEVER("support::application::single_instance::print_on");

      base::print_on(os);

      os << "\b,@" << instance_ << ']';
    }
    
  } // namespace application {
  
} // namespace support {
