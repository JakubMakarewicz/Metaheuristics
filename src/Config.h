#pragma once
#include <string>
class Config {
public: 
	double crossoverProbability;
	double nodeMutationProbability;
	double itemMutationProbability;
	bool mutateKnapsack;
	bool generateGreedyKnapsackPostCross;
	int populationSize;
	int generationsCount;
	int tournametBatchSize;
	std::string selector;
	std::string crossoverer;
	std::string mutator;
	std::string factory;
	std::string dataFilePath;
};