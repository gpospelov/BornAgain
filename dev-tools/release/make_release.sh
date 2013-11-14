#!/bin/bash 
# Main script to start release preparation

set -e

mkdir BornAgain-release
cd BornAgain-release

git clone git://apps.jcns.fz-juelich.de/BornAgain.git
cd BornAgain
git checkout develop

cd ..
mkdir build
cd build

cmake ../BornAgain

./bin/release.sh

cd BornAgain-release/build/RELEASE
