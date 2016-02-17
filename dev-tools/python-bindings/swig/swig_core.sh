#!/bin/bash

INCLUDE_PREFIX=../../../

swig3.0 -c++ -python -I/usr/include/python2.7\
	-I$INCLUDE_PREFIX/Core/Algorithms/inc\
	-I$INCLUDE_PREFIX/Core/FormFactors/inc\
	-I$INCLUDE_PREFIX/Core/Geometry/inc\
	-I$INCLUDE_PREFIX/Core/InputOutput\
	-I$INCLUDE_PREFIX/Core/Samples/inc\
	-I$INCLUDE_PREFIX/Core/StandardSamples\
	-I$INCLUDE_PREFIX/Core/Tools/inc\
	-I/usr/include/eigen3 libBornAgainCore.i

mv libBornAgainCore_wrap.cxx libBornAgainCore_wrap.cpp

sed -i 's/_libBornAgainCore.ICloneable_transferToCPP(self)/self.__disown__()/g' libBornAgainCore.py

mv libBornAgainCore_wrap.cpp $INCLUDE_PREFIX/Core/PythonAPI/src/
mv libBornAgainCore_wrap.h $INCLUDE_PREFIX/Core/PythonAPI/inc/
