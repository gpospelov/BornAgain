#!/usr/bin/env bash

export PATH=/usr/local/bin:/usr/local/opt/qt5/bin/:$PATH
rm -r -f /Users/vagrant/build; mkdir -p /Users/vagrant/build; cd /Users/vagrant/build;

git clone git://apps.jcns.fz-juelich.de/BornAgain.git
mkdir BornAgain-build
cd BornAgain-build
cmake -DBORNAGAIN_APPLE_BUNDLE=ON ../BornAgain
make -j4
cpack
cp *.dmg /vagrant/.
