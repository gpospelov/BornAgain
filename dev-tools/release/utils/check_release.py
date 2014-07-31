import os
import sys
from common import *
import subprocess



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
    cmd = "source %s/installed/bin/thisbornagain.sh; python -c \"from libBornAgainCore import *; print GetVersionNumber()\"" % (get_checktarball_dir())
    print cmd
    #p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    #p.wait()
    #return iter(p.stdout.readline, b''), iter(p.stderr.readline, b'')


def check_manual():
    cmd = "cd %s; wget http://apps.jcns.fz-juelich.de/src/BornAgain/%s" % (get_checkrelease_dir(), get_manual_name())
    print cmd
    if not os.path.exists(get_checkrelease_dir()+"/"+get_manual_name()):
        exit("Error! Can't access user manual")


def check_master_branch():
    print "Checking master branch ..."
    cmd = "cd %s; mkdir build; mkdir installed" % get_checkmaster_dir()
    print cmd
    cmd = "cd %s; git clone git://apps.jcns.fz-juelich.de/BornAgain.git " % get_checkmaster_dir()
    print cmd
    cmd = "cd %s/build; cmake -DCMAKE_INSTALL_PREFIX=../installed ../BornAgain; make -j8; make check; make install" % (get_checkmaster_dir())
    print cmd
    cmd = "source %s/installed/bin/thisbornagain.sh; python -c \"from libBornAgainCore import *; print GetVersionNumber()\"" % (get_checkmaster_dir())
    print cmd


def check_release():
    print "Checking release"
    check_manual()
    check_tarball()
    check_master_branch()



