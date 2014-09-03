# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

SET(_glm_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include")

SET(_glm_ENV_ROOT_DIR "$ENV{GLM_ROOT_DIR}")

IF(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)
  SET(GLM_ROOT_DIR "${_glm_ENV_ROOT_DIR}")
ENDIF(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)

IF(GLM_ROOT_DIR)
  SET(_glm_HEADER_SEARCH_DIRS "${GLM_ROOT_DIR}"
                              "${GLM_ROOT_DIR}/include"
                              ${_glm_HEADER_SEARCH_DIRS})
ENDIF(GLM_ROOT_DIR)

FIND_PATH(GLM_INCLUDE_DIR "glm/glm.hpp"
          PATHS ${_glm_HEADER_SEARCH_DIRS}
	  DOC "The directory where glm/glm.hpp resides")

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

IF(GLM_FOUND AND VERBOSE)
  MESSAGE(STATUS "GLM_INCLUDE_DIR = ${GLM_INCLUDE_DIR}")
ENDIF(GLM_FOUND AND VERBOSE)
