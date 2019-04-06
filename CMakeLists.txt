cmake_minimum_required(VERSION 3.7)
project(Game)

IF (WIN32) # WINDOWS

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

ELSE() # LINUX

	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Linux")
	IF (${BITS} MATCHES "64")
		set(SDL2_LIBRARY "/usr/lib/libSDL2.so")
		set(SDL2_IMAGE_LIBRARIES "/usr/lib/libSDL2_image.so")
		set(Box2D_LIBRARY "${CMAKE_SOURCE_DIR}/libraries/Box2D/lib/libBox2D.a")
	ELSE()
		message(WARNING "Did you remember to set the BITS variable? - 32bit selected (default) ...")
		set(SDL2_LIBRARY "/usr/lib32/libSDL2.so")
		set(SDL2_IMAGE_LIBRARIES "/usr/lib32/libSDL2_image.so")
		set(Box2D_LIBRARY "${CMAKE_SOURCE_DIR}/libraries/Box2D/lib32/libBox2D.a")
		set(CMAKE_CXX_FLAGS "-m32")
		set(CMAKE_EXE_LINKER_FLAGS "-m32")
	ENDIF()

	set(Box2D_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libraries/Box2D")
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

