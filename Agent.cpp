//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Agent.h"
#include "World.h"

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

void Agent::stepMove(World world1) {
    int direction = rand() % 4;
    switch (direction) {
        case 0:
            if(Agent::getY() < world1.getY())
            {
                Agent::moveUp();
            }else{
                Agent::moveDown();
            }
            break;
        case 1:
            if(Agent::getY() > 0){
                Agent::moveDown();
            }else{
                Agent::moveUp();
            }
            break;
        case 2:
            if(Agent::getX() < world1.getX()){
                Agent::moveRight();
            }else{
                Agent::moveLeft();
            }
            break;
        case 3:
            if(Agent::getX() > 0){
                Agent::moveLeft();
            }else{
                Agent::moveRight();
            }
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