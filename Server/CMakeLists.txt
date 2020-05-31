# SppMsg BS
# Sppmacd (c) 2020

set(SOURCES
	config.hpp
	client.cpp
	client.hpp
	main.cpp
	server.cpp
	server.hpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_executable(SppMsgServer "${SOURCES}")
target_link_libraries(SppMsgServer SppMsgUtility)
cg_link_common(SppMsgServer)
