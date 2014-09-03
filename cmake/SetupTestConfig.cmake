# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2014 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

SET(CTEST_PROJECT_NAME       "DCS0896X")
SET(CTEST_NIGHTLY_START_TIME "01:00:00 EST")
SET(CTEST_DROP_METHOD        "http")
SET(CTEST_DROP_SITE          "www.cdash.org")
SET(CTEST_DROP_LOCATION      "/CDash/submit.php?project=${CTEST_PROJECT_NAME}")
SET(CTEST_DROP_SITE_CDASH    TRUE)
SET(CTEST_USE_LAUNCHERS      0)
