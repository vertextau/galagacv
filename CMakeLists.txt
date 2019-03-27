cmake_minimum_required(VERSION 3.1.0)

project(galagacv)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(galagacv_srcs
    src/background_stars.cpp
    src/background_stars.h
    src/base.cpp
    src/base.h
    src/bomber.cpp
    src/bomber.h
    src/camera_controller.cpp
    src/camera_controller.h
    src/camera_initializer.cpp
    src/camera_initializer.h
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/settings.h
    src/spacebug.cpp
    src/spacebug.h
    src/spaceship.cpp
    src/spaceship.h
    src/sprite.cpp
    src/sprite.h
    src/game_board.cpp
    src/game_board.h
)

add_executable(galagacv ${galagacv_srcs})

target_link_libraries(galagacv Qt5::Widgets ${OpenCV_LIBS})
