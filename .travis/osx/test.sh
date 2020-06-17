cd build
make check && exit 0
cat ./Testing/Temporary/*.log
exit 1
