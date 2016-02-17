#!/bin/bash

INCLUDE_PREFIX=../../../

swig3.0 -c++ -python -I/usr/include/python2.7\
	-I$INCLUDE_PREFIX/Core/Algorithms/inc\
	-I$INCLUDE_PREFIX/Core/Tools/inc\
	-I$INCLUDE_PREFIX/Core/FormFactors/inc\
	-I$INCLUDE_PREFIX/Fit/FitKernel/inc\
	-I$INCLUDE_PREFIX/Fit/StandardFits\
	-I/usr/include/eigen3 libBornAgainFit.i

mv libBornAgainFit_wrap.cxx libBornAgainFit_wrap.cpp

sed -i 's/_libBornAgainFit.ICloneable_transferToCPP(self)/self.__disown__()/g' libBornAgainCore.py

mv libBornAgainFit_wrap.cpp $INCLUDE_PREFIX/Fit/PythonAPI/src/
mv libBornAgainFit_wrap.h $INCLUDE_PREFIX/Fit/PythonAPI/inc/
