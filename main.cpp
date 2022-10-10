#include <iostream>
#include "DataLoader.h"
#include "Specimen.h"
#include "Evaluator.h"
#include "Selector.h"

int main() {
    DataLoader dataLoader;
    const int s = 10;
    dataLoader.loadData("/home/kuba/Source/Metaheuristics/data/trivial_1.ttp");
    std::array<Specimen<10,9>, s> pop;
    for (int i=0;i<s;i++){
        Specimen<10,9> specimen;
        specimen.Randomize();
        pop[i]=specimen;
    }

    Evaluator<10,9> evaluator;
    evaluator.data = dataLoader.data;

    RouletteSelector<10,9,s> rouletteSelector;
    auto pop2= rouletteSelector.RunSelection(pop,evaluator);

    std::sort(pop.begin(), pop.end());
    std::sort(pop2.begin(), pop2.end());

    for (int i =0; i<s; i++){
        std::cout<<pop[i].fitness<<" | "<<pop2[i].fitness <<"\n";
    }
//    evaluator.EvaluateSpecimen(specimen);
    return 0;
}
