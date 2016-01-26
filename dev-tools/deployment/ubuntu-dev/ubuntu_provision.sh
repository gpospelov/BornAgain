#!/usr/bin/env bash

apt-get update
apt-get install -f -y build-essential git cmake libgsl0-dev libboost-all-dev libfftw3-dev python-dev python-numpy python-matplotlib
apt-get install -f -y qt5-default libqt5designercomponents5 qttools5-dev qtscript5-dev
