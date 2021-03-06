=====
td.sh
=====

  Converting seconds to human readable time duration.

**td.sh** project has two implementations:

1. C:

   The C implementation include

   * library (``libtd``),
   * command-line program (``td``), and
   * Bash loadable (``td-bash``), loaded as ``td`` shell builtin.

2. Bash script (``td.sh``)

.. contents:: **Contents**
   :local:


Installation
============

When installing from Git repository, run the following command to initialize
required files:

.. code:: sh

  $ autoreconf --install

By default, to install to ``/usr/local``, run:

.. code:: sh

  $ ./configure && make && make install

Or to ``/usr``:

.. code:: sh

  $ ./configure prefix=/usr && make && make install

Or to your home:

.. code:: sh

  $ ./configure prefix=$HOME/.local && make && make install

To uninstall, use ``uninstall`` target.

Options
-------

``--disable-bash``
  do not build Bash implementation

``--disable-c``
  do not build C implementation

``--enable-bash-loadable=BASH_HEADER_PATH``
  build Bash loadable

  The loadable is installed as ``prefix/bin/td.bash``, it can be enabled by, as
  long as ``td.bash`` is in ``$PATH``:

  .. code:: sh

    $ enable -f "$(which td.bash)" td
    $ td 123

``--disable-python``
  do not build Python bindings

  ``--disable-python2``
    do not build Python 2 binding

  ``--disable-python3``
    do not build Python 3 binding

``--without-check``
  do not run Check unittest


Usage
=====

The basic usage:

.. code:: sh

  $ td.sh 123
  2 minutes 3 seconds

You can source the Bash script to have ``print_td`` function for better performance:

.. code:: sh

  $ source td.sh
  $ print_td 123
  2 minutes 3 seconds
  $ ./td.sh 1 2 60 61
  1 second
  2 seconds
  1 minute
  1 minute 1 second
  $ ./td.sh -p -P 1 2 60 61
   1 second 
   2 seconds
   1 minute 
   1 minute   1 second 
  $ ./td.sh -p -P -a 1 2 60 61
   0 days  0 hours  0 minutes  1 second 
   0 days  0 hours  0 minutes  2 seconds
   0 days  0 hours  1 minute   0 seconds
   0 days  0 hours  1 minute   1 second 

Options
-------

``-a``
  prints all numbers and units even the numbers are zeros.

``-p[X]``: number padding
  prints out like ``_1 second`` (``_`` denotes the space) or ``-p0`` for ``01 second`` or ``07 seconds``, default is a space .

``-P``: unit string padding
  prints out like ``1 minute  12 seconds``, note there is additional space after ``minute``.


Tests
=====

The unittest is done by Check_ and Autotest_:

.. code:: sh

  $ make check

.. _Check: http://check.sourceforge.net/
.. _Autotest: http://www.gnu.org/savannah-checkouts/gnu/autoconf/manual/autoconf-2.69/html_node/Using-Autotest.html#Using-Autotest


Benchmark
=========

.. code:: sh

  $ make benchmark

Here is a sample result of benchmarking:

+-------------+---------------------------------+
| conversions | benchmark                       |
+=============+=================================+
| 2,060       | ``td.sh`` function calls        |
+-------------+---------------------------------+
| 184         | ``td.sh`` script executions     |
+-------------+---------------------------------+
| 60          | ``td`` command executions       |
+-------------+---------------------------------+
| 24,092      | ``td.bash`` loadable executions |
+-------------+---------------------------------+
| 40          | Python 2 script executions      |
+-------------+---------------------------------+
| 16          | Python 3 script executions      |
+-------------+---------------------------------+


License
=======

This project is licensed under the MIT License, see COPYING_ for full text::

  Copyright (c) 2010, 2012, 2014 Yu-Jie Lin

.. _COPYING: COPYING
