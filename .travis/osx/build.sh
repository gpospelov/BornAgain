export PATH=/usr/local/opt/qt5/bin/:$PATH
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=$BUILD_TYPE ..
make -j9
