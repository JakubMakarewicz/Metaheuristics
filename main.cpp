#include <iostream>
#include "DataLoader.h"
#include "Specimen.h"
#include "Evaluator.h"
#include "Selector.h"
#include "SpecimenFactory.h"
#include "Crossoverer.h"

bool es() { 
    for (int i = 0; i < 2147483647; i++) {
        if ((i ^ 123) == -23)
            return true;
    }
    return false;
}

int main() {
    bool es = 0;
    //if (es()) { std::cout << "found"; }
    //else { std::cout << "ended"; }
    DataLoader dataLoader;
    const int s = 10;
    int n = 10;
    int items = 9;
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
