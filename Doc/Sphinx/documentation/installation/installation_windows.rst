.. _installation_windows:


Installation on Windows
----------------------------------------------------

For the moment, we provide 32-bit installer package which can be installed into either a 32-bit or a 64-bit Windows 7,8 systems.

To install and run BornAgain for the first time proceed with the following steps:

.. contents::
   :depth: 1
   :local:
   :backlinks: none


Install the third party software
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The current version of BornAgain requires ``python-2.7, matplotlib, numpy``
to be installed on the system. These set of packages is known as `SciPy stack <http://www.scipy.org>`_  and for most users
the easiest way to install it, is to download one of free Python distributions, which includes all the key packages.

The list of possible options is given on SciPy installation `site <http://www.scipy.org/install.html>`_.

We have tested  `Anaconda Python Distribution <https://store.continuum.io/cshop/anaconda>`_  and suggest to use it if you do not have any other preferences.
The user has to download and install the package before proceeding to
the installation of BornAgain.

* Download and install Anaconda *Windows 32-bit — Python 2.7 — Graphical Installer* from `link <http://continuum.io/downloads>`_ 




Use BornAgain installer
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
BornAgain installation package for Windows 7,8 can be downloaded from `link <http://apps.jcns.fz-juelich.de/src/BornAgain>`_.
After downloading the installer, double click ``.exe`` file and follow the instructions on the screen.


Run the first simulation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Run Graphical User Interface
""""""""""""""""""""""""""""

Use BornAgain icon |BornAgainIcon| located on the desktop to start GUI.

.. |BornAgainIcon| image:: ../../_static/bornagainapp_32.png
          :align: top

.. seealso::

    :ref:`using_gui_label`
          
          
Run Python example
""""""""""""""""""""""""""""

Run an example located in BornAgain installation directory by double-clicking on python file:

.. code-block:: bash

    python C:/BornAgain-<Version>/Examples/python/simulation/ex001_CylindersAndPrisms/CylindersAndPrisms.py

You have to see immediately a scattering image appeared on the screen.
    
.. hint::
    This step will work only if  Python file extensions ``*.py`` are associated by the system with Python interpreter.
    If it is not the case, Windows will ask to choose what program to use to open the file. Depending from your Python installation
    it might be, for example, 
    ``C:\Anaconda\python.exe`` or ``C:\Users\yourname\Anaconda\python.exe``.


.. seealso::

    :ref:`working_from_python_label`




