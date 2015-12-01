#!/usr/bin/env bash

export PATH=/usr/local/bin:/usr/local/opt/qt5/bin/:$PATH
rm -r -f ~/build; mkdir -p build; cd ~/build;

git clone git://apps.jcns.fz-juelich.de/BornAgain.git
mkdir BornAgain-build
cd BornAgain-build
cmake ../BornAgain
make -j4
