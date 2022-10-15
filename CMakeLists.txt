cmake_minimum_required(VERSION 3.23)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_executable(Metaheuristics
        src/Crossoverer.cpp
        src/Crossoverer.h
        src/DataLoader.cpp
        src/DataLoader.h
        src/DataStructure.cpp
        src/DataStructure.h
        src/Evaluator.cpp
        src/Evaluator.h
        src/Item.cpp
        src/Item.h
        src/Mutator.cpp
        src/Mutator.h
        src/Node.cpp
        src/Node.h
        src/Selector.cpp
        src/Selector.h
        src/Specimen.cpp
        src/Specimen.h
        main.cpp src/SpecimenFactory.cpp src/SpecimenFactory.h)
