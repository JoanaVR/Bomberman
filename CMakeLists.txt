PROJECT(Bomberman)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

IF(CMAKE_HOST_WIN32)
  set(HOME  c:/Users/vladi)
ELSE(CMAKE_HOST_WIN32)
  FILE(TO_CMAKE_PATH "$ENV{HOME}" HOME)
ENDIF(CMAKE_HOST_WIN32)

set(DEV ${HOME}/dev)

message(">>> ${DEV}")

set(EXTERNAL ${DEV}/external)
set(COMMON ${DEV}/common)
set(LOCAL_LIBS_DIR ${HOME}/opt)
set(BOOST_LIB_ROOT ${HOME}/opt/lib)
set(BOOST_ROOT ${HOME}/opt/include)

add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
add_definitions(-DU_STATIC_IMPLEMENTATION)
add_definitions(-DU_ATTRIBUTE_DEPRECATED=)
add_definitions(-DU_COMMON_IMPLEMENTATION)

ADD_DEFINITIONS(-Werror)

IF(CMAKE_HOST_WIN32)
message(">> >aaaaaaaaaa ${DEV}")
  link_libraries (
    WS2_32.lib
  )
ELSE(CMAKE_HOST_WIN32)
  link_libraries (
    -lpthread
    dl
    -lrt
    -lGL
    -lSDL3
    -lSDL3_ttf
  )
ENDIF(CMAKE_HOST_WIN32)

IF(CMAKE_HOST_WIN32)
  set(SDL3_INCLUDE_DIRS ${EXTERNAL}/SDL3-2.0.12/include)
  include_directories(${EXTERNAL}/SDL3-2.0.12/)
  include_directories(${EXTERNAL}/SDL3_ttf-2.0.15/)
ELSE(CMAKE_HOST_WIN32)
  find_package(SDL3 REQUIRED)
  #include_directories(${COMMON}/Rava/Draw2D)
  #include_directories(${COMMON}/Rava/GUI)
ENDIF(CMAKE_HOST_WIN32)



add_subdirectory( ${COMMON}/Rava/Draw2D ${CMAKE_CURRENT_BINARY_DIR}/Draw2D )
add_subdirectory( ${COMMON}/Rava/GUI ${CMAKE_CURRENT_BINARY_DIR}/GUI )
add_subdirectory( ${COMMON}/Rava/AppBase ${CMAKE_CURRENT_BINARY_DIR}/AppBase )
add_subdirectory( ${COMMON}/Logging ${CMAKE_CURRENT_BINARY_DIR}/Logging )

ADD_EXECUTABLE(Bomberman
src/game/Board.cpp
src/game/Bomb.cpp
src/game/Blocks.cpp
src/game/Game.cpp
src/game/Level.cpp
src/game/Player.cpp
src/game/GameObject.cpp
src/game/Explosion.cpp

src/gameDraw/DrawObject.cpp
src/gameDraw/GameDrawer.cpp

src/Application.cpp

src/GUI/game/game_screen.cpp
src/AppSplashScreen.cpp

src/GUI/game/BoardWidget.cpp
src/GUI/game/menu_screen.cpp
src/GUI/game/game_over_screen.cpp
src/Utils/GuiFactory.cpp
${COMMON}/ThirdParties/tinyxml2/tinyxml2.cpp

)

target_include_directories(Bomberman 

    PRIVATE
    include
    ${COMMON}/ThirdParties/tinyxml2
    $<TARGET_PROPERTY:Draw2D,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:GUI,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:AppBase,INTERFACE_INCLUDE_DIRECTORIES>
    ./src
    )


target_link_libraries(Bomberman 
PRIVATE
Draw2D
GUI
AppBase
Logging
${SDL3_LIBRARIES} 
)

add_subdirectory(tests)
