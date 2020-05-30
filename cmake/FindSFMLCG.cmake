##############################
# CARGAME CMake Build System #
#      Ver. 0.3-beta.1       #
##############################

# assumes that the FindSFML.cmake file exists in ./cmake folder.
# the cg_detect_arch macro from DetectArchCG.cmake must be called before.
# sets:
#  SFML_FOUND
#  SFML_LIBRARIES
#  SFML_DEPENDENCIES
# copies <sfml>/<EXTLIB_PATH>/ to <sfml>/lib
# you must set:
#  SFML_ROOT - if it is not any standard path (see ./cmake/FindSFML.cmake)
macro(cg_find_sfml)
	cmake_policy(SET CMP0074 NEW) # suppress SFML_ROOT warning
	set(SFML_STATIC_LIBRARIES TRUE)
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
	find_package(SFML 2.4 COMPONENTS network audio graphics window system REQUIRED)
	
	# a bug in sfml build system?
	if(SFML_FOUND)
		file(COPY ${SFML_ROOT}/${CG_EXTLIB_PATH}/ DESTINATION ${SFML_ROOT}/lib)
	endif()
endmacro()
