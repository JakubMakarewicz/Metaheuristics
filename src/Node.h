//
// Created by kuba on 10/6/22.
//

#ifndef METAHEURISTICS_NODE_H
#define METAHEURISTICS_NODE_H


class Node {
public:
    Node(){index=0;x=0;y=0;}

    int index;
    double x;
    double y;
    double getDistance(const Node& other);
    Node(const Node& other);
private:

};


#endif //METAHEURISTICS_NODE_H
