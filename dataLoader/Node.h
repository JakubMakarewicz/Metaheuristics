//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_NODE_H
#define METAHEURISTICS_NODE_H


class Node {
public:
    int index;
    int x;
    int y;
    double getDistance(Node other);
private:

};


#endif //METAHEURISTICS_NODE_H
