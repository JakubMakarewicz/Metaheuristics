//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_ITEM_H
#define METAHEURISTICS_ITEM_H


class Item {
public://
    int index;
    double profit;
    double weight;
    double profitMargin;
    int node;
    Item(){index=0;profit=0;weight=0;node=0;}

    Item(int index, double profit, double weight, int node) : index(index), profit(profit), weight(weight),
                                                              node(node) {this->profitMargin = profit/weight;}

    bool operator<(const Item &rhs) const { // TODO: test this
        return profitMargin < rhs.profitMargin;
    }

    bool operator>(const Item &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Item &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Item &rhs) const {
        return !(*this < rhs);
    }

    Item(const Item& other){this->weight=other.weight;this->index=other.index;this->profit=other.profit;this->node=other.node;this->profitMargin=other.profitMargin;}
};


#endif //METAHEURISTICS_ITEM_H
