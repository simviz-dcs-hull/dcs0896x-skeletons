# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

MESSAGE(STATUS "Setting up: ${CMAKE_CURRENT_SOURCE_DIR}")

SET(LIB "win")

SET(SRC)

LIST(APPEND SRC "application.cpp")

LIBRARY_SETUP(${LIB} SOURCES ${SRC})

ADD_SUBDIRECTORY(test EXCLUDE_FROM_ALL)
