PROJECT(tests)

cmake_minimum_required(VERSION 3.6)
set(CMAKE_BUILD_TYPE Debug)
FILE(TO_CMAKE_PATH "$ENV{HOME}" HOME)
set(LOCAL_LIBS_DIR ${HOME}/opt)
set(DEV ${HOME}/dev)
set(EXTERNAL ${DEV}/external)
set (gtest_dir  ${EXTERNAL}/googletest/googletest)

ADD_DEFINITIONS(-Werror)

link_libraries (
  -lpthread
  dl
  #-ljpeg
  #-lpng
  -lz
)

ADD_DEFINITIONS(-fpermissive)


include_directories(
${COMMON}/ThirdParties/tinyxml2
${gtest_dir}/
${gtest_dir}/include/
$<TARGET_PROPERTY:Draw2D,INTERFACE_INCLUDE_DIRECTORIES>
../src
./
)

ADD_EXECUTABLE(tests
${gtest_dir}/src/gtest-all.cc

../src/game/Level.cpp
../src/game/Board.cpp
../src/game/Game.cpp
../src/game/Blocks.cpp
../src/game/GameObject.cpp
../src/game/Player.cpp
../src/game/Bomb.cpp
../src/game/Explosion.cpp
../src/game/PowerUp.cpp
../src/game/Enemy.cpp

main.cpp
TestBoard.cpp
TestLevel.cpp
TestGameObject.cpp
${COMMON}/ThirdParties/tinyxml2/tinyxml2.cpp

)
target_link_libraries (tests
PRIVATE
  Logging)
