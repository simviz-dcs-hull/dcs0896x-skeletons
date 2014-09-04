# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

SET(ARCH "unknown")

IF(UNIX)
  EXECUTE_PROCESS(COMMAND uname -m OUTPUT_VARIABLE ARCH OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDIF()

# 32-bit vs. 64-bit platform
# unfortunatly, M$ are completely inconsistent in how they name directories (e.g., x64 vs. amd64),
# which is why no architecture variable is set here as well
IF(MSVC AND CMAKE_CL_64)
  MESSAGE(STATUS "Enabling settings for WIN64")
  SET(WIN64 1)
ELSE()
  SET(WIN64 0)
ENDIF()

IF(WIN32 OR WIN64)
  SET(ARCH x86)
  IF(WIN64)
    SET(ARCH x64)
  ENDIF()
ENDIF()

# Boost
SET(BOOST_MINIMUM_VERSION "1.53.0")

# defaults
IF(UNIX)
  # install: DESTDIR + CMAKE_INSTALL_PREFIX (CMAKE_INSTALL_PREFIX must be absolute!)
  STRING(TOLOWER ${CMAKE_PROJECT_NAME} PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")

  # GLM
  SET(GLM_INCLUDE_DIR "~/Projects/others/glm-regnirpsj-git")

  # GLI
  SET(GLI_INCLUDE_DIR "~/Projects/others/gli-regnirpsj-git")
ENDIF()

IF(WIN32 OR WIN64)
  # install: CMAKE_INSTALL_PREFIX
  STRING(TOLOWER ${CMAKE_PROJECT_NAME} PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Tools/${PREFIX}")

  # AntTweakBar
  SET(ATB_ROOT_DIR "C:/Tools/anttweakbar/1.16")

  # Boost
  SET(BOOST_ROOT "C:/Tools/boost/1.54.0")
  IF(WIN64)
    SET(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib64")
  ELSE()
    SET(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib32")
  ENDIF()
  IF(NOT EXISTS "${BOOST_LIBRARYDIR}" OR NOT IS_DIRECTORY "${BOOST_LIBRARYDIR}")
    UNSET(BOOST_LIBRARYDIR)
  ENDIF()

  # GLM
  SET(GLM_INCLUDE_DIR "C:/Tools/glm/regnirpsj-git")

  # GLI
  SET(GLI_INCLUDE_DIR "C:/Tools/gli/regnirpsj-git")
ENDIF()

IF(DCS0896X_TRACE_ALL)
  ADD_DEFINITIONS("-DUKACHULLDCS_ALL_TRACE")
ENDIF()

IF(TRUE OR VERBOSE)
  MESSAGE(STATUS "Project ${CMAKE_PROJECT_NAME} defaults:\n"
    "   ARCH                  = ${ARCH}\n"
    "   CMAKE_INSTALL_PREFIX  = ${CMAKE_INSTALL_PREFIX}\n"
    "   ATB_ROOT_DIR          = ${ATB_ROOT_DIR}\n"
    "   BOOST_MINIMUM_VERSION = ${BOOST_MINIMUM_VERSION}\n"
    "   BOOST_ROOT            = ${BOOST_ROOT}\n"
    "   GLM_INCLUDE_DIR       = ${GLM_INCLUDE_DIR}\n"
    "   GLI_INCLUDE_DIR       = ${GLI_INCLUDE_DIR}\n"
    "   DCS0896X_TRACE_ALL    = ${DCS0896X_TRACE_ALL}")
ENDIF()
