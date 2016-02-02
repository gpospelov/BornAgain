"""
Script to fix all dependencies in OS X bundle. Runs automatically when -DBORNAGAIN_APPLE_BUNDLE
"""
import os
import sys
import platform
import shutil
import subprocess
import glob
from distutils import sysconfig

BUNDLE_DIR = ""

# -----------------------------------------------------------------------------
# Locations
# -----------------------------------------------------------------------------


def set_bundle_dir(bundle_dir):
    global BUNDLE_DIR
    BUNDLE_DIR = bundle_dir


def bundle_dir():
    global BUNDLE_DIR
    return BUNDLE_DIR


def bundle_frameworks_path():
    return os.path.join(bundle_dir(), "Contents", "Frameworks")


def bundle_plugins_path():
    return os.path.join(bundle_dir(), "Contents", "PlugIns")


def bundle_main_executable():
    return os.path.join(bundle_dir(), "Contents", "MacOS", "BornAgain")


def bundle_python_library():
    return os.path.join("Python.framework", "Versions", "2.7", "Python")


def qtlibs_path():
    return os.path.join(os.environ['QTDIR'], "lib")


def qtplugins_path():
    return os.path.join(os.environ['QTDIR'], "plugins")


def bornagain_binaries():
    result = glob.glob(os.path.join(bundle_dir(), "Contents", "lib", "BornAgain-*", "*"))
    result.append(bundle_main_executable())
    return result


# -----------------------------------------------------------------------------
# Utils
# -----------------------------------------------------------------------------


def make_dir(dirname):
    if not os.path.exists(dirname):
        os.makedirs(dirname)


def copy_file_to_dir(file_name, dest_dir):
    """
    Copies file to the destination directory. If destination doesn't exists, it will be created.
    """
    make_dir(dest_dir)
    shutil.copyfile(file_name, os.path.join(dest_dir, os.path.basename(file_name)))


def otool(filename):
    """
    Parses dependencies of given binary file
    """
    p = subprocess.Popen(['otool', '-XL', filename], stdout=subprocess.PIPE)
    # return iter(p.stdout.readline, b'')
    for line in iter(p.stdout.readline, b''):
        str = line.strip().split()[0]
        yield str


def setId(filename, newId):
    """
    Sets new id for binary file
    """
    p = subprocess.Popen(['install_name_tool', '-id', newId, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def fixDependency(filename, old, new):
    """
    Replaces old dependency with new one for given binary file
    """
    p = subprocess.Popen(['install_name_tool', '-change', old, new, filename], stdout=subprocess.PIPE)
    p.communicate()
    return


def is_python_framework_dependency(dependency):
    """
    Returns True if this dependency is python library
    """
    if not "boost" in dependency.lower():
        if "python" in dependency.lower():
            return True
    return False


def is_qt_framework_dependency(dependency):
    """
    Returns True if this dependency is Qt related
    """
    if "Qt" in dependency:
        return True
    return False


def is_to_bundle_dependency(dependency):
    """
    Returns True if this dependency should be moved to the bundle.
    Qt libraries and Python framework are special case and will be treated separately.
    """
    if not os.path.exists(dependency):
        return False
    non_dependency_patterns = ['@', '/usr/lib', '/System']
    for pat in non_dependency_patterns:
        if dependency.startswith(pat):
            return False

    if is_python_framework_dependency(dependency):
        return False

    if is_qt_framework_dependency(dependency):
        return False

    return True


def get_special_dependency_id(dependency):
    """
    Returns libId if this dependency requires special attention (i.e. Python framework)
    """
    if is_python_framework_dependency(dependency):
        return "@rpath/" + bundle_python_library()

    if is_qt_framework_dependency(dependency) and not "@rpath" in dependency:
        libname = os.path.basename(dependency)
        return "@rpath/" + libname +".framework/Versions/5/"+libname
    return None


def get_python_library_location():
    """
    Returns location of Python library. The library is deduced from interpreter itself
    """
    for dependency in otool(sys.executable):
        print dependency
        if os.path.exists(dependency) and "Python.framework" in dependency:
            return dependency

    # At this point it looks that interpreter depends from libPython via @loader_path
    # Let's try to find library directly

    prefix = sys.prefix
    suffix = sysconfig.get_config_var('LDVERSION') or sysconfig.get_config_var('VERSION')
    result = sys.prefix+"/lib/libpython"+suffix+".dylib"
    if os.path.exists(result):
        return result

    return None


# -----------------------------------------------------------------------------
# Actions
# -----------------------------------------------------------------------------


def copy_python_framework():
    """
    Copies Python library to the bundle. The name of the library will be deduced from the interpreter itself.
    """
    print "--> Copying Python framework"
    python_lib = get_python_library_location()
    destfile = os.path.join(bundle_frameworks_path(), bundle_python_library())
    make_dir(os.path.dirname(destfile))
    print "    From '{0}'\n    To '{1}'".format(python_lib, destfile)
    if not os.path.exists(destfile):
        shutil.copyfile(python_lib, destfile)
        libId = "@rpath/" + bundle_python_library()
        setId(destfile, libId)



def copy_qt_libraries():
    print "--> Copying Qt libraries"
    libs = ['QtCore', 'QtDBus', 'QtDesigner', 'QtGui', 'QtPrintSupport', 'QtWidgets', 'QtXml', 'QtSvg', 'QtNetwork']
    print "   ",
    for libname in libs:
        print libname,
        libpath = os.path.join(libname+".framework", "Versions", "5")
        srcfile = os.path.join(qtlibs_path(), libpath, libname)
        if os.path.exists(srcfile):
            dstdir = os.path.join(bundle_frameworks_path(), libpath)
            copy_file_to_dir(srcfile, dstdir)
    print


def copy_qt_plugins():
    print "--> Copying Qt plugins"
    plugins = ['platforms/libqcocoa.dylib', 'iconengines/libqsvgicon.dylib']
    print "   ",
    for name in plugins:
        print name,
        srcfile = os.path.join(qtplugins_path(), name)
        dstdir = os.path.join(bundle_plugins_path(), os.path.dirname(name))
        copy_file_to_dir(srcfile, dstdir)
    print


def process_dependency(dependency):
    """
    Copies external dependency library into Frameworks directory (if it is not already there)
    and sets corresponding library Id for it. Returns library Id and new location to the user.
    """
    libname = os.path.basename(dependency)
    libId = "@rpath/" + libname
    new_location = os.path.join(bundle_frameworks_path(), libname)
    if os.path.exists(new_location):
        return libId, None
    print "copying dependency", dependency
    copy_file_to_dir(dependency, bundle_frameworks_path())
    setId(new_location, libId)
    return libId, new_location


def walk_through_dependencies(file_name):
    for dependency in otool(file_name):
        if is_to_bundle_dependency(dependency):
            libId, new_location = process_dependency(dependency)
            fixDependency(file_name, dependency, libId)
            if new_location:
                walk_through_dependencies(new_location)
        else:
            libId = get_special_dependency_id(dependency)
            if libId:
                fixDependency(file_name, dependency, libId)


def copy_dependencies():
    print "--> Copying third party dependencies"
    for binfile in iter(bornagain_binaries()):
        walk_through_dependencies(binfile)


def fix_apple_bundle():
    print '-'*80
    print "Fixing OS X bundle at '{0}'".format(bundle_dir())
    print '-'*80
    copy_python_framework()
    copy_qt_libraries()
    copy_qt_plugins()
    copy_dependencies()
    print "Done!"


if __name__ == '__main__':
    if not platform.system() == 'Darwin':
        exit("This script is intended for MacOs systems. Exiting...")

    if len(sys.argv) != 2:
        exit("Please specify bundle location")

    set_bundle_dir(sys.argv[1])

    fix_apple_bundle()
