#include <iostream>
#include "DataLoader.h"
#include "Specimen.h"
#include "Algorithm.h"
#include "RandomGenerators.h"
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>




int main() {
    DataLoader dataLoader;
    dataLoader.loadConfig(".\\configs\\config1.txt");
    //dataLoader.loadConfig("/home/kuba/Source/Metaheuristics/configs/config1.txt");
    dataLoader.loadData(dataLoader.config.dataFilePath);
    RandomGenerators rand;
    std::vector<double> bests;
    std::vector<double> worsts;
    std::vector<double> avgs;
    std::filesystem::remove_all(dataLoader.config.outputFolderPath.c_str());
    std::filesystem::create_directories(dataLoader.config.outputFolderPath);
    for (int i = 0; i < dataLoader.config.tries; i++) {
        rand.Init(dataLoader.data);
        //NonGeneticAlgorithm* algorithm = new NonGeneticAlgorithm(dataLoader.config, dataLoader.data);
        Algorithm* algorithm = Algorithm::GenerateAlgorithm(dataLoader.config, dataLoader.data, rand);
        algorithm->id = i;
        algorithm->Run();
        bests.push_back(algorithm->goats.back());
        delete algorithm;
    }
    std::ofstream logFile;
    logFile.open(dataLoader.config.outputFolderPath + "/results.csv");
    // get best, first,
    for (int i = 0; i < dataLoader.config.tries; i++) {
        logFile << std::fixed << bests.at(i) << ',' << i;
        logFile << '\n';
    }
    logFile.close();
    //int i =0;

    //dataLoader.loadData("/home/kuba/Source/Metaheuristics/data/trivial_1.ttp"); // linux
//    dataLoader.loadData("C:\\Users\\makaron\\CLionProjects\\Metaheuristics\\data\\trivial_1.ttp"); // windows
//    std::vector<Specimen> pop;
//
//    GreedySpecimenFactory factory(& dataLoader.data );
//
//    for (int i=0;i<s;i++){
//        Specimen specimen(n, items);
//        factory.InitializeSpecimen(specimen);
//        pop.push_back(specimen);
//    }
//
//    Evaluator evaluator;
//    evaluator.data = dataLoader.data;
//    for (auto & i : pop)
//        evaluator.EvaluateSpecimen(i);
//    RouletteSelector rouletteSelector;
//    auto pop2= rouletteSelector.RunSelection(pop);
//
//    std::sort(pop.begin(), pop.end());
//    std::sort(pop2.begin(), pop2.end());
//
//
//    for (int i =0; i<s; i++){
//        std::cout<<pop[i].fitness<<" | "<<pop2[i].fitness <<"\n";
//    }
////    evaluator.EvaluateSpecimen(specimen);
//
//    PMXCrossoverer cross;
//    Specimen lhs{};
//    std::array lhsnodes{1,2,3,4,5,6};
//    Specimen rhs{};
//    std::array rhsnodes{1,3,5,4,6,2};
//    for (int i = 0; i<6;i++){
//        lhs.nodeGenome.push_back(lhsnodes.at(i));
//        rhs.nodeGenome.push_back(rhsnodes.at(i));
//    }
//    cross.Cross(lhs,rhs);


    return 0;
}
