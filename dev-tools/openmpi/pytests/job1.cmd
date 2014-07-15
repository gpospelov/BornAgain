#!/bin/bash
#
#@ job_type = parallel
#@ class = test
#@ node = 2
#@ total_tasks=32
#@ wall_clock_limit = 0:20:00
#@ job_name = mytest
#@ network.MPI = sn_all,not_shared,us
#@ initialdir = $(home)/development/BornAgain/source/dev-tools/openmpi/pytests
#@ output = job$(jobid).out
#@ error = job$(jobid).err
#@ notification=always
#@ queue
. /etc/profile
. /etc/profile.d/modules.sh
export LD_LIBRARY_PATH=/home/hpc/pr87me/di29sok/software/boost_1_55_0.gcc47/lib:/home/hpc/pr87me/di29sok/development/BornAgain/installed/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/hpc/pr87me/di29sok/development/BornAgain/installed/lib:$PYTHONPATH
module load python/2.7_anaconda
poe python ompi_meso_cpp.py

