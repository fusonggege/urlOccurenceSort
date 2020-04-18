# Note: CMake support is community-based. The maintainers do not use CMake
# internally.

cmake_minimum_required(VERSION 2.8.8)
Project( urlOccurenceSort )
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
file(GLOB hdrs "${CMAKE_SOURCE_DIR}/src/*.h")
file(COPY  ${hdrs}  
	DESTINATION  "${CMAKE_SOURCE_DIR}/include"  )
include(CMakeDependentOption)
include(GNUInstallDirs)
# compile gtest for unittest
add_subdirectory( thirdPartyLib )

#find_package(Glog)
#include_directories(${GLOG_INCLUDE_DIRS})
# compile urlOccurenceSort
INCLUDE_DIRECTORIES(
	include
	)


#ADD_DEPENDENCIES(occurrence_sort glog)
ADD_LIBRARY(occurence_sort STATIC src/url_occurence_sort.cpp )

# compile urlOccurenceSortUnitTest
ADD_EXECUTABLE(url_occurence_sort_unittest unittest/url_occurence_sort_unittest.cpp)
TARGET_LINK_LIBRARIES(
	url_occurence_sort_unittest
	gtest
	occurence_sort
	glog
	)
