#pragma once
#include <string>
class Config {
public: 
	double crossoverProbability;
    double specimenNodeGenomeMutationProbability;
	double nodeMutationProbability;
	double itemMutationProbability;
	double annealingRatio;
	double startingTemperature;
	double targetTemperature;
	bool mutateKnapsack;
	bool generateGreedyKnapsackPostCross;
	bool mutateOnlyOnce;
	int populationSize;
	int generationsCount;
	int tournamentBatchSize;
	int tabooSize;
	std::string selector;
	std::string crossoverer;
	std::string mutator;
	std::string factory;
	std::string dataFilePath;
    std::string algorithm;
    std::string outputFilePath;
    //TODO: place random engines here
};