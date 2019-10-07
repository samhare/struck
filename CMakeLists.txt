cmake_minimum_required(VERSION 2.6)
project(struck)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, defaulting to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_HOME_DIRECTORY}/cmake ${CMAKE_MODULE_PATH})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Eigen REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(
    src
    ${EIGEN_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
)

add_library(struck STATIC
	src/GraphUtils/GraphUtils.cpp
	src/Config.cpp
	src/HaarFeature.cpp
	src/HistogramFeatures.cpp
	src/LaRank.cpp
	src/MultiFeatures.cpp
	src/Sampler.cpp
	src/Features.cpp
	src/HaarFeatures.cpp
	src/ImageRep.cpp
	src/RawFeatures.cpp
	src/Tracker.cpp
)

add_executable(struck_main src/main.cpp)

target_link_libraries(struck_main ${OpenCV_LIBS} struck)

# Try to find TraX header and library ...
FIND_PACKAGE(trax COMPONENTS core opencv)

IF (trax_FOUND)
	LINK_DIRECTORIES(${TRAX_LIBRARY_DIRS})
	LINK_LIBRARIES(${TRAX_LIBRARIES})
	INCLUDE_DIRECTORIES(AFTER ${TRAX_INCLUDE_DIRS})

    add_executable(struck_trax src/trax.cpp)
    target_link_libraries(struck_trax ${OpenCV_LIBS} ${TRAX_LIBRARIES} struck)
ENDIF()

