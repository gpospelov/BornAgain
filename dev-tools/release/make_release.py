#!/usr/bin/env python

import sys
import os
import subprocess


def run_process(command, working_directory):
    p = subprocess.Popen(command, cwd=working_directory, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
    if p.returncode:
        for line in iter(p.stderr.readline, b''):
            print line
        exit("Error while running the command '"+" ".join(command)+"'")
    return not p.returncode


def git_clone(branch_name, working_directory):
    print "Cloning BornAgain repository ... ",
    cmd = ['git', 'clone', 'git@apps.jcns.fz-juelich.de:BornAgain.git']
    run_process(cmd, working_directory)
    print " OK."
    cmd = ['git', 'checkout', branch_name]
    print "XXX", cmd, working_directory
    run_process(cmd, working_directory)


def parse_release_name(release_branch_name):
    name, version = release_branch_name.split("-")
    version_major, version_minor, version_patch = version.split(".")
    print version_major, version_minor, version_patch
    return version_major, version_minor, version_patch


def prepare_release(release_branch_name, release_working_directory):
    print "Preparing release working directory '%s'." % release_working_directory
    # making directories
    os.makedirs(release_working_directory)
    os.makedirs(release_working_directory+"/build")
    os.makedirs(release_working_directory+"/upload")

    # cloning git
    #git_clone(release_branch_name, release_working_directory)
    git_clone("develop", release_working_directory)



def main():
    if len(sys.argv) != 2:
        print "Please specify the name of the release branch."
        print "Usage: python make_release.py release-0.9.3"
        exit()

    release_branch_name = sys.argv[1]

    release_working_directory = os.getcwd() + "/" + release_branch_name

    if os.path.exists(release_working_directory):
        print "Directory %s exists, continuing release process." % release_working_directory
    else:
        prepare_release(release_branch_name, release_working_directory)




if __name__ == '__main__':
    main()
