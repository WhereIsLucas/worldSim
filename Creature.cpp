//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "World.h"
#include "utilities/Vector2.h"
#include <cmath>
#include <iostream>

float Creature::getCollectedFood() const {
    return collectedFood;
}

void Creature::stepMove(World &world1) {
    double speed = 1.; // max displacement every increment
    double e = 0.05;
    double noise = (-45 + ((float) rand() / RAND_MAX) * 90);
    if (Creature::hasTarget) {
        if (Creature::position.getX() - Creature::target.getX() < e &&
            Creature::position.getY() - Creature::target.getY() < e) {
            Creature::setHasTarget(false);
        }else{
            double dx = Creature::target.getX() - Creature::getX();
            double dy = Creature::target.getY() - Creature::getY();
            double targetAngle = atan2(-dx, -dy) * (180 / M_PI);
            Creature::angle = (targetAngle + Creature::angle) / 2.;
        }
    }
    if (fabs(Creature::getX()) >= 50. || fabs(Creature::getY()) >= 50.) {
        if (Creature::getX() >= 50.) {
            Creature::position.setX(50);
        }else if (Creature::getX() <= -50.) {
            Creature::position.setX(-50.);
        }
        if (Creature::getY() >= 50.) {
            Creature::position.setY(50);
        }else if (Creature::getY() <= -50.) {
            Creature::position.setY(-50.);
        }
        Creature::angle = Creature::angle + 180. + noise;
    }else {
        if(!Creature::hasTarget){ // Trying to remove the ping-pong against boundaries (but failing)
            Creature::angle = Creature::angle + noise; // in degrees
        }
    }

    Vector2 dVec = Vector2((cos(Creature::angle * M_PI / 180.) * speed),
                           (sin(Creature::angle * M_PI / 180.) * speed));
    Creature::position = Creature::position + dVec;
}


void Creature::setCollectedFood(float collectedFoodArg) {
    Creature::collectedFood = collectedFoodArg;
}

Creature::Creature(Vector2 &position) {
    Creature::position = position;
    Creature::velocity = Vector2(0, 0);
    Creature::angle = 45.;
}

const Vector2 &Creature::getPosition() const {
    return position;
}

const Vector2 &Creature::getVelocity() const {
    return velocity;
}

const Vector2 &Creature::getTarget() const {
    return Creature::target;
}


double Creature::getX() {
    return Creature::position.getX();
}

double Creature::getY() {
    return Creature::position.getY();
}

void Creature::setLinkedCell(int i) {
    Creature::linkedCell = i;
}

void Creature::setLinkedCreature(int creatureIndex) {
    Creature::linkedCreature = creatureIndex;
}

bool Creature::isHasTarget() const {
    return hasTarget;
}

void Creature::setHasTarget(bool hasTargetBool) {
    Creature::hasTarget = hasTargetBool;
}

void Creature::setTarget(const Vector2 &targetVector) {
    Creature::target = targetVector;
}

void Creature::searchForFood(const World &world) {
    double min_distance = 1000000000000.;
    for (auto foodItem : world.getFoodItems()) {
        double distance = getDistanceBetweenVectors(Creature::getPosition(), foodItem.getPosition());
        if (distance < min_distance) {
            min_distance = distance;
            Creature::setHasTarget(true);
            Creature::setTarget(foodItem.getPosition());
        }
    }
}