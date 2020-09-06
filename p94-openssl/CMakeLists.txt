# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name, in this case no language required
project(YOUR_PROJECT_NAME LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
# set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")


find_package(Boost COMPONENTS system program_options)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
add_executable(main main.cpp)
target_link_libraries(main ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

