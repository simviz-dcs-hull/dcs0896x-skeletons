# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

SET(_oglplus_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include")

SET(_oglplus_ENV_ROOT_DIR "$ENV{OGLplus_ROOT_DIR}")

IF(NOT OGLplus_ROOT_DIR AND _oglplus_ENV_ROOT_DIR)
  SET(OGLplus_ROOT_DIR "${_oglplus_ENV_ROOT_DIR}")
ENDIF()

IF(OGLplus_ROOT_DIR)
  SET(_oglplus_HEADER_SEARCH_DIRS "${OGLplus_ROOT_DIR}"
                              "${OGLplus_ROOT_DIR}/include"
			      "${OGLplus_ROOT_DIR}/implement"
                              ${_oglplus_HEADER_SEARCH_DIRS})
ENDIF()

# non-installed build-only locations will have .hpp/.ipp files in different directories;
# in case of an installed location, i.e. .hpp/.ipp in the same place, the following
# 'LIST(REMOVE_DUPLICATES ...)' takes care of dublicate
FIND_PATH(OGLplus_HPP_DIR "oglplus/buffer.hpp"
          PATHS ${_oglplus_HEADER_SEARCH_DIRS}
	  DOC "The directory where oglplus/buffer.hpp resides")

FIND_PATH(OGLplus_IPP_DIR "oglplus/buffer.ipp"
          PATHS ${_oglplus_HEADER_SEARCH_DIRS}
	  DOC "The directory where oglplus/buffer.ipp resides")

SET(OGLplus_INCLUDE_DIRS "${OGLplus_HPP_DIR};${OGLplus_IPP_DIR}")
LIST(REMOVE_DUPLICATES OGLplus_INCLUDE_DIRS)

INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(OGLplus DEFAULT_MSG OGLplus_INCLUDE_DIRS)

IF(OGLplus_FOUND AND VERBOSE)
  MESSAGE(STATUS "OGLplus_INCLUDE_DIRS = ${OGLplus_INCLUDE_DIRS}")
ENDIF()
