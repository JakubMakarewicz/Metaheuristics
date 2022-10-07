//
// Created by kuba on 10/6/22.
//

#include "Node.h"
#include<cmath>

double Node::getDistance(const Node& other) {
    double xDist = pow((this->x - other.x),2);
    double yDist = pow((this->y - other.y),2);
    return pow(xDist + yDist, 0.5);
}

Node::Node(const Node &other) {
    this->index = other.index;
    this->x = other.x;
    this->y = other.y;
}
