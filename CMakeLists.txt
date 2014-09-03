# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4 FATAL_ERROR)

PROJECT(DCS0896X)

# disallow in-source build
IF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  MESSAGE(FATAL_ERROR
    "\n"
    "This project requires an out-of-source build.\n"
    "Please create a separate build directory and run CMake there.\n"
    "Consult README.build for command-line examples.")
ENDIF()

IF("" STREQUAL "${CMAKE_BUILD_TYPE}")
  SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF()

MESSAGE(STATUS "CMAKE_BUILD_TYPE set to '" ${CMAKE_BUILD_TYPE} "'")

# initial cache to make life easier on window$ (if we ever get there ;)
IF(NOT DCS0896XINITCACHELOADED AND EXISTS ${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  INCLUDE(${CMAKE_SOURCE_DIR}/CMakeCacheInitial.txt)
  SET(DCS0896XINITCACHELOADED TRUE CACHE INTERNAL "")
ENDIF()

# globally visible functions/modules/variables
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
INCLUDE(SetupProjectOptions)
INCLUDE(SetupFunctions)
INCLUDE(SetupWindowsSDK)
INCLUDE(SetupProjectPaths)
INCLUDE(SetupProjectVariables)
INCLUDE(SetupCompilerPre)

# see [http://athile.net/library/blog/?p=288]
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# testing
IF(DCS0896X_BLD_UTEST)
  MESSAGE(STATUS "Enabling unit-test building")

  IF(DCS0896X_RUN_CTEST)
    ENABLE_TESTING()
    CONFIGURE_FILE(cmake/SetupTestConfig.cmake ${CMAKE_BINARY_DIR}/CTestConfig.cmake COPYONLY)
    MESSAGE(STATUS "Enabling CTest unit-test execution")
  ELSEIF(DCS0896X_RUN_UTEST)
    MESSAGE(STATUS "Enabling unit-test execution")
  ELSE()
    MESSAGE(STATUS "Disabling unit-test execution")
  ENDIF()

  ADD_CUSTOM_TARGET(check)
  SET_PROPERTY(TARGET check PROPERTY FOLDER "Tests")
  ADD_DEPENDENCIES(check test_all)
ELSE()
  MESSAGE(STATUS "Disabling unit-test building")
ENDIF()

# globally added include directories (-I); keep ordering
# 1. project
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/inc)

# 2. BOOST
FIND_PACKAGE(Boost ${BOOST_MINIMUM_VERSION} REQUIRED)

# 3. GLM
FIND_PACKAGE(GLM REQUIRED)

# 4. GLI
FIND_PACKAGE(GLI REQUIRED)

# 5. AntTweakBar (hdr/lib not globally available though)
FIND_PACKAGE(ATB REQUIRED)

INCLUDE(SetupCompilerPost)

# traverse these sub dirs
ADD_SUBDIRECTORY(doc)
ADD_SUBDIRECTORY(src)

ADD_CUSTOM_TARGET(ALL_BUILD)
SET_PROPERTY(TARGET ALL_BUILD PROPERTY FOLDER "CMakePredefinedTargets")

IF(VERBOSE)
  INCLUDE(FeatureSummary)
  FEATURE_SUMMARY(WHAT ALL)
ENDIF()

# keep last
INCLUDE(SetupPackaging)
