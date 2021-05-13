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
    double e = Creature::eatingRange;
    double noise = (-45 + ((float) rand() / RAND_MAX) * 90);
    if (Creature::isHasTarget()) {
        if (fabs(Creature::position.getX() - Creature::target.getPosition().getX()) < e &&
            fabs(Creature::position.getY() - Creature::target.getPosition().getY()) < e) {
            Creature::clearTarget();
            world1.clearFood(); //this is temporary
        } else {
            double dx = Creature::target.getPosition().getX() - Creature::getX();
            double dy = Creature::target.getPosition().getY() - Creature::getY();
            double targetAngle = atan2(-dx, dy) * (180 / M_PI) + 90;
            Creature::angle = targetAngle + noise / 3.;
        }
    }
    if (fabs(Creature::getX()) >= 50. || fabs(Creature::getY()) >= 50.) {
        if (Creature::getX() >= 50.) {
            Creature::position.setX(50);
        } else if (Creature::getX() <= -50.) {
            Creature::position.setX(-50.);
        }
        if (Creature::getY() >= 50.) {
            Creature::position.setY(50);
        } else if (Creature::getY() <= -50.) {
            Creature::position.setY(-50.);
        }
        Creature::angle = Creature::angle + 180.;
    } else {
        if (!Creature::isHasTarget()) { // Trying to remove the ping-pong against boundaries (but failing)
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

Vector2 &Creature::getPosition() {
    return position;
}

Vector2 &Creature::getVelocity() {
    return velocity;
}

Eatable &Creature::getTarget() {
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

void Creature::setTarget(Eatable eatableTarget) {
    Creature::target = eatableTarget;
}

void Creature::searchForFood(World &world) {
    double min_distance = 1000000000000.;
    for (auto foodItem : world.getFoodItems()) {
        double distance = getDistanceBetweenVectors(Creature::getPosition(), foodItem.getPosition());
        if (distance < min_distance) {
            min_distance = distance;
            Creature::setTarget(foodItem);
            Creature::setHasTarget(true);
        }
    }
}

void Creature::clearTarget() {
    Creature::setHasTarget(false);
}

void Creature::refreshTarget(World world) {
    //CHECK IF TARGET STILL IN FOOD
}

bool Creature::isHasTarget() const {
    return hasTarget;
}

void Creature::setHasTarget(bool hasTarget) {
    Creature::hasTarget = hasTarget;
}
