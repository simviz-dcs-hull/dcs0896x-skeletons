# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

IF(WIN32)
  ADD_SUBDIRECTORY(d3d)
  ADD_SUBDIRECTORY(win)
ENDIF()

ADD_SUBDIRECTORY(support)
