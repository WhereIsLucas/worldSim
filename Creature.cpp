//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "World.h"
#include "Vector2.h"


float Creature::getCollectedFood() const {
    return collectedFood;
}

void Creature::stepMove(World world1) {
    //TODO
}


void Creature::setCollectedFood(float collectedFoodArg) {
    Creature::collectedFood = collectedFoodArg;
}

Creature::Creature(Vector2 &position) {
    Creature::position = position;
    Creature::velocity = Vector2(0,0);
    Creature::collectedFood = 0;
}

const Vector2 &Creature::getPosition() const {
    return position;
}

const Vector2 &Creature::getVelocity() const {
    return velocity;
}

double Creature::getX() {
    return Creature::position.getX();
}

double Creature::getY() {
    return Creature::position.getY();
}
