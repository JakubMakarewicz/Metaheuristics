//
// Created by kuba on 10/6/22.
//

#include "Node.h"

double Node::getDistance(Node other) {
    int xDist = (this->x - other.x)^2;
    int yDist = (this->y - other.y)^2;
    return (xDist + yDist)
}