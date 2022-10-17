#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SpecimenFactory.cpp>
#include <Crossoverer.cpp>
#include <Mutator.cpp>
#include <Selector.cpp>
#include "Config.h"
#include <DataLoader.cpp>
class Algorithm {
public: 
	Crossoverer* crossoverer;
	Mutator* mutator;
	Selector* selector;
	SpecimenFactory* specimenFactory;
	DataStructure* data;
	Config* config;
    Evaluator* evaluator;

    std::vector<std::reference_wrapper<Specimen>> population; // TODO: use reference vector
    std::vector<Specimen> bestSpecimens;
    std::vector<Specimen> worstSpecimens;
    std::vector<double> averageScores;

    int currentGeneration;

	Algorithm(Config& config, DataStructure& data) {
        this->config = &config;
        this->data = &data;
		this->crossoverer = &Crossoverer::GenerateCrossoverer(config.crossoverer);
		this->mutator = &Mutator::GenerateMutator(config.mutator, config.nodeMutationProbability, config.itemMutationProbability, config.mutateKnapsack);
		this->selector = &Selector::GenerateSelector(config.selector, config.tournamentBatchSize);
		this->specimenFactory = &SpecimenFactory::GenerateSpecimenFactory(config.factory, *this->data);
        this->evaluator = new Evaluator();
	}

    static Algorithm& GenerateAlgorithm(Config& config, DataStructure& data);

    virtual void Run();
private:
	virtual void RunIteration();
	virtual void Initialize();
	virtual bool CanRun();
	virtual void Log();
    virtual void SaveGenerationResult();
};

class NonGeneticAlgorithm: public Algorithm{
public:
    NonGeneticAlgorithm(Config& config, DataStructure& data): Algorithm(config, data){}
    void RunIteration() override;
};