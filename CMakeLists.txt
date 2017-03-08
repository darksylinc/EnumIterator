project( EnumIterator )
cmake_minimum_required( VERSION 2.8 )

set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )

if( CMAKE_BUILD_TYPE STREQUAL "" )
	set( CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "One of: Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

# Determine if we are compiling for a 32bit or 64bit system
include(CheckTypeSize)
CHECK_TYPE_SIZE("void*" ARCH_PTR_SIZE BUILTIN_TYPES_ONLY)
if (ARCH_PTR_SIZE EQUAL 8)
  set(PLATFORM_X64 TRUE)
else ()
  set(PLATFORM_X64 FALSE)
endif ()

# Setup our application
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}" )
if( MSVC )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	if( NOT PLATFORM_X64 )
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	add_definitions( -DUNICODE -D_UNICODE )
endif()

macro( add_recursive dir retVal )
	file( GLOB_RECURSE ${retVal} ${dir}/*.h ${dir}/*.cpp ${dir}/*.c )
endmacro()

include_directories( "./include" )
#include_directories( "./Dependencies/rapidjson" )

add_recursive( ./src SOURCES )
add_recursive( ./include HEADERS )

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS} )
