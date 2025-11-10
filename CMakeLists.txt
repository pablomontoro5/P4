cmake_minimum_required(VERSION 4.0)
project(P4)

set(CMAKE_CXX_STANDARD 26)

add_executable(P4 main.cpp Laboratorio.h Laboratorio.cpp MediExpress.h MediExpress.cpp PA_Medicamento.h PA_Medicamento.cpp
        Farmacia.h
        Farmacia.cpp
)
