# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name, in this case no language required
project(YOUR_PROJECT_NAME LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

#add_subdirectory(lib/cpprestsdk)

find_package(Boost COMPONENTS system beast asio)

include_directories(${Boost_INCLUDE_DIR})
add_executable(main main.cpp)
target_link_libraries(main ${Boost_LIBRARIES})

