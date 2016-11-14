#!/usr/bin/env bash


export QTDIR=/usr/local/opt/qt5
export PATH=/usr/local/bin:$QTDIR/bin/:$PATH
export WORKDIR=/Users/vagrant/build
rm -r -f $WORKDIR; mkdir -p $WORKDIR; cd $WORKDIR;

#git clone -b develop https://github.com/scgmlz/BornAgain.git
#git clone -b release-1.7.0 https://github.com/waltervh/BornAgain.git
git clone -b DmgInstaller https://github.com/gpospelov/BornAgain.git

mkdir BornAgain-build
cd BornAgain-build
export ANACONDA=/Users/vagrant/anaconda2
cmake -DCMAKE_C_COMPILER=/usr/local/opt/llvm36/bin/clang-3.6 -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm36/bin/clang++-3.6  -DPYTHON_LIBRARY=$ANACONDA/lib/libpython2.7.dylib -DPYTHON_EXECUTABLE=$ANACONDA/bin/python2.7 -DBORNAGAIN_APPLE_BUNDLE=ON -DCMAKE_PREFIX_PATH=/usr/local ../BornAgain
make -j4
cpack -V

echo 'Copying dmg installer back to build server'
echo 'scp /Users/vagrant/build/BornAgain-build/*.dmg scg@scgmini:./deployment/results/.'
scp /Users/vagrant/build/BornAgain-build/*.dmg scg@scgmini:./deployment/results/.
