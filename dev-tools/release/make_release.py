#!/usr/bin/env python

import sys
import os
import subprocess

RELEASE_WORKING_DIRECTORY = ""
RELEASE_BRANCH_NAME = ""

def get_working_dir():
    return RELEASE_WORKING_DIRECTORY


def get_source_dir():
    return get_working_dir()+"/"+"BornAgain"


def get_build_dir():
    return get_working_dir()+"/"+"build"


def get_upload_dir():
    return get_working_dir()+"/"+"upload"


def get_install_dir():
    return get_working_dir()+"/"+"installed"


def get_branch_name():
    return RELEASE_BRANCH_NAME


def run_process(command, working_directory):
    p = subprocess.Popen(command, cwd=working_directory, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
    if p.returncode:
        for line in iter(p.stderr.readline, b''):
            print line
        exit("Error while running the command '"+" ".join(command)+"'")
    return not p.returncode


def make_directories():
    os.makedirs(get_working_dir())
    os.makedirs(get_build_dir())
    os.makedirs(get_upload_dir())
    os.makedirs(get_install_dir())


def git_clone():
    print "Cloning BornAgain repository ... ",
    cmd = ['git', 'clone', 'git@apps.jcns.fz-juelich.de:BornAgain.git']
    run_process(cmd, get_working_dir())
    print " OK."
    cmd = ['git', 'checkout', get_branch_name()]
    run_process(cmd, get_source_dir())


def download_from_app_server():
    print "Downloading from application server ..."
    returncode = os.system("rsync -avzhe ssh apps@apps.jcns.fz-juelich.de:/www/apps/src/BornAgain/ "+get_upload_dir())
    if returncode:
        exit("Error while downloading from application server")


def cmake_release():
    print "Running cmake ...", get_build_dir()
    cmd = ['cd',get_build_dir(), ';', 'cmake -DBORNAGAIN_APP=ON -DBORNAGAIN_MAN=ON -DBORNAGAIN_RELEASE=ON',
           '-DCMAKE_INSTALL_PREFIX', get_install_dir(), get_source_dir()]
    returncode = os.system(" ".join(cmd))
    if returncode:
        exit("Error while running cmake.")


def compile_release():
    print "Compiling ..."
    cmd = ['make --directory', get_build_dir(), '-j8; make check']
    returncode = os.system(" ".join(cmd))
    if returncode:
        exit("Error while compiling the project.")


def measure_performance():
    print "Measuring performance ..."
    perf_txt = get_source_dir()+"/dev-tools/log/perf_history.txt"
    cmd = 'cd ' + get_build_dir() + ';'
    cmd += './bin/App --performance --batch;'
    cmd += 'echo \"#   '+get_branch_name()+'\" >> '+perf_txt+";"
    cmd += 'cat perf_history.txt >> '+perf_txt
    print cmd
    returncode = os.system(cmd)
    if returncode:
        exit("Error while measuring the performance.")



def parse_release_name(release_branch_name):
    name, version = release_branch_name.split("-")
    version_major, version_minor, version_patch = version.split(".")
    print version_major, version_minor, version_patch
    return version_major, version_minor, version_patch


def prepare_release():
    print "Preparing release working directory '%s'." % get_working_dir()

    #make_directories()

    #git_clone()

    #download_from_app_server()

    #cmake_release()

    #compile_release()

    measure_performance()



def main():
    global RELEASE_BRANCH_NAME
    global RELEASE_WORKING_DIRECTORY

    if len(sys.argv) != 2:
        print "Please specify the name of the release branch."
        print "Usage: python make_release.py release-0.9.3"
        exit()

    RELEASE_BRANCH_NAME = sys.argv[1]
    RELEASE_WORKING_DIRECTORY = os.getcwd() + "/" + RELEASE_BRANCH_NAME

    #if os.path.exists(get_working_dir()):
    #    print "Directory %s exists, continuing release process." % get_working_dir()
    #else:
    #    prepare_release()

    prepare_release()



if __name__ == '__main__':
    main()
