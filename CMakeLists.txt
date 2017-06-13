cmake_minimum_required (VERSION 3.5)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
SET(GCC_COVERAGE_LINK_FLAGS "")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

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
