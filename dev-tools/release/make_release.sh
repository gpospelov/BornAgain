#!/bin/bash 
# Main script to start release preparation

set -e




# set -e
# 
# mkdir BornAgain-release
# cd BornAgain-release
# 
# git clone git@apps.jcns.fz-juelich.de:BornAgain.git
# cd BornAgain
# git checkout PreRelease
# 
# cd ..
# mkdir build
# cd build
# 
# cmake ../BornAgain
# 
# ./bin/release.sh
# 
# echo " "
# echo "1) Modify BornAgain-release/build/RELEASE/CHANGELOG"
# echo "2) Copy new Windows build into BornAgain-release/build/RELEASE"
# echo "3) Run BornAgain-release/build/bin/release.sh with menu option #2 (upload on apps)"
# echo "4) Run BornAgain-release/build/bin/release.sh with menu option #3 (finalize git)"
