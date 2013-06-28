### CMake file for Flying_Sebs
###
###   -  2010: Initial version <druon@lirmm.fr>
###
###
###############################################################################


cmake_minimum_required (VERSION 2.6)

project (test)
set (test_VERSION_MAJOR 0)
set (test_VERSION_MINOR 1)

set( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /lib /usr/lib /usr/local/lib )
set( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} /usr/include /usr/local/include )
set( CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH}  "${PROJECT_SOURCE_DIR}/cmake" ) 

set ( INSTALL_BIN_PATH bin )
set ( INSTALL_LIB_PATH lib )
set ( INSTALL_AR_PATH  lib )
set ( INSTALL_HEADERS_PATH include )


# Make relative paths absolute (needed later on)

foreach(p LIB BIN HEADERS AR)
    set(var INSTALL_${p}_PATH)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()


### Search for Lib/Headers

find_package( RT_ARDrone REQUIRED )
find_package( RT_ARDRONE_VIDEOSTREAM REQUIRED )


### Set include directories 
        
include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include"
	             "${CMAKE_CURRENT_SOURCE_DIR}/src"
        	     "${CMAKE_CURRENT_BINARY_DIR}"
                     "${CMAKE_INSTALL_PREFIX}/include" 
                     "${RT_ARDRONE_INCLUDE_DIRS}"
                     "${RT_ARDRONE_VIDEOSTREAM_INCLUDE_DIRS}")


### File Lists

file( GLOB hdr "src/*.h*" )


### Main Target and linking

add_executable( "testYUV" 
				"${CMAKE_CURRENT_SOURCE_DIR}/src/test_video_YUV420.c"
				 ${hdr} )


target_link_libraries ( "testYUV" ${CMAKE_THREAD_LIBS_INIT}
					${RT_ARDRONE_LIBRARIES}
					${RT_ARDRONE_VIDEOSTREAM_LIBRARIES} )

### Install targets

install( TARGETS "testYUV"
        RUNTIME DESTINATION ${INSTALL_BIN_PATH}  COMPONENT main
        LIBRARY DESTINATION ${INSTALL_LIB_PATH}  COMPONENT main
        ARCHIVE DESTINATION ${INSTALL_AR_PATH}   COMPONENT main )


        

