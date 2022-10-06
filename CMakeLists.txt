cmake_minimum_required(VERSION 3.23)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 14)

add_executable(Metaheuristics main.cpp dataLoader/DataLoader.cpp dataLoader/DataLoader.h dataLoader/DataStructure.cpp dataLoader/DataStructure.h dataLoader/Node.cpp dataLoader/Node.h dataLoader/Item.cpp dataLoader/Item.h)
