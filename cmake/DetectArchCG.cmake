##############################
# CARGAME CMake Build System #
#      Ver. 0.3-beta.1       #
##############################

# The macro saves:
#   CG_COMPILER - compiler identifier (mingw,unix,msvc,invalid)
#   CG_ARCH_PREFIX_A - OS identifier (win,unix,_)
#   CG_ARCH_PREFIX_B - CPU arch identifier (x86,x64,_)
#   CG_ARCH_PREFIX - "${CG_ARCH_PREFIX_A}_${CG_ARCH_PREFIX_B}"
#   CG_EXTLIB_PATH - SFML external libraries (dependencies) path (extlibs/libs-COMPILER/ARCH)

macro(cg_detect_arch)
	message("CG: compiler is ${CMAKE_CXX_COMPILER_ID}")
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		if(WIN32)
			set(CG_COMPILER "mingw")
			set(CG_ARCH_PREFIX_A "win")
		elseif(UNIX)
			set(CG_COMPILER "unix")
			set(CG_ARCH_PREFIX_A "unix")
		endif()
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set(CG_COMPILER "msvc")
		set(CG_ARCH_PREFIX_A "win")
	else()
		set(CG_COMPILER "invalid")
		set(CG_ARCH_PREFIX_A "_")
		set(CG_ARCH_PREFIX_B "_")
	endif()

	# detect arch
	if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)")
		set(CG_ARCH_PREFIX_B "x86")
	elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(amd64)|(AMD64)")
		set(CG_ARCH_PREFIX_B "x64")
	else()
		set(CG_ARCH_PREFIX_B "_")
	endif()

	# generate arch prefix
	set(CG_ARCH_PREFIX "${CG_ARCH_PREFIX_A}_${CG_ARCH_PREFIX_B}")
	set(CG_EXTLIB_PATH "extlibs/libs-${CG_COMPILER}/${CG_ARCH_PREFIX_B}")
endmacro()
