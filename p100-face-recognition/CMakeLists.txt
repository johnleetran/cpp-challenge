# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name, in this case no language required
project(YOUR_PROJECT_NAME LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

find_package(Boost COMPONENTS system)
find_package(OpenCV CONFIG REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(main main.cpp)
target_link_libraries(main ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})

configure_file("data/age_deploy.prototxt" "${CMAKE_CURRENT_BINARY_DIR}/age_deploy.prototxt" COPYONLY)
configure_file("data/age_net.caffemodel" "${CMAKE_CURRENT_BINARY_DIR}/age_net.caffemodel" COPYONLY)
configure_file("data/gender_deploy.prototxt" "${CMAKE_CURRENT_BINARY_DIR}/gender_deploy.prototxt" COPYONLY)
configure_file("data/gender_net.caffemodel" "${CMAKE_CURRENT_BINARY_DIR}/gender_net.caffemodel" COPYONLY)
configure_file("data/opencv_face_detector.pbtxt" "${CMAKE_CURRENT_BINARY_DIR}/opencv_face_detector.pbtxt" COPYONLY)
configure_file("data/opencv_face_detector_uint8.pb" "${CMAKE_CURRENT_BINARY_DIR}/opencv_face_detector_uint8.pb" COPYONLY)