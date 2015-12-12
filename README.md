# Struck: Structured Output Tracking with Kernels


This is a C++ implementation of the tracking algorithm described in the paper:

**Struck: Structured Output Tracking with Kernels**  
Sam Hare, Amir Saffari, Philip H. S. Torr  
International Conference on Computer Vision (ICCV), 2011

Tracking can be performed on video sequences, or live input from a webcam.

Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK

## Requirements

* OpenCV: http://opencv.org/
* Eigen: http://eigen.tuxfamily.org/

This code has been tested using OpenCV v2.4.12 and Eigen v3.2.6

## Compilation

CMake is used for cross-platform compilation. For example on Unix-based systems run:

    > mkdir build
    > cd build
    > cmake ..
    > make

**Note: Make sure you compile the code in Release, as a Debug build will result in significantly slower performance**

## Usage

After compilation, from the top level of the repository run:

    > build/bin/struck [config-file-path]

If no path is given the application will attempt to
use ./config.txt.

Please see config.txt for configuration options.


## Sequences

Sequences are assumed to be of the format of those
available from: http://vision.ucsd.edu/~bbabenko/project_miltrack.html

## License

This code is released under the GPLv3 license for non-commercial use only. For other types of license please contact me.

## Acknowledgements

This code uses the OpenCV graphing utilities provided
by Shervin Emami: http://www.shervinemami.info/graphs.html
