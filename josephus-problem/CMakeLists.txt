cmake_minimum_required(VERSION 3.16)
project(JosephusQt6 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(josephus_qt6 main.cpp)
target_link_libraries(josephus_qt6 PRIVATE Qt6::Widgets)
set_target_properties(josephus_qt6 PROPERTIES AUTOMOC ON)

