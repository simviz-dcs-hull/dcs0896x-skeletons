# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

# sub directories, relative to CMAKE_BINARY_DIR or CMAKE_INSTALL_PREFIX
# depending on if they are used during build or install
SET(DCS0896X_CPACK_DIRECTORY   cpack)
SET(DCS0896X_RUNTIME_DIRECTORY bin)

IF(WIN32 OR WIN64)
  SET(DCS0896X_LIBRARY_DIRECTORY bin)
ELSE()
  SET(DCS0896X_LIBRARY_DIRECTORY lib)
ENDIF()

SET(DCS0896X_HEADER_DIRECTORY  include)
SET(DCS0896X_SHARE_DIRECTORY   share)
SET(DCS0896X_DOC_DIRECTORY     ${DCS0896X_SHARE_DIRECTORY}/doc)
SET(DCS0896X_EXTRA_DIRECTORY   ${DCS0896X_SHARE_DIRECTORY}/extra)
SET(DCS0896X_SHADER_DIRECTORY  ${DCS0896X_SHARE_DIRECTORY}/shader)

# output directories, overwrite
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${DCS0896X_LIBRARY_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${DCS0896X_LIBRARY_DIRECTORY})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${DCS0896X_RUNTIME_DIRECTORY})

# output directories, project specific
SET(CMAKE_DOC_OUTPUT_DIRECTORY     ${CMAKE_BINARY_DIR}/${DCS0896X_DOC_DIRECTORY})
SET(CMAKE_EXTRA_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/${DCS0896X_EXTRA_DIRECTORY})
SET(CMAKE_SHADER_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/${DCS0896X_SHADER_DIRECTORY})
