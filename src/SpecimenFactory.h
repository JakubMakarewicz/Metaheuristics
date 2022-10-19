//
// Created by kuba on 10/13/22.
//

#ifndef METAHEURISTICS_SPECIMENFACTORY_H
#define METAHEURISTICS_SPECIMENFACTORY_H


#include "Specimen.h"
#include "DataStructure.h"
#include "RandomGenerators.h"

class RandomSpecimenFactory;
class GreedySpecimenFactory;
class SpecimenFactory {
public:
    RandomGenerators* rand;
    DataStructure data;

    SpecimenFactory(DataStructure& data, RandomGenerators& rand) { this->data = data; this->rand=&rand; }
    virtual void InitializeSpecimen(Specimen& specimen){}

    int GetClosest(int currentNode, std::vector<bool>& availableNodes) const;

    void GenerateGreedyItems(Specimen &specimen);

    static SpecimenFactory* GenerateSpecimenFactory(std::string specimenFactoryName, DataStructure& data, RandomGenerators& rand);

};
//
class RandomSpecimenFactory: public SpecimenFactory{
public:
    RandomSpecimenFactory(DataStructure& data, RandomGenerators& rand): SpecimenFactory(data,rand){}
    void InitializeSpecimen(Specimen& specimen) override;
};

class GreedySpecimenFactory: public SpecimenFactory{
public:
    GreedySpecimenFactory(DataStructure& data, RandomGenerators& rand): SpecimenFactory(data,rand){}
    void InitializeSpecimen(Specimen& specimen) override;
};
#endif //METAHEURISTICS_SPECIMENFACTORY_H
