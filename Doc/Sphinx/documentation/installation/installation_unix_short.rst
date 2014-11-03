Installation instruction (short version)
-----------------------

Install the third party software
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* cmake (>= 2.8)
* boost library (>= 1.48)
* GNU scientific library (>= 1.15)
* fftw3 library (>= 3.3.1)
* Python-2.7, python-devel, python-numpy-devel

Get the source
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Download BornAgain source tarball from `link <http://apps.jcns.fz-juelich.de/src/BornAgain>`_ 
or use following git repository

.. code-block:: bash

    $ git clone git://apps.jcns.fz-juelich.de/BornAgain.git


Build and install the framework
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: bash

    $ mkdir <build_dir>; cd <build_dir>;
    $ cmake -DCMAKE_INSTALL_PREFIX=<install_dir> <source_dir>
    $ make -j4
    $ make check
    $ make install

