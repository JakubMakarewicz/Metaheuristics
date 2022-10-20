#include "Algorithm.h"
#include "RandomGenerators.h"

void Algorithm::Run(){
	this->Initialize();
	while (this->CanRun()) {
        this->currentGeneration++;

		this->RunIteration();

        this->SaveGenerationResult();

        std::cout << this->currentGeneration << '\n';
	}
	this->Log();
}

void Algorithm::Log(){
	std::ofstream logFile;
	logFile.open("/home/kuba/Source/Metaheuristics/example.csv");
    for (int i = 0; i < this->currentGeneration; i++) {
        logFile << std::fixed<< this->bestSpecimens.at(i).fitness << ',' << this->worstSpecimens.at(i).fitness << ',' << this->averageScores.at(i);
        logFile << '\n';
    }
	logFile.close();
}

void Algorithm::Initialize()
{
    this->population = new std::vector<Specimen*>();
//    this->population.clear();
    this->currentGeneration = 0;
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* s = new Specimen();
        this->specimenFactory->InitializeSpecimen(*s);
        this->evaluator->EvaluateSpecimen(*s);
        this->population->push_back(s);
    }
}

bool Algorithm::CanRun(){
    return this->currentGeneration < this->config->generationsCount;
    //return true;
}

void Algorithm::SaveGenerationResult() {
    double worstScore = std::numeric_limits<double>::infinity();
    int worstIndex=0;
    double bestScore = INT_MIN;
    int bestIndex=0;
    double sum=0;
    for (int i =0; i<this->population->size(); i++){
        Specimen* specimen = this->population->at(i);
        sum+=specimen->fitness;
        if (specimen->fitness > bestScore) {
            bestScore = specimen->fitness;
            bestIndex = i;
        }
        if (specimen->fitness < worstScore){
            worstScore = specimen->fitness;
            worstIndex = i;
        }
    }
    this->bestSpecimens.push_back(*this->population->at(bestIndex));
    this->worstSpecimens.push_back(*this->population->at(worstIndex));
    this->averageScores.push_back(sum/this->config->populationSize);
}

Algorithm::Algorithm(Config& config, DataStructure& data, RandomGenerators& rand)
{
    this->config = &config;
    this->data = &data;
    this->crossoverer = Crossoverer::GenerateCrossoverer(config.crossoverer, config.crossoverProbability, rand);
    this->mutator = Mutator::GenerateMutator(config.mutator, config.nodeMutationProbability, config.itemMutationProbability, config.mutateKnapsack, rand);
    this->selector = Selector::GenerateSelector(config.selector, config.tournamentBatchSize, rand);
    this->specimenFactory = SpecimenFactory::GenerateSpecimenFactory(config.factory, *this->data, rand);
    this->evaluator = new Evaluator(*this->data);
    this->currentGeneration = 0;
}

Algorithm* Algorithm::GenerateAlgorithm(Config& config, DataStructure& data, RandomGenerators& rand){
    if (config.algorithm == "NON_GENETIC"){
        NonGeneticAlgorithm* algorithm = new NonGeneticAlgorithm{config, data,rand};
        return algorithm;
    }
    else if (config.algorithm == "GENETIC") {
        GeneticAlgorithm* algorithm = new GeneticAlgorithm{ config, data,rand};
        return algorithm;
    }
}

void NonGeneticAlgorithm::RunIteration() {
    for (int i = 0; i<this->config->populationSize; i++){
        this->specimenFactory->InitializeSpecimen(*this->population->at(i));
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
    }
}

void GeneticAlgorithm::RunIteration() {
//    for (int i = 0; i < this->config->populationSize; i++) {
        this->population = this->selector->RunSelection(*this->population);
        for (int i = 0; i < this->population->size(); i += 2) {
            this->crossoverer->Cross(*this->population->at(i), *this->population->at(i));
        }
        for (int i = 0; i < this->population->size(); i++) {
            this->mutator->MutateSpecimen(*this->population->at(i));
            if (this->config->generateGreedyKnapsackPostCross)
                this->specimenFactory->GenerateGreedyItems(*this->population->at(i));
            if (this->config->mutateKnapsack)
                this->mutator->MutateKnapsack(*this->population->at(i));
            this->evaluator->EvaluateSpecimen(*this->population->at(i));
        }

//    }
}