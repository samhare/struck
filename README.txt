Struck: Structured Output Tracking with Kernels

Code to accompany the paper:
  Struck: Structured Output Tracking with Kernels
  Sam Hare, Amir Saffari, Philip H. S. Torr
  International Conference on Computer Vision (ICCV), 2011

Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK

Contact: Sam Hare <sam.hare@brookes.ac.uk>

------------
Requirements
------------

OpenCV: http://opencv.willowgarage.com/
Eigen: http://eigen.tuxfamily.org/

This code has been developed and tested using 
OpenCV v2.1 and Eigen v2.0.15

-----
Usage
-----

> struck [config-file-path]

If no path is given the application will attempt to
use ./config.txt.

Please see config.txt for configuration options.

---------
Sequences
---------

Sequences are assumed to be of the format of those 
available from:

http://vision.ucsd.edu/~bbabenko/project_miltrack.shtml

----------------
Acknowledgements
----------------

This code uses the OpenCV graphing utilities provided
by Shervin Emami: http://www.shervinemami.co.cc/graphs.html
