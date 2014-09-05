# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

# doxygen docs
OPTION(DCS0896X_DOC_DEV "Enable generation of developer documentation" OFF)
OPTION(DCS0896X_DOC_USR "Enable generation of user documentation"      OFF)

# unit testing
OPTION(DCS0896X_BLD_UTEST "Enable unit-test building by default"                          ON)
OPTION(DCS0896X_RUN_CTEST "Enable unit-test execution using CTest by default"            OFF)
OPTION(DCS0896X_RUN_UTEST "Enable unit-test execution using the build system by default" OFF)

# tracing
OPTION(DCS0896X_TRACE_ALL "Enable runtime function tracing for everything!" OFF)

# gcc/clang specific options
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  OPTION(DCS0896X_ADDR_SANITATION  "Enable gcc/clang address sanitation" OFF)
  OPTION(DCS0896X_GLIBCXX_PARALLEL "Enable GLIBCXX parallel mode"        OFF)
  OPTION(DCS0896X_PROFILE          "Enable support for coverage testing" OFF)
ENDIF()

# msvc specific options
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
ENDIF()
