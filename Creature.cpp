//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "World.h"
#include "utilities/Vector2.h"
#include <cmath>

float Creature::getCollectedFood() const {
    return collectedFood;
}

void Creature::stepMove(World world1) {
    //TODO target
    double speed = 1.; // max displacement every increment
    if(fabs(Creature::getX()) >= 50. || fabs(Creature::getY()) >= 50.){
        Creature::angle = Creature::angle + 180.;
    }
    else{
        Creature::angle = Creature::angle + (-45 + ((float) rand()/ RAND_MAX)*90); // in degrees
    }
    Vector2 dVec = Vector2(( cos(Creature::angle*M_PI/180.)* speed),
                           ( sin(Creature::angle*M_PI/180.)* speed));
    Creature::position = Creature::position + dVec;
}


void Creature::setCollectedFood(float collectedFoodArg) {
    Creature::collectedFood = collectedFoodArg;
}

Creature::Creature(Vector2 &position) {
    Creature::position = position;
    Creature::velocity = Vector2(0,0);
    Creature::angle = 45.;
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
