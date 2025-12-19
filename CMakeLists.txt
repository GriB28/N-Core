cmake_minimum_required(VERSION 4.1)
project(N-Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/.release")

set(RENDER_ICON TRUE)  # для добавления иконки на итоговый бинарник
if (RENDER_ICON)
    enable_language(RC)
    set(CMAKE_RC_COMPILER "D:/Developing/.mingw/bin/windres.exe")
endif()

set(SFML_DIR "D:/Developing/.lib/SFML-2.6.2-shared-self-compiled")

find_package(
        SFML 2.6
        PATHS "${SFML_DIR}/lib/cmake/SFML"
        REQUIRED
        COMPONENTS audio graphics window network system
)

set(SOURCES
        main.cpp
        game.cpp

        level/object.cpp
        level/generator.cpp
        level/platform.cpp
        level/ladder.cpp
        level/void.cpp

        player/player.cpp

        scenes/scene.cpp
        scenes/loading.cpp
        scenes/main_menu.cpp
        scenes/level.cpp
        scenes/chapter_layout.cpp

        source/fonts.cpp
        source/music.cpp

        utils/button.cpp
        utils/numeric.cpp
)

if (RENDER_ICON)
    list(APPEND SOURCES icon.rc)
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${SFML_DIR}/include")
target_link_libraries(
        ${PROJECT_NAME}
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
)
