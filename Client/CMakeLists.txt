# SppMsg BS
# Sppmacd (c) 2020

set(SOURCES
	config.hpp
	main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
add_executable(SppMsgClient "${SOURCES}")
target_link_libraries(SppMsgClient SppMsgUtility)
cg_link_common(SppMsgClient)
