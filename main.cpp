#include <iostream>
#include "DataLoader.h"
#include "Specimen.h"
#include "Evaluator.h"
#include "Selector.h"

int main() {
    DataLoader dataLoader;
    const int s = 10;
    int n = 10;
    int items = 9;
//    dataLoader.loadData("/home/kuba/Source/Metaheuristics/data/trivial_1.ttp"); // linux
    dataLoader.loadData("C:\\Users\\makaron\\CLionProjects\\Metaheuristics\\data\\trivial_1.ttp"); // windows
    std::vector<Specimen> pop;
    for (int i=0;i<s;i++){
        Specimen specimen(n, items);
        specimen.Randomize();
        pop.push_back(specimen);
    }

    Evaluator evaluator;
    evaluator.data = dataLoader.data;

    RouletteSelector rouletteSelector;
    auto pop2= rouletteSelector.RunSelection(pop,evaluator);

    std::sort(pop.begin(), pop.end());
    std::sort(pop2.begin(), pop2.end());

    for (int i =0; i<s; i++){
        std::cout<<pop[i].fitness<<" | "<<pop2[i].fitness <<"\n";
    }
//    evaluator.EvaluateSpecimen(specimen);
    return 0;
}
