CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT( izg04 )
 
set(SRC
	src/main.cpp
	src/IZG_TrackballDragger.cpp
	src/IZG_RotateCylinderDragger.cpp
	src/IZG_MultiDragger.cpp
	src/IZG_Scale1DDragger.cpp
	src/IZG_Translate1DDragger.cpp
	src/Student.cpp)

set(INCLUDE
	include/IZG_TrackballDragger.h
	include/IZG_RotateCylinderDragger.h
	include/IZG_MultiDragger.h
	include/IZG_Scale1DDragger.h
	include/IZG_Translate1DDragger.h
	include/Student.h)


ADD_EXECUTABLE(izg04)

set(OSG_ROOT  "${CMAKE_CURRENT_SOURCE_DIR}/OSG" CACHE PATH "OSG root folder")

set(OSG_REQUIRED_LIBRARIES 
	OpenThreads
	osgDB
	osg
	osgViewer
	osgGA
	osgUtil
	osgManipulator)

set(OSG_INCLUDE_DIR ${OSG_ROOT}/include)

SET(OSG_LIBRARY_RELEASE "")
SET(OSG_LIBRARY_DEBUG "")

foreach(OSG_LIB IN LISTS OSG_REQUIRED_LIBRARIES)

	list(APPEND OSG_LIBRARY_RELEASE ${OSG_ROOT}/lib/${OSG_LIB}.lib)
	list(APPEND OSG_LIBRARY_DEBUG ${OSG_ROOT}/lib/${OSG_LIB}d.lib)

endforeach()

FIND_PACKAGE(OpenSceneGraph)


target_sources(izg04 PRIVATE
               ${SRC}
               ${INCLUDE})

INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(izg04 ${OPENSCENEGRAPH_LIBRARIES} )

target_include_directories(izg04
                           PRIVATE
                           "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(OSG_LIBRARIES_TO_INSTALL
	osg
	osgDB
	osgGA
	osgManipulator
	osgText
	osgUtil
	osgViewer
	OpenThreads
  zlib)

foreach(file ${OSG_LIBRARIES_TO_INSTALL})
	add_custom_command(TARGET izg04 POST_BUILD        
    				   COMMAND if $<CONFIG:Release> neq 0 ${CMAKE_COMMAND} -E copy_if_different "${OSG_ROOT}/bin/${file}.dll" $<TARGET_FILE_DIR:izg04>
    				   COMMAND if $<CONFIG:Debug> neq 0 ${CMAKE_COMMAND} -E copy_if_different "${OSG_ROOT}/bin/${file}d.dll" $<TARGET_FILE_DIR:izg04>)      
endforeach()   

add_custom_command(TARGET izg04 POST_BUILD
    			   COMMAND ${CMAKE_COMMAND} -E copy_directory
    			   "${OSG_ROOT}/bin/osgPlugins-3.6.5"
        		   $<TARGET_FILE_DIR:izg04>/osgPlugins-3.6.5)  
              
add_custom_command(TARGET izg04 POST_BUILD        
    				   COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/bunny.obj" ${CMAKE_CURRENT_BINARY_DIR})   

set_property(DIRECTORY "${CMAKE_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT izg04)