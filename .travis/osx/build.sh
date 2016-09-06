export PATH=/usr/local/opt/qt5/bin/:$PATH
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=/usr/local/opt/llvm37/bin/clang-3.7 -DCMAKE_CXX_COMPILER=/usr/local/opt/llvm37/bin/clang++-3.7 -DCMAKE_PREFIX_PATH=/usr/local -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
make -j4
