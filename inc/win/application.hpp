// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  win/application.hpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_WIN_APPLICATION_HPP)

#define UKACHULLDCS_0896X_WIN_APPLICATION_HPP

// includes, system

// #include <>

// includes, project

#include <support/application.hpp>

namespace win {
  
  // types, exported (class, enum, struct, union, typedef)

  class application : public support::application::single_instance {

  public:
    
    virtual signed run();

    virtual void print_on(std::ostream&) const;

  protected:

    static bool use_window_manager_count_; // dflt: true

    explicit application(int /* argc */, char* /* argv */[]);
    virtual ~application() =0;

    virtual void   message_wait();
    virtual signed message_loop();

  private:

    template <typename T> friend signed execute(int, char* []);
    
    static void setup();
    
  };
  
  // variables, exported (extern)

  // functions, inlined (inline)

  /**
   * \brief ...
   *
   * \c
   *
   * \param  argc
   * \param  argv
   * \return EXIT_[FAILURE|SUCCESS]
   *
   * \throw  std::runtime_error
   */
  //@{
  template <typename T> signed execute(int, char* []);
  template <typename T> signed execute(int, char* [], std::nothrow_t const&);
  //@}
  
  // functions, exported (extern)
  
} // namespace win {

#include <win/application.inl>

#endif // #if !defined(UKACHULLDCS_0896X_WIN_APPLICATION_HPP)
