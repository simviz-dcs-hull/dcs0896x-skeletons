===============
dcs08961 README
===============

:Author: Jan P Springer <regnirpsj@gmail.com>
:Author: Warren J. Viant <wjviant@googlemail.com>

.. contents::

.. _OpenGL: http://opengl.org/
.. _OGLplus: http://oglplus.org/
.. _CMake: http://www.cmake.org/
.. _Doxygen: http://www.doxygen.org/

Introduction
============

``dcs0896x-skeletons`` is an infrastructure project to support the ``08960 C++ Programming and Design`` and ``08961 Real-Time Graphics`` modules at the ``Department of Computer Science, University of Hull``.

Building and Installation
=========================

Quick Setup
-----------

::

 # clone project
 $> git clone <project-url-for-cloning>
 # creates ./<project-dir>
 
 # linux
 $> cd <project-dir>
 $> mkdir build && cd build
 $> cmake ..
 $> make -j4
 $> make -j4 test_all

 # windows
 $> cd <project-dir>
 $> mkdir build && cd build
 $> cmake ..
 $> msbuild.exe DCS08961.sln /nologo /v:q /m:4
 $> msbuild.exe DCS08961.sln /nologo /v:q /m:4 /t:"Tests\test_all"

Overview
--------

[to be written]

Requirements
------------

[to be written]

Acknowledgements
================

[to be written]

License
=======

Copyright 2014  University of Hull. Distributed under the LGPLv2.1 (see the accompanying file LICENSE).
