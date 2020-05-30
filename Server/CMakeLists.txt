# SppMsg BS
# Sppmacd (c) 2020

set(SOURCES
	clients.cpp
	command.cpp
	command.hpp
	config.hpp
	main.cpp
	send.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_executable(SppMsgServer "${SOURCES}")
cg_link_common(SppMsgServer)
