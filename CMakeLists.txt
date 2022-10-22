cmake_minimum_required(VERSION 3.23)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(utils)

add_executable(Metaheuristics
        src/Algorithm.cpp
        src/Algorithm.h
        src/Config.h
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
        src/RandomGenerators.cpp
        src/RandomGenerators.h
        src/Selector.cpp
        src/Selector.h
        src/Specimen.cpp
        src/Specimen.h
        src/SpecimenFactory.cpp
        src/SpecimenFactory.h
        utils/bitwise.cpp
        utils/bitwise.h
        utils/fenwick_tree.cpp
        utils/fenwick_tree.h
        main.cpp)
