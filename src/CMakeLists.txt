cmake_minimum_required(VERSION 3.0.0)
project(Server VERSION 0.1.0)

include(CTest)
enable_testing()
find_package (Threads REQUIRED)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)
include_directories(${CMAKE_SOURCE_DIR}/matrix  ${CMAKE_SOURCE_DIR}/search_problem ${CMAKE_SOURCE_DIR}/command ${CMAKE_SOURCE_DIR}/server_side)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
link_directories(${CMAKE_SOURCE_DIR}/matrix  ${CMAKE_SOURCE_DIR}/search_problem ${CMAKE_SOURCE_DIR}/command ${CMAKE_SOURCE_DIR}/server_side)
add_executable(ex4.out ./src/CacheException.cpp ./src/ErrorCache.cpp ./src/ErrorCodeException.cpp ./src/file_reading.cpp
       ./src/FileCopier.cpp ./src/main.cpp ./src/Matrix.cpp ./src/Maze.cpp ./src/MazeState.cpp ./src/MyClientHandler.cpp ./src/Problem.cpp ./src/SearchAlgoritem.cpp Server.cpp
       ./src/Soloution.cpp ./src/StatesPair.cpp

)
target_link_libraries(ex4.out matrix  ${CMAKE_THREAD_LIBS_INIT})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)