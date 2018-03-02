#!/usr/bin/env bash


#export QTDIR=/usr/local/opt/qt5
export QTDIR=/Users/vagrant/Qt/5.10.1/clang_64
export PATH=/usr/local/bin:$QTDIR/bin/:$PATH
export WORKDIR=/Users/vagrant/build
rm -r -f $WORKDIR; mkdir -p $WORKDIR; cd $WORKDIR;

#git clone --recurse-submodules -b develop https://github.com/scgmlz/BornAgain.git
git clone --recurse-submodules -b MacBuild https://github.com/gpospelov/BornAgain.git

# --------------------------------------------------------------------
echo 'Building on Python2'
# --------------------------------------------------------------------

mkdir BornAgain-build-python2
cd BornAgain-build-python2
#export ANACONDA=/Users/vagrant/anaconda2
#cmake -DCMAKE_C_COMPILER=/usr/local/opt/llvm/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm/bin/clang++  -DPYTHON_LIBRARY=$ANACONDA/lib/libpython2.7.dylib -DPYTHON_EXECUTABLE=$ANACONDA/bin/python2.7 -DBORNAGAIN_APPLE_BUNDLE=ON -DCMAKE_PREFIX_PATH=/usr/local ../BornAgain
cmake -DCMAKE_C_COMPILER=/usr/local/opt/llvm/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm/bin/clang++ -DBORNAGAIN_USE_PYTHON3=OFF -DBORNAGAIN_APPLE_BUNDLE=ON -DCMAKE_PREFIX_PATH=/usr/local ../BornAgain
make -j4
cpack -V

echo 'Copying dmg installer back to build server'
echo 'scp /Users/vagrant/build/BornAgain-build-python2/*.dmg scg@scgmini:./deployment/results/.'
scp /Users/vagrant/build/BornAgain-build-python2/*.dmg scg@scgmini:./deployment/results/.

# --------------------------------------------------------------------
echo 'Building on Python3'
# --------------------------------------------------------------------
cd $WORKDIR

mkdir BornAgain-build-python3
cd BornAgain-build-python3
cmake -DCMAKE_C_COMPILER=/usr/local/opt/llvm/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm/bin/clang++ -DBORNAGAIN_USE_PYTHON3=ON -DBORNAGAIN_APPLE_BUNDLE=ON -DCMAKE_PREFIX_PATH=/usr/local ../BornAgain
make -j4
cpack -V

echo 'Copying dmg installer back to build server'
echo 'scp /Users/vagrant/build/BornAgain-build-python3/*.dmg scg@scgmini:./deployment/results/.'
scp /Users/vagrant/build/BornAgain-build-python3/*.dmg scg@scgmini:./deployment/results/.
