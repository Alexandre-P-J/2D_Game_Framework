cmake_minimum_required(VERSION 3.7)
project(Game)


IF (WIN32)

	set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2/include")
	# Support both 32 and 64 bit
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2/lib/x64/SDL2main.lib")
	else ()
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2/lib/x86/SDL2main.lib")
	endif ()


	set(SDL2_IMAGE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2_image/include")
	# Support both 32 and 64 bit
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_IMAGE_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2_image/lib/x64/SDL2_image.lib")
	else ()
		set(SDL2_IMAGE_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/Windows/SDL2_image/lib/x86/SDL2_image.lib")
	endif ()

	include_directories(include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
	file(GLOB SOURCES "src/*.cpp")

	add_executable(game.x ${SOURCES})
	target_link_libraries(game.x ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

ELSE()

	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
	
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	set(Box2D_LIBRARY "${CMAKE_SOURCE_DIR}/lib/Linux/libBox2D.a")
	set(RapidXML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/Multiplatform/rapidxml")

	include_directories(include ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIRS} ${RapidXML_INCLUDE_DIR})
	file(GLOB SOURCES "src/*.cpp")

	add_executable(game.x ${SOURCES})
	target_link_libraries(game.x ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${Box2D_LIBRARY})

ENDIF()
