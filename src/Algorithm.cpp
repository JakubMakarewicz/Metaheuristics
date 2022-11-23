#include "Algorithm.h"
#include "RandomGenerators.h"

void Algorithm::Run(){
	this->Initialize();
    this->SaveGenerationResult();

	while (this->CanRun()) {
        this->currentGeneration++;

		this->RunIteration();

        this->SaveGenerationResult();
        std::cout << this->id << "|" << this->currentGeneration << '\n';
	}
	this->Log();
}

void Algorithm::Log(){
	std::ofstream logFile;
    logFile.open(this->config->outputFolderPath + "/" + std::to_string(this->id) + ".csv");
    for (int i = 0; i < this->currentGeneration; i++) {
        logFile << std::fixed<< this->goats.at(i) << ',' << this->bestSpecimens.at(i) << ',' << this->worstSpecimens.at(i) << ',' << this->averageScores.at(i)<< ','<<i;
        logFile << '\n';
    }
	logFile.close();
}

void Algorithm::Initialize()
{
    this->population = std::make_unique<std::vector<Specimen*>>();
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
}

void Algorithm::SaveGenerationResult() {
    if (this->population->size() == 0)
        return;
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
    if (this->goats.size() == 0)
        this->goats.push_back(this->population->at(bestIndex)->fitness);
    else if (this->population->at(bestIndex)->fitness > this->goats.back())
        this->goats.push_back(this->population->at(bestIndex)->fitness);
    else this->goats.push_back(this->goats.back());
    this->bestSpecimens.push_back(this->population->at(bestIndex)->fitness);
    this->worstSpecimens.push_back(this->population->at(worstIndex)->fitness);
    this->averageScores.push_back(sum/this->config->populationSize);
}

Algorithm::Algorithm(Config& config, DataStructure& data, RandomGenerators& rand)
{
    this->config = &config;
    this->data = &data;
    this->rand = &rand;
    this->crossoverer = Crossoverer::GenerateCrossoverer(config.crossoverer, config.crossoverProbability, rand);
    this->mutator = Mutator::GenerateMutator(config.mutator, this->config, rand);
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
    else if (config.algorithm == "TABOO") {
        TabooSearch* algorithm = new TabooSearch{ config, data,rand };
        return algorithm;
    }
    else if (config.algorithm == "SA") {
        SimulatedAnnealing* algorithm = new SimulatedAnnealing{ config, data,rand };
        return algorithm;
    }
    else if (config.algorithm == "GEA") {
        GenderedEA* algorithm = new GenderedEA{ config, data,rand };
        return algorithm;
    }
    else if (config.algorithm == "EAL") {
        EAL* algorithm = new EAL{ config, data,rand };
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
    this->population = this->selector->RunSelection(*this->population);
    for (int i = 0; i < this->population->size()-1; i += 2) {
        this->crossoverer->Cross(*this->population->at(i), *this->population->at(i+1));
    }
    for (int i = 0; i < this->population->size(); i++) {
        this->mutator->MutateSpecimen(*this->population->at(i));
        if (this->config->generateGreedyKnapsackPostCross)
            this->specimenFactory->GenerateGreedyItems(*this->population->at(i));
        if (this->config->mutateKnapsack)
            this->mutator->MutateKnapsack(*this->population->at(i));
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
    }
    this->EndOfGenerationAction();
}

void TabooSearch::FindNeighbourhood()
{
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* spec = new Specimen();
        spec->CopyNodeGenome(*this->currentSpecimen);
        this->mutator->MutateSpecimen(*spec);
        bool inTaboo=false;
        for (auto const& i: this->taboo) {
            if (spec->IsNodeGenomeSame(*i)) {
                inTaboo = true;
                break;
            }
        }
        if (inTaboo) {
            delete spec;
            continue;
        }
        if (this->config->generateGreedyKnapsackPostCross)
            this->specimenFactory->GenerateGreedyItems(*spec);
        this->population->push_back(spec);
    }
}

void TabooSearch::Initialize() {
    this->currentSpecimen = new Specimen();
    this->specimenFactory->InitializeSpecimen(*this->currentSpecimen);
    this->currentGeneration = 0;
    this->population = std::make_unique<std::vector<Specimen*>>();
    this->evaluator->EvaluateSpecimen(*this->currentSpecimen);

}
void TabooSearch::RunIteration() {
    for (int i = 0; i < this->population->size(); i++)
        delete this->population->at(i);
    this->population->clear();
    this->FindNeighbourhood();
    double maxScore = INT_MIN;
    int bestIndex = 0;
    for (int i = 0; i < this->population->size();i++) {
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
        if (this->population->at(i)->fitness > maxScore) {
            maxScore = this->population->at(i)->fitness;
            bestIndex = i;
        }
    }
    delete this->currentSpecimen;
    this->currentSpecimen = new Specimen(*this->population->at(bestIndex));
    this->taboo.push_back(new Specimen(*this->population->at(bestIndex)));
    if (this->taboo.size() > this->config->tabooSize){
        delete this->taboo.front();
        this->taboo.pop_front();
    }
}

void SimulatedAnnealing::FindNeighbourhood()
{
    for (int i = 0; i < this->config->populationSize; i++) {
        Specimen* spec = new Specimen();
        spec->CopyNodeGenome(*this->currentSpecimen);
        this->mutator->MutateSpecimen(*spec);
        if (this->config->generateGreedyKnapsackPostCross)
            this->specimenFactory->GenerateGreedyItems(*spec);
        this->population->push_back(spec);
    }
}

void SimulatedAnnealing::Initialize() {
    this->currentSpecimen = new Specimen();
    this->specimenFactory->InitializeSpecimen(*this->currentSpecimen);
    this->evaluator->EvaluateSpecimen(*this->currentSpecimen);
    this->currentGeneration = 0;
    this->population = std::make_unique<std::vector<Specimen*>>();
}
void SimulatedAnnealing::RunIteration() {
    for (int i = 0; i < this->population->size(); i++)
        delete this->population->at(i);
    this->population->clear();
    this->FindNeighbourhood();
    double maxScore = INT_MIN;
    int bestIndex = 0;
    for (int i = 0; i < this->population->size();i++) {
        this->evaluator->EvaluateSpecimen(*this->population->at(i));
        if (this->population->at(i)->fitness > maxScore) {
            maxScore = this->population->at(i)->fitness;
            bestIndex = i;
        }
    }
    if (maxScore > this->currentSpecimen->fitness) {
        delete this->currentSpecimen;
        this->currentSpecimen = new Specimen(*this->population->at(bestIndex));
    }
    else if (((*rand->distChance)(*rand->mt)) < std::exp(-(this->currentSpecimen->fitness - maxScore) / temperature)) {
        delete this->currentSpecimen;
        this->currentSpecimen = new Specimen(*this->population->at(bestIndex));
    }
    this->temperature = this->temperature * this->config->annealingRatio;
    std::cout << "Temp:" << this->temperature << '\n';
}

void SimulatedAnnealing::SaveGenerationResult()
{
    if (this->goats.size() == 0)
        this->goats.push_back(this->currentSpecimen->fitness);
    else if (this->currentSpecimen->fitness > this->goats.back())
        this->goats.push_back(this->currentSpecimen->fitness);
    else this->goats.push_back(this->goats.back());
    this->bestSpecimens.push_back(this->currentSpecimen->fitness);
    this->worstSpecimens.push_back(this->currentSpecimen->fitness);
    this->averageScores.push_back(this->currentSpecimen->fitness);
}


bool SimulatedAnnealing::CanRun() {
    bool test =  Algorithm::CanRun() && this->temperature > this->config->targetTemperature;
    return test;
}


void GenderedEA::SaveGenerationResult() {
    if (this->population[0]->size() == 0 && this->population[1]->size() == 0)
        return;

    std::array<int, 2> worstIndex{0,0};
    std::array<int, 2> bestIndex{ 0,0 };
    std::array<double, 2> bestScore{ INT_MIN,INT_MIN };
    std::array<double, 2> worstScore{ std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity() };

    std::array<double, 2> sum{ 0,0 };
    for (int gender = 0; gender < 2; gender++) {
        for (int i = 0; i < this->population[gender]->size(); i++) {
            Specimen* specimen = this->population[gender]->at(i);
            sum[gender] += specimen->fitness;
            if (specimen->fitness > bestScore[gender]) {
                bestScore[gender] = specimen->fitness;
                bestIndex[gender] = i;
            }
            if (specimen->fitness < worstScore[gender]) {
                worstScore[gender] = specimen->fitness;
                worstIndex[gender] = i;
            }
        }
    }
    double goat;
    if (bestScore[0] > bestScore[1])
        goat = bestScore[0];
    else goat = bestScore[1];

    if (this->goats.size() == 0)
        this->goats.push_back(goat);
    else if (goat > this->goats.back())
        this->goats.push_back(goat);
    else this->goats.push_back(this->goats.back());

    for (int gender = 0; gender < 2; gender++) {
        this->bestSpecimens[gender].push_back(this->population[gender]->at(bestIndex[gender])->fitness);
        this->worstSpecimens[gender].push_back(this->population[gender]->at(worstIndex[gender])->fitness);
        this->averageScores[gender].push_back(sum[gender] / this->config->populationSize);
    }
}

void GenderedEA::Initialize()
{
    this->population[0] = std::make_unique<std::vector<Specimen*>>();
    this->population[1] = std::make_unique<std::vector<Specimen*>>();
    this->currentGeneration = 0;
    for (int gender = 0; gender < 2; gender++)
        for (int i = 0; i < this->config->populationSize; i++) {
            Specimen* s = new Specimen();
            this->specimenFactory->InitializeSpecimen(*s);
            this->evaluator->EvaluateSpecimen(*s);
            this->population[gender]->push_back(s);
        }
}

void GenderedEA::RunIteration() {
    this->population[0] = this->selector->RunSelection(*this->population[0]);
    this->population[1] = this->selector->RunSelection(*this->population[1]);
    for (int i = 0; i < this->config->populationSize; i ++) {
        bool hadSex = this->crossoverer->Cross(*this->population[0]->at(i), *this->population[1]->at(i));
        // random gender of children
        if (hadSex && ((*rand->distChance)(*rand->mt) > 0.5)) {
            auto temp = this->population[0]->at(i);
            this->population[0]->at(i) = this->population[1]->at(i);
            this->population[1]->at(i) = temp;
        }
    }
    for (int gender = 0; gender < 2; gender++)
        for (int i = 0; i < this->population[gender]->size(); i++) {
            this->mutator->MutateSpecimen(*this->population[gender]->at(i));
            if (this->config->generateGreedyKnapsackPostCross)
                this->specimenFactory->GenerateGreedyItems(*this->population[gender]->at(i));
            if (this->config->mutateKnapsack)
                this->mutator->MutateKnapsack(*this->population[gender]->at(i));
            this->evaluator->EvaluateSpecimen(*this->population[gender]->at(i));
        }
}

void GenderedEA::Log() {
    std::ofstream logFile;
    logFile.open(this->config->outputFolderPath + "/" + std::to_string(this->id) + ".csv");
    logFile << "goat,best0,worst0,avg0,best1,worst1,avg1,generation";
    logFile << '\n';
    for (int i = 0; i < this->currentGeneration; i++) {
        logFile << std::fixed << this->goats.at(i) << ',' << this->bestSpecimens[0].at(i) << ',' << this->worstSpecimens[0].at(i) << ',' << this->averageScores[0].at(i) << ',' << this->bestSpecimens[1].at(i) << ',' << this->worstSpecimens[1].at(i) << ',' << this->averageScores[1].at(i) << ','<< i;
        logFile << '\n';
    }
    logFile.close();
}

void EAL::EndOfGenerationAction(){
    if (generationsUntilLocalSearch == 0) {
        std::vector<Specimen*> localSearch;
        std::sample(
            population->begin(),
            population->end(),
            std::back_inserter(localSearch),
            config->EALLocalSearchSpecimens,
            std::mt19937(std::random_device()())
        );
        for (int i = 0; i < localSearch.size(); i++) {
            Run2OptLocalSearch(*localSearch.at(i));
        }
        generationsUntilLocalSearch = config->EALLocalSearchInterval;
    }
    else generationsUntilLocalSearch--;
}

void EAL::Run2OptLocalSearch(Specimen& specimen){
    bool foundImprovement = true;
    Specimen spec;
    spec.CopyNodeGenome(specimen);
    int runCount = 0;
    while ((config->runsOf2Opt == -1 && foundImprovement) || runCount <= config->runsOf2Opt) {
        runCount++;
        foundImprovement = false;
        int n = spec.nodeGenome.size();
        for (int i = 0; i <= n - 2; i++) {
            for (int j = i + 1; j <= n - 1; j++) {
                double lengthDelta =
                    -data->nodeAdjacencyMatrix.at(spec.nodeGenome.at(i)).at(spec.nodeGenome.at((i + 1) % n))
                    - data->nodeAdjacencyMatrix.at(spec.nodeGenome.at(j)).at(spec.nodeGenome.at((j + 1) % n))
                    + data->nodeAdjacencyMatrix.at(spec.nodeGenome.at(i)).at(spec.nodeGenome.at(j))
                    + data->nodeAdjacencyMatrix.at(spec.nodeGenome.at((i + 1) % n)).at(spec.nodeGenome.at((j + 1) % n));
                if (lengthDelta < 0) {
                    std::reverse(spec.nodeGenome.begin() + i + 1, spec.nodeGenome.begin() + j + 1);
                    foundImprovement = true;
                }
            }
        }
    }
    this->specimenFactory->GenerateGreedyItems(spec);
    this->evaluator->EvaluateSpecimen(spec);
    if (spec.fitness > specimen.fitness) {
        specimen.fitness = spec.fitness;
        if (config->EALSetGenome)
            specimen.CopyNodeGenome(spec);
    }
}
