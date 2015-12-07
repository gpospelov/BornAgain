#!/usr/bin/env bash

export PATH=/usr/local/bin:/usr/local/opt/qt5/bin/:$PATH
rm -r -f /Users/vagrant/build; mkdir -p /Users/vagrant/build; cd /Users/vagrant/build;

git clone -b develop git://apps.jcns.fz-juelich.de/BornAgain.git
mkdir BornAgain-build
cd BornAgain-build
export ANACONDA=/Users/vagrant/anaconda2
cmake -DPYTHON_LIBRARY=$ANACONDA/lib/libpython2.7.dylib -DPYTHON_EXECUTABLE=$ANACONDA/bin/python2.7 -DBORNAGAIN_APPLE_BUNDLE=ON -DCMAKE_PREFIX_PATH=/usr/local ../BornAgain
make -j4
cpack -V
#cp *.dmg /vagrant/.
scp *.dmg scg@scgmini:./deployment/results/.

