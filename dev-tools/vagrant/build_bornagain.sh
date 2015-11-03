#!/usr/bin/env bash

git clone git://apps.jcns.fz-juelich.de/BornAgain.git
mkdir BornAgain-build
cd BornAgain-build
cmake ../BornAgain
make -j4

