cmake_minimum_required(VERSION 3.6)
project(SimulacaoServidor)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Aluno.h Aluno.cpp)
add_executable(SimulacaoServidor ${SOURCE_FILES})