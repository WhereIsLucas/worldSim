//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "World.h"

Creature::Creature(int positionX, int positionY) : x(positionX), y(positionY) {
    Creature::x = positionX;
    Creature::y = positionY;
    Creature::collectedFood = 0.0;
}

int Creature::getX() const {
    return x;
}

int Creature::getY() const {
    return y;
}

float Creature::getCollectedFood() const {
    return collectedFood;
}

void Creature::stepMove(World world1) {
    int direction = rand() % 4;
    switch (direction) {
        case 0:
            if(Creature::getY() < world1.getY()-1)
            {
                Creature::moveUp();
            }else{
                Creature::moveDown();
            }
            break;
        case 1:
            if(Creature::getY() > 0){
                Creature::moveDown();
            }else{
                Creature::moveUp();
            }
            break;
        case 2:
            if(Creature::getX() < world1.getX()-1){
                Creature::moveRight();
            }else{
                Creature::moveLeft();
            }
            break;
        case 3:
            if(Creature::getX() > 0){
                Creature::moveLeft();
            }else{
                Creature::moveRight();
            }
            break;
    }
}

void Creature::moveUp() {
    Creature::y = (Creature::getY() + 1);
}

void Creature::moveDown() {
    Creature::y = (Creature::getY() - 1);
}

void Creature::moveRight() {
    Creature::x = (Creature::getX() + 1);
}

void Creature::moveLeft() {
    Creature::x = (Creature::getX() - 1);
}

void Creature::setCollectedFood(float collectedFoodArg) {
    Creature::collectedFood = collectedFoodArg;
}
