cmake_minimum_required(VERSION 4.0)
project(123)

set(CMAKE_CXX_STANDARD 20)

add_executable(123 main.cpp
        game_model.h
        game_model.cpp
        game_view.h
        game_view.cpp
        simulation_controller.h
        simulation_controller.cpp
        field.h
        field.cpp
        point.h
        point.cpp)
