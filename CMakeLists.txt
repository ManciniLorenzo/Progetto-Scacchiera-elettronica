# Lorenzo Mancini
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(scacchiera VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-O2")
include_directories(include)

add_library(master_comp
    include/Scacchiera.h
    src/Scacchiera.cpp  
    include/Re.h
    src/Re.cpp 
    include/Regina.h
    src/Regina.cpp 
    include/Alfiere.h
    src/Alfiere.cpp 
    include/Cavallo.h
    src/Cavallo.cpp
    include/Torre.h
    src/Torre.cpp
    include/Pedone.h
    src/Pedone.cpp
    include/Giocatore.h
    src/Giocatore.cpp 
    include/Computer.h
    src/Computer.cpp 
    include/Log.h
    src/Log.cpp
    include/Scacchista.h
    include/Posizione.h
    include/Pezzo.h
)

add_executable(scacchiera src/mainScacchiera.cpp)
add_executable(replay src/mainReplay.cpp)

target_link_libraries(scacchiera master_comp)
target_link_libraries(replay master_comp)