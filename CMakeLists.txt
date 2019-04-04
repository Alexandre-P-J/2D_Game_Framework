cmake_minimum_required(VERSION 3.7)
project(Game)

IF (WIN32)

	set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2/Windows")
	# Support both 32 and 64 bit
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2/Windows/lib/x64/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2/Windows/lib/x64/SDL2main.lib")
	else ()
		set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2/Windows/lib/x86/SDL2.lib;${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2/Windows/lib/x86/SDL2main.lib")
	endif ()

	set(SDL2_IMAGE_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2_image/Windows")
	# Support both 32 and 64 bit
	if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
		set(SDL2_IMAGE_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2_image/Windows/lib/x64/SDL2_image.lib")
	else ()
		set(SDL2_IMAGE_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libraries/SDL2_image/Windows/lib/x86/SDL2_image.lib")
	endif ()

	set(Box2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/Box2D")
	set(Box2D_LIBRARY "${CMAKE_SOURCE_DIR}/libraries/Box2D/Box2D.lib")
	set(RapidXML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/rapidxml")

ELSE()

	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Linux")
	
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
	set(Box2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/Box2D")
	set(Box2D_LIBRARY "${CMAKE_SOURCE_DIR}/libraries/Box2D/libBox2D.a")
	set(RapidXML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/rapidxml")
	
ENDIF()



# Create PACKED folder under /build that contains the packed game
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/PACKED)

include_directories(engine/include game/include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${Box2D_INCLUDE_DIR} ${RapidXML_INCLUDE_DIR})

file(GLOB ENGINE_SOURCES "engine/src/*.cpp")
file(GLOB GAME_SOURCES "game/src/*.cpp")

add_executable(game ${ENGINE_SOURCES} ${GAME_SOURCES})
target_link_libraries(game ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${Box2D_LIBRARY})

# Copy game/data
add_custom_command(TARGET game PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/game/data $<TARGET_FILE_DIR:game>)

