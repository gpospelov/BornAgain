Detailed installation instruction
--------------------------------------



BornAgain uses ``CMake`` to configure a build system for compiling and installing the framework. 
There are three major steps to building BornAgain

.. contents::
   :depth: 1
   :local:
   :backlinks: none

Install the third party software
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To successfully build BornAgain a number of prerequisite packages must be installed.

**Required**

  * compilers: clang  versions >= 3.1 or GCC versions >= 4.1.2
  * cmake >= 2.8
  * boost library >=1.48
  * GNU scientific library >= 1.15
  * fftw3 library >= 3.3.1
  * python-2.7, python-devel, python-numpy-devel, python-matplotlib

**Optional**
  * ROOT5 framework >= 5.34 (for additional fitting algorithms in BornAgain)

All required packages can be easily installed on most Linux distributions using the system's package
manager.

Below we give a few examples for several selected operation systems. Please note,
that other distributions (Fedora, Mint, etc) may have different commands for invoking the package manager and slightly different names of packages (like ``boost`` instead of ``libboost`` etc). 
Besides that, the installation should be very similar.




Ubuntu, Debian
""""""""""""""""""""

Installing required packages

.. code-block:: bash

    sudo apt-get install git cmake libgsl0-dev libboost-all-dev libfftw3-dev python-dev python-numpy python-matplotlib

Installing optional packages

.. code-block:: bash

    sudo apt-get install root-system

OpenSuse
""""""""""""""""""""

Installing required packages

.. code-block:: bash

    sudo zypper install git-core cmake gsl-devel boost-devel fftw3-devel python-devel python-numpy-devel python-matplotlib python-matplotlib-tk

Installing optional packages. Adding ''scientific'' repository (for OpenSuse 13.1, for other versions use corresponding repository)

.. code-block:: bash

    sudo zypper ar http://download.opensuse.org/repositories/science/openSUSE_13.1 science

and then installing packages

.. code-block:: bash

    sudo zypper install root-system



Mac OS X
""""""""""""""""""""

To simplify the installation of third party open-source software on a Mac OS X system we recommend the use of 
`MacPorts <http://www.macports.org/install.php>`_ package manager.  The easiest way to install ``MacPorts`` is by downloading the 
`dmg <http://www.macports.org/install.php>`_ and running the system's installer.
After installation new command ``port`` will be available in terminal window of your Mac.

Installing required packages

.. code-block:: bash

    sudo port -v selfupdate
    sudo port install git-core cmake fftw-3 gsl py27-matplotlib py27-numpy py27-scipy
    sudo port install boost -no_single-no_static+python27 
    sudo port select --set python python27

Installing optional packages

.. code-block:: bash

    sudo port install root +fftw3+python27

.. important::
    By default ``MacPorts`` will be installed to separate ``/opt/local`` directory. 
    This path has to be specified explicitely during ``CMake`` configuration using ``-DCMAKE_PREFIX_PATH=/opt/local``, see :ref:`below <important_cmake_prefix>`.     
    
Get the source
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Download BornAgain source tarball from `link <http://apps.jcns.fz-juelich.de/src/BornAgain>`_ and unpack it

.. code-block:: bash

    cd <some_directory>
    tar xfz BornAgain-0.9.9.tar.gz


Alternatively, instead of downloading the tarball you can get access to the source code by cloning our public Git repository

.. code-block:: bash

    cd <some_directory>
    git clone git://apps.jcns.fz-juelich.de/BornAgain.git

.. note::
  Our Git repository holds two main branches called ``master`` and ``develop``. We consider ``master`` branch to be the main branch where the source code of HEAD always reflect latest stable release. Cloning the repository

  - gives you source code snapshot corresponding to the latest stable release,
  - automatically sets up your local master branch to track our remote master branch,  so you will be able to fetch changes from remote branch at any time using ``git pull`` command.

  Master branch is updating approximately once per month. The second branch, ``develop`` branch, is a snapshot of the current development. This is where any automatic nightly builds are built from. The develop branch is 
  always expected to work, so to get the most recent features one can switch source tree to it by
  
  .. code-block:: bash

    cd BornAgain
    git checkout develop
    git pull


Build and install the framework
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

BornAgain should be build using `CMake <http://www.cmake.org>`_  cross platform build system. Having third-party libraries installed  and BornAgain 
source code acquired as was explained in previous sections, type build commands


.. code-block:: bash

  mkdir <build_dir>
  cd <build_dir>
  cmake -DCMAKE_INSTALL_PREFIX=<install_dir> <source_dir>
  make -j4
  make check
  make install

.. _important_cmake_prefix:    

    .. important::

        * Especially  for MacOS users who has installed third party libraries using ``MacPorts`` package manager.

        In the case of a complex system setup, with libraries of different versions 
        scattered across multiple places (``/opt/local``, ``/usr/local`` etc.),
        you may want to help ``CMake`` in finding the correct library paths
        by running it with additional parameter
    
        .. code-block:: bash

            cmake -DCMAKE_PREFIX_PATH=/opt/local -DCMAKE_INSTALL_PREFIX=<install_dir> <source_dir>
  

Here ``<source_dir>`` is the name of directory, where BornAgain source code has been copied, ``<install_dir>`` is the directory, where user wants  the package
to be installed, and ``<build_dir>`` is the directory where building will occur.

.. note::

  Having dedicated directory ``<build_dir>`` for build process is recommended by ``CMake``. 
  That allows several builds with different compilers/options from the same source and keeps source directory clean from build remnants.

  
Compilation process invoked by the command ``make`` lasts about 10 min for an average laptop of 2012 edition. On multi-core machines the compilation can be 
decreased by invoking command make with the parameter ''make -j[N]'', where N is the number of cores.

Running functional tests is an optional but recommended step. Command ``make check``
will compile several additional tests and run them one by one. Every tests contains
simulation of typical GISAS geometry and comparison of simulation results with reference files on numerical level. Having 100% tests passed ensures that your local installation
is correct.

.. code-block:: bash

  make check
  ...
  100% tests passed, 0 tests failed out of 61
  Total Test time (real) = 31.14 sec
  [100%] Build target check

The last command ``make install`` copies compiled libraries and some usage examples
into  installation directory.

.. code-block:: bash
  
  make install

After installation is completed, the location of BornAgain libraries needs to be included into
``LD_LIBRARY_PATH`` and ``PYTHONPATH`` environment variables.
This can be done by running BornAgain setup script in the terminal session

.. code-block:: bash

  source <install_dir>/bin/thisbornagain.sh

Conveniently, given call can be placed in your ``.bashrc`` file.

    
