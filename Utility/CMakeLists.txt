# SppMsg BS
# Sppmacd (c) 2020

set(SPPMSG_UTILITY_SOURCES
	command.cpp
	command.hpp
	config.hpp
	)
	
message("SPPMSG: compiling and adding SppMsgUtility")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
add_library(SppMsgUtility "${SPPMSG_UTILITY_SOURCES}")
target_include_directories(SppMsgUtility PUBLIC "${CMAKE_SOURCE_DIR}/${sources}")
st2_link_sfml(SppMsgUtility)
