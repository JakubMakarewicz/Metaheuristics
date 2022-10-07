cmake_minimum_required(VERSION 3.23)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 14)

add_executable(Metaheuristics main.cpp src/DataLoader.cpp src/DataLoader.h src/DataStructure.cpp src/DataStructure.h src/Node.cpp src/Node.h src/Item.cpp src/Item.h src/Specimen.cpp src/Specimen.h src/Mutator.cpp src/Mutator.h src/Selector.cpp src/Selector.h src/Crossoverer.cpp src/Crossoverer.h src/Evaluator.cpp src/Evaluator.h)
