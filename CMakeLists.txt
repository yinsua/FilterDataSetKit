cmake_minimum_required (VERSION 3.5)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
project (FilterDataSetKit)

find_package(OpenCV REQUIRED)

aux_source_directory(. DIRSRCS)
include_directories(./ )
link_directories(
    /usr/lib
)

add_executable(main ${DIRSRCS})
target_link_libraries (
    main ${OpenCV_LIBS} 
)
