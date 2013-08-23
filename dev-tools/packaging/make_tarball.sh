

BornAgain="BornAgain-0.9"

echo $BornAgain
echo "copying..."


mkdir $BornAgain

cp -r ../BornAgain/App $BornAgain/.
cp -r ../BornAgain/BornAgain.pro $BornAgain/.
cp -r ../BornAgain/CMakeLists.txt $BornAgain/.
cp -r ../BornAgain/Core $BornAgain/.

mkdir $BornAgain/Doc
cp -r ../BornAgain/Doc/CHANGELOG $BornAgain/Doc/.
cp -r ../BornAgain/Doc/COPYING $BornAgain/Doc/.
cp -r ../BornAgain/Doc/Doxygen $BornAgain/Doc/.

cp -r ../BornAgain/Examples $BornAgain/.
cp -r ../BornAgain/Fit $BornAgain/.

cp -r ../BornAgain/INSTALL $BornAgain/.
cp -r ../BornAgain/README $BornAgain/.
cp -r ../BornAgain/Tests $BornAgain/.
cp -r ../BornAgain/ThirdParty $BornAgain/.

cp -r ../BornAgain/bin $BornAgain/.
cp -r ../BornAgain/cmake $BornAgain/.

mkdir $BornAgain/dev-tools
cp -r ../BornAgain/dev-tools/README $BornAgain/dev-tools/.
cp -r ../BornAgain/dev-tools/git-utils $BornAgain/dev-tools/.
cp -r ../BornAgain/dev-tools/log $BornAgain/dev-tools/.
cp -r ../BornAgain/dev-tools/profiling $BornAgain/dev-tools/.
cp -r ../BornAgain/dev-tools/python-bindings $BornAgain/dev-tools/.

cp -r ../BornAgain/shared.pri $BornAgain/.

find . -name ".o*" | xargs rm -r -f
find . -name ".m*" | xargs rm -r -f
find . -name ".l*" | xargs rm -r -f

# ---------------
echo "making tarball"
rm -f $BornAgain.tgz
tar cfz $BornAgain.tgz $BornAgain
rm -r -f $BornAgain

rm -r -f tmp
mkdir tmp
cd tmp
cp ../$BornAgain.tgz .
tar xfz ../$BornAgain.tgz
mkdir build
mkdir installed

#cd build
#cmake ../BornAgain-0.8.2 -DCMAKE_INSTALL_PREFIX=../installed
