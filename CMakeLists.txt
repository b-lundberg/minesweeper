cmake_minimum_required(VERSION 3.10)
project(minesweeper C)
add_executable(${PROJECT_NAME} src/main.c src/board.c src/board_renderer.c)
target_link_libraries(${PROJECT_NAME} raylib)
