cmake_minimum_required(VERSION 3.27)
project(fifteen)
set(CMAKE_CXX_STANDARD 20)

INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_Image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(fifteen main.cpp)
target_include_directories(fifteen PRIVATE include)
if(MSVC)
  target_compile_options(fifteen PRIVATE /W4 /WX)
else()
  target_compile_options(fifteen PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
  
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(fifteen PRIVATE SDL2::SDL2)
target_link_libraries(fifteen PRIVATE SDL2_image::SDL2_image)
target_link_libraries(fifteen PRIVATE SDL2_ttf::SDL2_ttf)