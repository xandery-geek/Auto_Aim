# cmake needs this line
cmake_minimum_required(VERSION 2.8)

# Define project name
set(PROJECT_NAME Auto_aim)
project(${PROJECT_NAME})

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")


#find_package(wiringPi REQUIRED)
 find_library(wiringPi_LIB wiringPi)


if(CMAKE_VERSION VERSION_LESS "2.8.11")
  # Add OpenCV headers location to your include paths
  include_directories(${OpenCV_INCLUDE_DIRS})
endif()

#the directory of include file 
include_directories(inc)
message(STATUS "include file : inc ")

#the directory of source file
aux_source_directory(src DIR_SRCS)
message(STATUS "src file: ${DIR_SRCS}")

# Declare the executable target built from your sources
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# Link your application with OpenCV libraries
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} ${wiringPi_LIB})

