cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(ffm+yt VERSION 1.1
               LANGUAGES CXX)



option(INCLUDE_YTDL "Enables YTDL library" 0)

add_library(inputlib STATIC src/Input.cpp include/project/Input.hpp)
target_include_directories(inputlib PUBLIC include/project)

add_library(outputlib STATIC src/Output.cpp include/project/Output.hpp)
target_include_directories(outputlib PUBLIC include/project)

add_library(mkvlib STATIC src/mkv.cpp include/project/mkv.hpp)
target_include_directories(mkvlib PUBLIC include/project)

add_library(mp4lib STATIC src/mp4.cpp include/project/mp4.hpp)
target_include_directories(mp4lib PUBLIC include/project)

add_library(webmlib STATIC src/webm.cpp include/project/webm.hpp)
target_include_directories(webmlib PUBLIC include/project)

add_library(timehandlerlib STATIC src/timeHandler.cpp include/project/timeHandler.hpp)
target_include_directories(timehandlerlib PUBLIC include/project)

if(INCLUDE_YTDL)
add_compile_definitions(INCLUDE_YTDL)
add_library(YTDL STATIC src/YTDL.cpp include/project/YTDL.hpp)
target_include_directories(YTDL PUBLIC include/project)
endif()

add_executable(encoder main.cpp)
if(INCLUDE_YTDL)
target_link_libraries(encoder PUBLIC inputlib outputlib mkvlib mp4lib webmlib timehandlerlib YTDL)
else()
target_link_libraries(encoder PUBLIC inputlib outputlib mkvlib mp4lib webmlib timehandlerlib)
endif()

set_target_properties(encoder PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../bin")
