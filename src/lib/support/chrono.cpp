// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2014 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/chrono.cpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "support/chrono.hpp"

// includes, system

#include <ctime>  // ::clock_get*, std::localtime, std::time, std::strftime
#include <locale> // std::locale

#if defined(_WIN32)
#  include <cerrno>  // errno, E*
#  include <cstdint> // 
#  include <winsock2.h>
#endif // #if defined(_WIN32)

// includes, project

#include <support/chrono_io.hpp>
#include <support/thread.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
#if defined(_WIN32)
  // http://code.google.com/p/libpthread/source/browse/
#  define DELTA_EPOCH_IN_100NS INT64_C(116444736000000000)
  
#  define MAX_SLEEP_IN_MS 4294967294UL
#  define POW10_2 INT64_C(100)
#  define POW10_3 INT64_C(1000)
#  define POW10_4 INT64_C(10000)
#  define POW10_6 INT64_C(1000000)
#  define POW10_7 INT64_C(10000000)
#  define POW10_9 INT64_C(1000000000)
  
#  define CLOCK_REALTIME           1
#  define CLOCK_MONOTONIC          2
#  define CLOCK_PROCESS_CPUTIME_ID 3
#  define CLOCK_THREAD_CPUTIME_ID  4

  typedef int clockid_t;
  
  struct timespec {
    time_t tv_sec;
    long   tv_nsec;
  };
#endif // #if defined(_WIN32)
  
  // variables, internal
  
  // functions, internal

#if defined(_WIN32)
  // http://code.google.com/p/libpthread/source/browse/
  
  int
  set_errno(int a)
  {
    int result(0);
    
    if (0 != a) {
      errno  = a;
      result = -1;
    }
    
    return result;
  }
  
  int
  clock_getres(clockid_t clock_id, struct timespec* res)
  {
    static __int64 hpet_frequency = -1;
    static long    time_increment = -1;
    
    if (-1 == hpet_frequency) {
      {
        DWORD timeAdjustment;
        DWORD timeIncrement;
        BOOL  isTimeAdjustmentDisabled;

        ::GetSystemTimeAdjustment(&timeAdjustment, &timeIncrement, &isTimeAdjustmentDisabled);

        time_increment = timeIncrement * 100;
      }
      
      {
        LARGE_INTEGER pf;
        
        if (0 != ::QueryPerformanceFrequency(&pf)) {
          hpet_frequency = pf.QuadPart;
        } else {
          hpet_frequency = 0;
        }
      }
    }
    
    int result(0);
    
    if (clock_id == CLOCK_MONOTONIC) {
      if (hpet_frequency < 1000) {
        result = set_errno(EINVAL);
      } else {
        res->tv_sec  = 0;
        res->tv_nsec = (int)((POW10_9 + (hpet_frequency >> 1)) / hpet_frequency);
        
        if (1 > res->tv_nsec) {
          res->tv_nsec = 1;
        }
      }
    } else { /* CLOCK_REALTIME, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID */
      res->tv_sec  = time_increment / POW10_7;
      res->tv_nsec = ((int)(time_increment % POW10_7)) * POW10_2;
    }

    return result;
  }
  
  int
  clock_gettime(clockid_t clock_id, struct timespec *tp)
  {
    static __int64 hpet_frequency = -1;
    
    if (-1 == hpet_frequency) {
      LARGE_INTEGER pf;
      
      if (0 != ::QueryPerformanceFrequency(&pf)) {
        hpet_frequency = pf.QuadPart;
      } else {
        hpet_frequency = 0;
      }
    }

    int     result(0);
    __int64 t;

    switch (clock_id) {
    case CLOCK_REALTIME:
      {
        FILETIME ft;
        
        ::GetSystemTimeAsFileTime(&ft);
        
        t = (((__int64) ft.dwHighDateTime) << 32 | ft.dwLowDateTime) - DELTA_EPOCH_IN_100NS;
        
        tp->tv_sec  = t / POW10_7;
        tp->tv_nsec = ((int)(t % POW10_7)) * 100;
      }
      break;

    case CLOCK_MONOTONIC:
      {
        LARGE_INTEGER performanceCount;

        if ((hpet_frequency < 1000) || (0 == ::QueryPerformanceCounter(&performanceCount))) {
          result = set_errno(EINVAL);
        } else {
          tp->tv_sec  = performanceCount.QuadPart / hpet_frequency;
          tp->tv_nsec = (int)((performanceCount.QuadPart % hpet_frequency +
                               (hpet_frequency >> 1)) * POW10_9 / hpet_frequency);
          
          if (tp->tv_nsec >= POW10_9) {
            ++(tp->tv_sec);
            tp->tv_nsec -= POW10_9;
          }
        }
      }
      break;

    case CLOCK_PROCESS_CPUTIME_ID:
    case CLOCK_THREAD_CPUTIME_ID:
      {
        FILETIME ct, et, kt, ut;
        int      got_time(0);

        switch (clock_id) {
        case CLOCK_PROCESS_CPUTIME_ID:
          got_time = ::GetProcessTimes(GetCurrentProcess(), &ct, &et, &kt, &ut);
          break;
          
        case CLOCK_THREAD_CPUTIME_ID:
          got_time = ::GetThreadTimes(GetCurrentThread(), &ct, &et, &kt, &ut);
          break;
          
        default:
          // to keep MSVC quiet at /W4 (C4701: potentially uninitialized local variable 'ut'/'kt')
          got_time = ::GetProcessTimes(GetCurrentProcess(), &ct, &et, &kt, &ut);
          break;
        }
        
        if(0 == got_time) {
          result = set_errno(EINVAL);
        } else {
          t = ((((__int64)kt.dwHighDateTime) << 32 | kt.dwLowDateTime) +
               (((__int64)ut.dwHighDateTime) << 32 | ut.dwLowDateTime));
          tp->tv_sec = t / POW10_7;
          tp->tv_nsec = ((int)(t % POW10_7)) * 100;
        }
      }
      break;

    default:
      result = set_errno(EINVAL);
      break;
    }

    return result;
  }
#endif // #if defined(_WIN32)
  
  void
  normalize(timespec& a)
  {
    static unsigned const tv_nsec_max(999999999);
    
    while (tv_nsec_max > a.tv_nsec) {
      a.tv_sec  -= 1;
      a.tv_nsec += tv_nsec_max + 1;
    }

    while (tv_nsec_max < a.tv_nsec) {
      a.tv_sec  += 1;
      a.tv_nsec -= tv_nsec_max + 1;
    }

    if      ((1 <= a.tv_sec) && (0 > a.tv_nsec)) {
      a.tv_sec  -= 1;
      a.tv_nsec += tv_nsec_max + 1;
    }
    
    else if ((0 > a.tv_sec) && (0 < a.tv_nsec)) {
      a.tv_sec  += 1;
      a.tv_nsec -= tv_nsec_max + 1;
    }
  }

  support::clock::duration
  clock_resolution()
  {
    timespec res = { 0, 0 };

    clock_getres(CLOCK_MONOTONIC, &res);

    normalize(res);
    
    return std::chrono::nanoseconds(res.tv_nsec);
  }
  
} // namespace {

namespace support {
  
  // variables, exported

  /* static */ bool const            clock::is_monotonic(true);
  /* static */ clock::duration const clock::resolution  (clock_resolution());
  
  // functions, exported

  /* static */ clock::time_point
  clock::now() throw()
  {
    timespec now = { 0, 0 };

    ::clock_gettime(CLOCK_MONOTONIC, &now);
    
    return time_point(std::chrono::seconds    (now.tv_sec) +
                      std::chrono::nanoseconds(now.tv_nsec));
  }
  
  /* explicit */
  timer::timer()
    : boost::noncopyable(),
      start_            (clock::now())
  {}
  
  timer::~timer()
  {}

  timer::time_point
  timer::reset()
  {
    return start_ = clock::now();
  }
  
  timer::duration
  timer::lapse() const
  {
    return clock::now() - start_;
  }
  
  void
  sleep(clock::duration const& a)
  {
#if defined(_WIN32)
    {
      timer           t1;
      timer           t2;
      clock::duration d(a);
      
      do { 
        support::this_thread::sleep_for(d);
        
        d -= t2.lapse();
        t2.reset();
      } while (t1.lapse() < a);
    }
#else
    {
      using std::chrono::duration_cast;
      using std::chrono::nanoseconds;
      
      timespec request = { 0,
                           static_cast<long int>(duration_cast<nanoseconds>(a).count()) };

      normalize(request);
      
      timespec remain { 0, 0 };
      
      while (0 != ::clock_nanosleep(CLOCK_MONOTONIC, 0, &request, &remain)) {
        request = remain;
      }
    }
#endif // #if defined(_WIN32)
  }
  
  std::string
  date_time_iso8601()
  {
    std::locale::global(std::locale()); // "C" locale
    
    std::time_t const  tme(std::time(nullptr));
    char               buf[32];
    std::size_t        len(0);
    std::string        result("YYYYMMDDTHHMMSS");
    
    // "%Y%m%dT%H%M%S" -> "yyyymmddThhmmss\0"
    // on windows '%Z' does not work correctly, so we leave it out here
    if (0 != (len = std::strftime(buf, sizeof(buf), "%Y%m%dT%H%M%S", std::localtime(&tme)))) {
      result = std::string(buf, buf + len);
    }

    return result;
  }
  
  namespace {

    clock::time_point const null(clock::now().time_since_epoch());
    
  }
  
  std::ostream&
  operator<<(std::ostream& os, clock::time_point const& a)
  {
    std::ostream::sentry const cerberus(os);
    
    if (cerberus) {
      os << std::chrono::duration_fmt(std::chrono::symbol) << (a - null);
    }
    
    return os;
  }
  
} // namespace support {
