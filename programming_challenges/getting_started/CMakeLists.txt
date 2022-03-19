cmake_minimum_required(VERSION 3.10)

# set the project name
project(programming_chanllenges)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# problem 1
add_executable(problem1 3n+1.cpp)

# problem 2
add_executable(problem2 minesweeper.cpp)

# problem 3
add_executable(problem3 the_trip.cpp)

# problem 4
add_executable(problem4 lcd_display.cpp)

# problem 5
add_executable(problem5 graphical_editor.cpp)

# problem 6
add_executable(problem6 interpreter.cpp)

# problem 7
add_executable(problem7 check_the_check.cpp)

# problem 8
add_executable(problem8 australian_voting.cpp)