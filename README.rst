=====
td.sh
=====

  Converting seconds to human readable time duration.

**td.sh** project has two implementations, C (``td``) and Bash (``td.sh``).

.. contents:: **Contents**
   :local:


Installation
============

By default, to install to ``/usr/local``, run:

.. code:: sh

  $ make install

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


License
=======

This project is licensed under the MIT License, see COPYING_ for full text::

  Copyright (c) 2010, 2012, 2014 Yu-Jie Lin

.. _COPYING: COPYING
