cmake_minimum_required(VERSION 3.9)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(snake DESCRIPTION "Snake game" LANGUAGES CXX VERSION 0.1.0)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
                     ${SDL2_INCLUDE_DIR}
                     ${SDL2_IMAGE_INCLUDE_DIR}
                     ${SDL2_TTF_INCLUDE_DIR}
                     ${SDL2_MIXER_INCLUDE_DIRS}
)

set(SOURCES
	src/main.cpp
	src/gamestate.cpp
	src/intro.cpp
	src/mainwindow.cpp
	src/font.cpp
	src/exception.cpp
	src/texture.cpp
	src/game.cpp
	src/node.cpp
	src/object.cpp
	src/utils.cpp
	src/listener.cpp
	src/collisionListener.cpp
	src/food.cpp
	src/music.cpp
	src/audioListener.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        $<$<CONFIG:Debug>:
            -O0 -Wall -Wextra -Weffc++ -Werror -pedantic-errors -g>
        $<$<CONFIG:Release>:
	    -O3 -Wall -pipe -march=native>>
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Debug>:/Od /Wall /Zi>>
)

add_definitions("-g")

target_link_libraries(${PROJECT_NAME}
                      ${SDL2_LIBRARY}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES}
                      ${SDL2_MIXER_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

