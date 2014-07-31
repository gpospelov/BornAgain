import os
import sys
from common import *




def check_tarball():
    print "Checking tarball ..."
    cmd = "cd %s; wget http://apps.jcns.fz-juelich.de/src/BornAgain/BornAgain-%s.tar.gz" % (get_checktarball_dir(), get_version())
    print cmd
    cmd = "cd %s; tar zxf BornAgain-%s.tar.gz" % (get_checktarball_dir(), get_version())
    print cmd
    cmd = "cd %s; mkdir build; mkdir installed" % get_checktarball_dir()
    print cmd
    cmd = "cd %s/build; cmake -DCMAKE_INSTALL_PREFIX=../installed ../BornAgain-%s; make -j8; make check; make install" % (get_checktarball_dir(), get_version())
    print cmd
    cmd = "cd %s/installed; source bin/thisbornagain.sh; python -c \"from libBornAgainCore import *; print GetVersionNumber()\"" % (get_checktarball_dir())
    print cmd

def check_release():
    print "Checking release"
    check_tarball()


