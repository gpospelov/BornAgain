.. _building_gui_label: 

Building Graphical User Interface
---------------------------------------

This section describes how to build and install BornAgain graphical user interface on Unix platforms (MacOS included).

Please follow first the :ref:`detailed_installation_instruction_label` 
to learn how to build and install BornAgain core libraries. When completed, proceed with the following additional steps:


.. contents::
   :depth: 1
   :local:
   :backlinks: none

   

Install Qt5 libraries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

BornAgain GUI depends on `Qt5 <http://qt-project.org/qt5>`_ libraries.
Most of Linux distributions, as well as MacOS, do not have it by default and you have to install it either via system package manager or using Qt binary installer
downloaded from the developers site. 

Below we provide recipe we use, to install latest Qt5 libraries on our Linux and MacOS operation systems


MacOS systems
"""""""""""""""

1. Download *Qt Online installer for Mac* from developers `site <http://qt-project.org/doc/qt-5/linux.html>`_

2. Run installer, then follow the instructions:

   By default Qt will be installed in the directory ``/Users/yourname/Qt``
   
3. After the installation insert following environment variables into ``.profile`` file of your home directory::

    export QTDIR=/Users/yourname/Qt/5.3/clang_64
    export PATH=$QTDIR/bin:$PATH
    export DYLD_LIBRARY_PATH=$QTDIR/lib:$DYLD_LIBRARY_PATH
   
..

  You have to adjust ``QTDIR`` variable for the Qt version number and ``yourname`` to point to the right Qt directory.



    
Linux systems
"""""""""""""""

1. Download *Qt online installer for Linux 64-bit* from developers `site <http://qt-project.org/doc/qt-5/linux.html>`_

2. Run installer from the command line, then follow the instructions::

    ./qt-opensource-linux-x64-1.6.0-4-online.run

..

  By default Qt will be installed in the directory ``/home/yourname/Qt``

3. Specify following variables in your ``.bashrc`` file::
 
    export QTDIR=/home/yourname/Qt/5.3/gcc_64
    export PATH=$QTDIR/bin:$PATH
    export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

..

  You have to adjust ``QTDIR`` variable for the Qt version number and ``yourname`` to point to the right Qt directory.

  
.. note::

    Open new terminal and validate that ``qmake --version`` command gives you the right Qt version you have just installed::

    Linux> Using Qt version 5.3.1 in /home/yourname/Qt/5.3/gcc_64/lib
    
    MacOS> Using Qt version 5.3.1 in /Users/yourname/Qt/5.3/clang_64/lib

    

    
Buld and install BornAgain GUI
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We assume that you have already BornAgain libraries compiled and installed as explained in :ref:`detailed_installation_instruction_label` 
and that

+------------------------+-----------------------------------------------------+
| <source_dir>           |    is your BornAgain source directory               |
+------------------------+-----------------------------------------------------+
| <build_dir>            |    the directory were BornAgain core was build      |
+------------------------+-----------------------------------------------------+
| <install_dir>          |    the directory where BornAgain core was installed |
+------------------------+-----------------------------------------------------+

Change the directory to ``<build_dir>``

.. code-block:: bash

  cd <build_dir>

type following cmake configuration command

**MacOS system (with third party librarties in /opt/local)**

.. code-block:: bash

  cmake -DBORNAGAIN_GUI=ON -DCMAKE_PREFIX_PATH=/opt/local -DCMAKE_INSTALL_PREFIX=<install_dir> <source_dir>

**Linux systems**

.. code-block:: bash

  cmake -DBORNAGAIN_GUI=ON -DCMAKE_INSTALL_PREFIX=<install_dir> <source_dir>

  
Finally, compile and install the graphical users interface  

.. code-block:: bash

  make -j4
  make install


Run BornAgain GUI
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After installation is complete the new ``BornAgain`` executable will appear in ``<install_dir>/bin`` directory.
Make sure that BornAgain core libraries are in your PATH by running

.. code-block:: bash

  source <install_dir>/bin/thisbornagain.sh

and launch GUI  
  

.. code-block:: bash

  <install_dir>/bin/BornAgain


.. seealso::

    :ref:`using_gui_label`
    
    :ref:`troubleshooting_label`
