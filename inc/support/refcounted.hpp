// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/refcounted.hpp                                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(UKACHULLDCS_0896X_SUPPORT_REFCOUNTED_HPP)

#define UKACHULLDCS_0896X_SUPPORT_REFCOUNTED_HPP

// includes, system

#include <atomic>                // std::atomic<>
#include <boost/noncopyable.hpp> // boost::noncopyable

// includes, project

// #include <>

namespace support {
  
  // types, exported (class, enum, struct, union, typedef)

  /**
   * \brief a reference-counted type
   *
   * a reference-counted type. \c add_ref/\c sub_ref are \c const and \c count_ is mutable to
   * allow refcounting of \c const objects.
   */
  class refcounted : private boost::noncopyable {

  public:

    class guard : private boost::noncopyable {

    public:

      explicit guard(refcounted const*);
              ~guard();

    private:
      
      refcounted const* refcnt_;
      
    };
    
    void   add_ref() const;
    void   sub_ref() const;
    signed get_ref() const;

  protected:

    explicit refcounted();
    virtual ~refcounted();

  private:
    
    mutable std::atomic<signed> count_;

  };
  
  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)

  /**
   * \brief support for automated reference counting with \c boost::intrusive_ptr<>
   *
   * \c intrusive_ptr_add_ref and \c intrusive_ptr_release wrap \c refcounted::add_ref and
   * \c refcounted::sub_ref interfaces, respectively, for use with any refcounted-derived instance
   * as a \c boost::intrusive_ptr<refcounted>. Note that \c boost::intrusive_ptr<> only automates
   * the reference counted but not setting the underlying pointer to \c nullptr. client code that
   * wishes to wrap a \c refcounted in a \c boost::intrusive_ptr<> needs to include the appropriate
   * boost header; \c intrusive_ptr_add_ref and \c intrusive_ptr_release should be found
   * automatically by the \c boost::intrusive_ptr<> specialization.
   *
   * \param  pointer
   * \return nothing
   *
   * \throw  nothing
   */
  //@{
  void intrusive_ptr_add_ref(refcounted const*);
  void intrusive_ptr_release(refcounted const*);
  //@}
  
} // namespace support {

#endif // #if !defined(UKACHULLDCS_0896X_SUPPORT_REFCOUNTED_HPP)
