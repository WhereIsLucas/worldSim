//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "World.h"
#include "utilities/Vector2.h"


float Creature::getCollectedFood() const {
    return collectedFood;
}

void Creature::stepMove(World world1) {
    //TODO refactor this shit
    double maxDisplacement = 2.;
    double xDirection = -1;
    double yDirection = -1;
    if((float) rand() / RAND_MAX > 0.5){
        xDirection = 1;
    }
    if((float) rand() / RAND_MAX > 0.5){
        yDirection = 1;
    }
    Vector2 dVec = Vector2((((float) rand() / RAND_MAX) * maxDisplacement * xDirection),
            ((float) rand() / RAND_MAX) * maxDisplacement * yDirection);
    Creature::position = Creature::position + dVec;
}


void Creature::setCollectedFood(float collectedFoodArg) {
    Creature::collectedFood = collectedFoodArg;
}

Creature::Creature(Vector2 &position) {
    Creature::position = position;
    Creature::velocity = Vector2(0,0);
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
