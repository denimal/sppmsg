# SppMsg BS
# Sppmacd (c) 2018,2020

cmake_minimum_required(VERSION 2.8)
project(SppMsg)

cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0079 NEW)

macro(st2_link_sfml target)
	target_link_libraries(${target} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	target_include_directories(${target} PUBLIC "${SFML_INCLUDE_DIR}")
endmacro()

macro(cg_link_common target)
	target_include_directories(${target} PUBLIC "${CMAKE_SOURCE_DIR}")
	#target_include_directories(${target} PUBLIC "${CMAKE_SOURCE_DIR}/cgui_fork/include")
	#target_include_directories(${target} PUBLIC "${CMAKE_SOURCE_DIR}/hmutil/include")
	st2_link_sfml(${target})
	#target_link_libraries(${target} hmutil)
	#target_link_libraries(${target} cgui)
	target_link_directories(${target} PUBLIC "${CMAKE_BINARY_DIR}")
endmacro()

macro(st2_compile_lib target sources)
	message("ST2: compiling and adding ${target}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
	file(GLOB_RECURSE HMUTIL_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/${sources}/*")
	add_library(${target} "${HMUTIL_SOURCES}")
	target_include_directories(${target} PUBLIC "${CMAKE_SOURCE_DIR}/${sources}/include")
endmacro()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# includes
include("${CMAKE_CURRENT_LIST_DIR}/cmake/DetectArchCG.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/FindSFMLCG.cmake")

cg_detect_arch()
cg_find_sfml()

#st2_compile_lib(hmutil "hmutil")
#st2_compile_lib(cgui "cgui_fork")
#target_include_directories(cgui PUBLIC "${CMAKE_SOURCE_DIR}/src/")
#st2_link_sfml(cgui)

add_subdirectory(Client)
add_subdirectory(Server)

# copy all resources
file(COPY data/ DESTINATION "${CMAKE_BINARY_DIR}")
