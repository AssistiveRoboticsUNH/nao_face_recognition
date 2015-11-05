
################################################
## Header Info
################################################

cmake_minimum_required(VERSION 2.8.3)
project(face_recognition)


################################################
## Find Catkin Macros and Libraries
################################################

find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  rospy
  roslib
  cv_bridge
  image_transport
  sensor_msgs
  )

find_package( OpenCV REQUIRED )


################################################
## Catkin Specific Configuration 
################################################

## Declare things to be passed to dependent projects
catkin_package(
    INCLUDE_DIRS include                    ## INCLUDE_DIRS: uncomment this if you package contains header files
    #    LIBRARIES face_recognition         ## LIBRARIES: libraries you create in this project that dependent projects also need
    CATKIN_DEPENDS message_generation       ## CATKIN_DEPENDS: catkin_packages dependent projects also need
                   roscpp 
                   rospy 
                   cv_bridge     
    #    DEPENDS system_lib                 ## DEPENDS: system dependencies of this project that dependent projects also need
)


###################################
## Build 
###################################

## Specify additional locations of header files
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  )


## Declare a C++ executable
add_executable(facedetect_node src/facedetect_node.cpp)
#add_executable(facedetect_class src/facedetect_class.cpp)
 
add_executable(test_opencv src/practice/test_opencv.cpp)
add_executable(stream src/practice/stream_video.cpp)
add_executable(detect src/practice/detect_face.cpp)


## Add cmake target dependencies of the executable
add_dependencies(facedetect_node ${catkin_EXPORTED_TARGETS})
#add_dependencies(facedetect_node facedetect_class.cpp)
#add_dependencies(facedetect_node facedetect_class.h)


## Specify libraries to link a library or executable target against
target_link_libraries(facedetect_node
   ${catkin_LIBRARIES}
   ${OpenCV_Libraries}
 )

#target_link_libraries(facedetect_class
#   ${catkin_LIBRARIES}
#   ${OpenCV_Libraries}
# )


target_link_libraries(test_opencv
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
 )

target_link_libraries(stream
   ${catkin_LIBRARIES}
   ${OpenCV_Libraries}
 )

target_link_libraries(detect
   ${catkin_LIBRARIES}
   ${OpenCV_Libraries}
 )


################################################
## Declare ROS Messages, Services and Actions
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
# add_service_files(
#   FILES
#   Service1.srv
#   Service2.srv
# )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
# generate_messages(
#   DEPENDENCIES
#   std_msgs  # Or other packages containing msgs
# )


