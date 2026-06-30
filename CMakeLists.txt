cmake_minimum_required(VERSION 3.21)
project(ADC_project C)

set(CMAKE_C_STANDARD 99)

add_executable(ADC_project main.c io.c io.h ADC.c ADC.h stats.c stats.h)
