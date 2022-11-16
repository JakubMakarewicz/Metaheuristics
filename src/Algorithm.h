#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include "SpecimenFactory.h"
#include "Crossoverer.h"
#include "Mutator.h"
#include "Selector.h"
#include "Config.h"
#include "DataLoader.h"
#include "RandomGenerators.h"

class Algorithm {
public: 
	Crossoverer* crossoverer;
	Mutator* mutator;
	Selector* selector;
	SpecimenFactory* specimenFactory;
	DataStructure* data;
	Config* config;
    Evaluator* evaluator;
	RandomGenerators* rand;

	std::unique_ptr<std::vector<Specimen*>> population;
	std::vector<double> goats;
    std::vector<double> bestSpecimens;
    std::vector<double> worstSpecimens;
    std::vector<double> averageScores;

    int currentGeneration;
	int id;
	Algorithm(Config& config, DataStructure& data, RandomGenerators& rand);
	~Algorithm() {
		goats.clear();
		bestSpecimens.clear();
		worstSpecimens.clear();
		averageScores.clear();
	}
    static Algorithm* GenerateAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand);

    void Run();
protected:
	virtual void RunIteration()=0;
	virtual void Initialize();
	virtual bool CanRun();
	virtual void Log();
	virtual void SaveGenerationResult();
};

class NonGeneticAlgorithm: public Algorithm{
public:
    NonGeneticAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand): Algorithm(config, data,rand){}
protected:
	void RunIteration() override;
};

class GeneticAlgorithm : public Algorithm {
public:
	GeneticAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand) : Algorithm(config, data,rand) {}
protected:
	void RunIteration() override;
};

class TabooSearch : public Algorithm {
public:
	Specimen* currentSpecimen;
	std::list<Specimen*> taboo;
	TabooSearch(Config& config, DataStructure& data, RandomGenerators& rand) : Algorithm(config, data,rand) {}
protected:
	void FindNeighbourhood();
	void Initialize() override;
	void RunIteration() override;
};

class SimulatedAnnealing: public Algorithm {
public:
    Specimen* currentSpecimen;
	double temperature = 0;
	SimulatedAnnealing(Config& config, DataStructure& data, RandomGenerators& rand) : Algorithm(config, data, rand) { this->temperature = config.startingTemperature; }
protected:
	bool CanRun();
    void FindNeighbourhood();
    void Initialize() override;
    void RunIteration() override;
	void SaveGenerationResult() override;
};