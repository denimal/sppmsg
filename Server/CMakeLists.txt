# SppMsg BS
# Sppmacd (c) 2020

set(SOURCES
	config.hpp
	client.cpp
	client.hpp
	command.cpp
	command.hpp
	main.cpp
	server.cpp
	server.hpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_executable(SppMsgServer "${SOURCES}")
cg_link_common(SppMsgServer)
