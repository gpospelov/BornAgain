import os
import sys
import platform
import shutil
import subprocess
import glob

BUNDLE_DIR = ""

# -----------------------------------------------------------------------------
# Locations
# -----------------------------------------------------------------------------


def set_bundle_dir(bundle_dir):
    global BUNDLE_DIR
    BUNDLE_DIR = bundle_dir
    if os.path.exists(bundle_frameworks_path()):
        shutil.rmtree(bundle_frameworks_path())


def bundle_dir():
    global BUNDLE_DIR
    return BUNDLE_DIR


def bundle_frameworks_path():
    return os.path.join(bundle_dir(), "Contents", "Frameworks")


def bundle_plugins_path():
    return os.path.join(bundle_dir(), "Contents", "PlugIns")


def bundle_main_executable():
    return os.path.join(bundle_dir(), "Contents", "MacOS", "BornAgain")


def qtlibs_path():
    return os.path.join(os.environ['QTDIR'], "lib")


def qtplugins_path():
    return os.path.join(os.environ['QTDIR'], "plugins")


def bornagain_binaries():
    result = glob.glob(os.path.join(bundle_dir(), "Contents","lib","BornAgain-*","*"))
    result.append(bundle_main_executable())
    return result


# -----------------------------------------------------------------------------
# Utils
# -----------------------------------------------------------------------------


def make_dir(dirname):
    if not os.path.exists(dirname):
        os.makedirs(dirname)


def copy_file(file_name, dest_dir):
    """
    Copies file to the destination directory. If destination doesn't exists, it will be created.
    """
    make_dir(dest_dir)
    shutil.copyfile(file_name, os.path.join(dest_dir, os.path.basename(file_name)))


def otool(filename):
    p = subprocess.Popen(['otool', '-XL', filename], stdout=subprocess.PIPE)
    return iter(p.stdout.readline, b'')


def setId(filename, newId):
    p = subprocess.Popen(['install_name_tool', '-id', newId, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def setDependency(filename, old, new):
    p = subprocess.Popen(['install_name_tool', '-change', old, new, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def analyse_dependency(dependency_string):
    """
    Analyse dependency line obtained from 'otool' command. Returns library full path file name
    if it is a real third party dependency. Returns None if it is system file or rpath link.
    """
    file_name = dependency_string.strip().split()[0]
    if not os.path.exists(file_name):
        return None
    non_dependency_patterns = ['@', '/usr/lib', '/System']
    for pat in non_dependency_patterns:
        if file_name.startswith(pat):
            return None
    return file_name


# -----------------------------------------------------------------------------
# Actions
# -----------------------------------------------------------------------------

def copy_qt_libraries():
    print "--> Copying Qt libraries"
    libs = ['QtCore', 'QtDBus', 'QtDesigner', 'QtGui', 'QtPrintSupport', 'QtWidgets', 'QtXml', 'QtSvg']
    for libname in libs:
        libpath = os.path.join(libname+".framework", "Versions", "5")
        srcfile = os.path.join(qtlibs_path(), libpath, libname)
        dstdir = os.path.join(bundle_frameworks_path(), libpath)
        copy_file(srcfile, dstdir)


def copy_qt_plugins():
    print "--> Copying Qt plugins"
    plugins = ['platforms/libqcocoa.dylib', 'iconengines/libqsvgicon.dylib']
    for name in plugins:
        srcfile = os.path.join(qtplugins_path(), name)
        dstdir = os.path.join(bundle_plugins_path(), os.path.dirname(name))
        copy_file(srcfile, dstdir)


def process_dependency(dependency):
    """
    Copies external dependency library into Frameworks directory (if it is not already there)
    and sets corresponding library Id for it. Returns library Id and new location to the user.
    """
    libname = os.path.basename(dependency)
    libId = "@rpath/" + libname
    new_location = os.path.join(bundle_frameworks_path(), libname)
    if os.path.exists(new_location):
        print "skipping dependency", dependency
        return libId, None
    print "copying dependency", dependency
    copy_file(dependency, bundle_frameworks_path())
    setId(new_location, libId)
    return libId, new_location


def get_file_dependencies(file_name, dependency_list = None):
    for line in otool(file_name):
        dependency = analyse_dependency(line)
        if dependency:
            libId, new_location = process_dependency(dependency)
            setDependency(file_name, dependency, libId)
            if new_location:
                get_file_dependencies(new_location)

            # print "         dependency:", file_name, dependency, os.path.basename(dependency)
            # dependency_list.append(dependency)
            # get_file_dependencies(dependency, dependency_list)


def copy_dependencies():
    print "--> collecting dependencies"
    for bin in iter(bornagain_binaries()):
        get_file_dependencies(bin)


def fix_apple_bundle():
    copy_qt_libraries()
    copy_qt_plugins()
    copy_dependencies()


if __name__ == '__main__':
    if not platform.system() == 'Darwin':
        exit("This script is intended for MacOs systems. Exiting...")

    if len(sys.argv) != 2:
        exit("Please specify bundle location")

    set_bundle_dir(sys.argv[1])

    fix_apple_bundle()
