//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Agent.h"

Agent::Agent(int x, int y) : x(x), y(y) {
    Agent::x = x;
    Agent::y = y;
    Agent::collectedFood = 0.0;
}

int Agent::getX() const {
    return x;
}

int Agent::getY() const {
    return y;
}

float Agent::getCollectedFood() const {
    return collectedFood;
}

void Agent::stepMove() {
    //TODO check world limits
    int direction = rand() % 4;
    switch (direction) {
        case 0:
            Agent::moveUp();
            break;
        case 1:
            Agent::moveDown();
            break;
        case 2:
            Agent::moveRight();
            break;
        case 3:
            Agent::moveLeft();
            break;
    }
}

void Agent::moveUp() {
    Agent::y = (Agent::getY() + 1);
}

void Agent::moveDown() {
    Agent::y = (Agent::getY() - 1);
}

void Agent::moveRight() {
    Agent::x = (Agent::getX() + 1);
}

void Agent::moveLeft() {
    Agent::x = (Agent::getX() - 1);
}