# Setup for BornAgain compilation at SuperMUC LRZ cluster


module load git
module load gcc/4.5
module load boost/1.47_gcc

#export FFTW3=/lrz/sys/libraries/fftw/3.3.3/avx/
export FFTW3=$FFTW_INC
export BOOST_ROOT=$BOOST_BASE

