# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

SET(_atb_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include")

SET(_atb_LIBRARY_SEARCH_DIRS
    "/usr/lib"
    "/usr/local/lib")

SET(_atb_ENV_ROOT_DIR "$ENV{ATB_ROOT_DIR}")

IF(NOT ATB_ROOT_DIR AND _atb_ENV_ROOT_DIR)
  SET(ATB_ROOT_DIR "${_atb_ENV_ROOT_DIR}")
ENDIF(NOT ATB_ROOT_DIR AND _atb_ENV_ROOT_DIR)

IF(ATB_ROOT_DIR)
  SET(_atb_HEADER_SEARCH_DIRS "${ATB_ROOT_DIR}"
                                      "${ATB_ROOT_DIR}/include"
				      ${_atb_HEADER_SEARCH_DIRS})
  SET(_atb_LIBRARY_SEARCH_DIRS "${ATB_ROOT_DIR}"
                                       "${ATB_ROOT_DIR}/lib"
				       "${ATB_ROOT_DIR}/bin"
			               ${_atb_LIBRARY_SEARCH_DIRS})
ENDIF(ATB_ROOT_DIR)

FIND_PATH(ATB_INCLUDE_DIR "AntTweakBar.h"
          PATHS ${_atb_HEADER_SEARCH_DIRS}
	  DOC "The directory where AntTweakBar.h resides")

IF(WIN64)
  SET(_atb_LIBRARY_NAME AntTweakBar64)
ELSE()
  SET(_atb_LIBRARY_NAME AntTweakBar)
ENDIF()

FIND_LIBRARY(ATB_LIBRARY
             NAMES ${_atb_LIBRARY_NAME}
	     PATHS ${_atb_LIBRARY_SEARCH_DIRS}
	     DOC "The AntTweakBar library")

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(ATB DEFAULT_MSG ATB_INCLUDE_DIR ATB_LIBRARY)

IF(ATB_FOUND AND VERBOSE)
  MESSAGE(STATUS "ATB_INCLUDE_DIR = ${ATB_INCLUDE_DIR}")
  MESSAGE(STATUS "ATB_LIBRARY     = ${ATB_LIBRARY}")
ENDIF(ATB_FOUND AND VERBOSE)
