cmake_minimum_required(VERSION 2.6)

project(lemmings)

set( SDL_BUILDING_LIBRARY false )

Find_Package( SDL REQUIRED )
Find_Package( SDL_image REQUIRED )
Find_Package( OpenGL REQUIRED )
find_package( GLUT REQUIRED )

if( NOT SDL_FOUND )
    message( FATAL ERROR "SDL not found!" )
endif( NOT SDL_FOUND )

if( NOT OPENGL_FOUND )
    message( FATAL ERROR "OpenGL not found!" )
endif( NOT OPENGL_FOUND )

if( NOT GLUT_FOUND )
    message( FATAL ERROR "GLUT not found!" )
endif( NOT GLUT_FOUND )


include_directories( ${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

link_libraries(
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${OPENGL_LIBRARY}
    ${GLUT_LIBRARY}
    SDLmain
)

file(
    GLOB
    source_files
    ${CMAKE_CURRENT_LIST_DIR}/../*.c
)

add_executable(
    lemmings
    ${source_files}
)

target_link_libraries( lemmings ${SDL_LIBS} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )