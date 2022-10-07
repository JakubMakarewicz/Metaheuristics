#include <iostream>
#include "DataLoader.h"
#include "Specimen.h"
#include "Evaluator.h"

int main() {
    DataLoader dataLoader;
    dataLoader.loadData("/home/kuba/Source/Metaheuristics/data/trivial_1.ttp");

    Specimen<10,9> specimen;

    Evaluator<10,9> evaluator;
    evaluator.data = dataLoader.data;
    evaluator.EvaluateSpecimen(specimen);
    return 0;
}
