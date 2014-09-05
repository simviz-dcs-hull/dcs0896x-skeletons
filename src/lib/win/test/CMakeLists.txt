# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

MESSAGE(STATUS "Setting up: ${CMAKE_CURRENT_SOURCE_DIR}")

FIND_PACKAGE(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS unit_test_framework)

SET(SRC)
LIST(APPEND SRC "application.cpp")

SET(LIBS)
LIST(APPEND LIBS ${LIB})
LIST(APPEND LIBS ${Boost_LIBRARIES})

TEST_SETUP(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})
