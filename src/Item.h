//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_ITEM_H
#define METAHEURISTICS_ITEM_H


class Item {
public:
    int index;
    double profit;
    double weight;
    int node;
    Item(){index=0;profit=0;weight=0;node=0;}
    Item(const Item& other){this->weight=other.weight;this->index=other.index;this->profit=other.profit;this->node=other.node;}
};


#endif //METAHEURISTICS_ITEM_H
