cmake_minimum_required(VERSION 3.11.3)
link_libraries(-lstdc++fs -pthread)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

project(EVSim)

# Find all executables
file(GLOB project_SRCS "src/*.cpp")

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

add_executable(EVSim ${project_SRCS})