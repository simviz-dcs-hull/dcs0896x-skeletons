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
LIST(APPEND SRC "utilities.cpp")

LIST(APPEND SRC "window/manager.cpp")

SET(LIBS)

LIST(APPEND LIBS support)

LIBRARY_SETUP(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})

ADD_SUBDIRECTORY(test EXCLUDE_FROM_ALL)
