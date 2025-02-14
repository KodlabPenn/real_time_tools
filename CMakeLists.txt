#
# Copyright (c) 2019, New York University and Max Planck Gesellschaft.
#
# License BSD-3 clause
#

#
# set up the project
#
cmake_minimum_required(VERSION 3.10.2)

project(real_time_tools VERSION 2.0.0)

# Using C++17
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

#
# Dependencies
#

# Usual dependencies
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Threads REQUIRED)

#
# Setup the environment from dependencies
#

# This macro sets the C++ preprocessor flags "XENOMAI", "RT_PREEMPT", or
# "UBUNTU" according to the current operating system.
set(CURRENT_OS "rt-preempt")
add_definitions("-DRT_PREEMPT")

#
# Add the main library
#

# Create the CMake target
add_library(
  ${PROJECT_NAME} STATIC
  src/realtime_check.cpp
  src/thread.cpp
  src/spinner.cpp
  src/hard_spinner.cpp
  src/timer.cpp
  src/iostream.cpp
  src/usb_stream.cpp
  src/process_manager.cpp
  src/frequency_manager.cpp
  src/timespec.c)
# Add the include dependencies
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                         $<INSTALL_INTERFACE:include>)
# Link the dependencies
target_link_libraries(${PROJECT_NAME} Boost::boost Boost::filesystem)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
# Xenomai libs could be empty. But this is needed in case the OS is Xenomai
target_link_libraries(${PROJECT_NAME} ${Xenomai_LIBS})
# For the installation
list(APPEND all_targets ${PROJECT_NAME})

#
# Demos.
#
macro(add_real_time_tools_demo demo_name)
  # set(demo_target_name ${PROJECT_NAME}_${demo_name})
  set(demo_target_name ${demo_name})
  # add the executable.
  add_executable(${demo_target_name} demos/${demo_name}.cpp)
  # save the name for installation
  set(all_targets ${all_targets} ${demo_target_name})
  # dependencies
  target_include_directories(
    ${demo_target_name}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include>)
  target_link_libraries(${demo_target_name} ${PROJECT_NAME})
endmacro(add_real_time_tools_demo target_name)

add_real_time_tools_demo(demo_realtime_check)
add_real_time_tools_demo(demo_realtime_strict_check)
add_real_time_tools_demo(demo_spinner)
add_real_time_tools_demo(demo_timing)
add_real_time_tools_demo(demo_thread)
add_real_time_tools_demo(demo_usb_stream_imu_3DM_GX3_25)
add_real_time_tools_demo(demo_checkpoint_timer)

#
# Executables.
#

# set(EXE1 realtime_test) add_executable(${EXE1} src/bin/realtime_test.cpp)
# target_link_libraries(${EXE1} ${PROJECT_NAME} ${catkin_LIBRARIES})

# set(EXE2 realtime_test_display) add_executable(${EXE2}
# src/bin/realtime_test_display.cpp) target_link_libraries(${EXE2}
# ${PROJECT_NAME} ${catkin_LIBRARIES})

#
# Install the package
#

# install the include directory
install(DIRECTORY include/ DESTINATION include)

# command to install the library and binaries
install(
  TARGETS ${all_targets}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

