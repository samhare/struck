find_path(EIGEN_INCLUDE_DIR NAMES Eigen/Core
             PATH_SUFFIXES eigen3)
  
# handle the QUIETLY and REQUIRED arguments and set EIGEN_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EIGEN DEFAULT_MSG EIGEN_INCLUDE_DIR)

SET(EIGEN_INCLUDE_DIRS ${EIGEN_INCLUDE_DIR})
