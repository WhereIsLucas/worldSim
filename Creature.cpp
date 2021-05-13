//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "World.h"
#include "utilities/Vector2.h"
#include <cmath>
#include <random>
#include <iostream>

double Creature::getCollectedFood() {
    return this->collectedFood;
}

void Creature::stepMove(World &world1) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-45, 45);
    double noise = dis(gen);
    if (this->hasTarget) {
        if (fabs(this->position.getX() - this->target.getPosition().getX()) < this->eatingRange &&
            fabs(this->position.getY() - this->target.getPosition().getY()) < this->eatingRange) {
            world1.getFoodItems()[this->target.getIndex()].setEaten(true);
            this->setCollectedFood((this->getCollectedFood() + this->target.getFoodQuantity()));
            this->clearTarget();
        } else {
            double dx = this->target.getPosition().getX() - this->getX();
            double dy = this->target.getPosition().getY() - this->getY();
            double targetAngle = atan2(-dx, dy) * (180 / M_PI) + 90;
            Creature::angle = targetAngle + noise / 3.;
        }
    }
    if (fabs(this->getX()) >= world1.getX() / 2. || fabs(this->getY()) >= world1.getY() / 2.) {
        if (this->getX() >= world1.getX() / 2.) {
            this->position.setX(world1.getX() / 2.);
        } else if (this->getX() <= -world1.getX() / 2.) {
            this->position.setX(-world1.getX() / 2.);
        }
        if (this->getY() >= world1.getY() / 2.) {
            this->position.setY(world1.getY() / 2.);
        } else if (this->getY() <= -world1.getY() / 2.) {
            this->position.setY(-world1.getY() / 2.);
        }
        this->angle = this->angle + 180.;
    } else {
        if (!this->isHasTarget()) { // Trying to remove the ping-pong against boundaries (but failing)
            this->angle = this->angle + noise; // in degrees
        }
    }

    Vector2 dVec = Vector2((cos(this->angle * M_PI / 180.) * this->speed),
                           (sin(this->angle * M_PI / 180.) * this->speed));
    this->position = this->position + dVec;
    this->decrementEnergy(0.01);
}


void Creature::setCollectedFood(double collectedFoodArg) {
    this->collectedFood = collectedFoodArg;
}

Creature::Creature(Vector2 &position) {
    this->position = position;
    this->velocity = Vector2(0, 0);
    this->angle = 45.;
}

void Creature::setAngle(double angle) {
    Creature::angle = angle;
}

Vector2 &Creature::getPosition() {
    return position;
}

Vector2 &Creature::getVelocity() {
    return velocity;
}

Eatable &Creature::getTarget() {
    return this->target;
}


double Creature::getX() {
    return this->position.getX();
}

double Creature::getY() {
    return this->position.getY();
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
        if (!foodItem.isEaten()) {
            double distance = getDistanceBetweenVectors(this->getPosition(), foodItem.getPosition());
            if (distance < min_distance && distance < this->sensingRange) {
                min_distance = distance;
                this->setTarget(foodItem);
                this->setHasTarget(true);
            }
        }
    }
}

void Creature::clearTarget() {
    Creature::setHasTarget(false);
}

void Creature::refreshTarget(World &world1) {
    if (world1.getFoodItems()[this->target.getIndex()].isEaten()) {
        this->clearTarget();
        this->searchForFood(world1);
    }
}

bool Creature::isHasTarget() const {
    return hasTarget;
}

void Creature::setHasTarget(bool hasTargetValue) {
    this->hasTarget = hasTargetValue;
}

double Creature::getEnergy() {
    return this->energy;
}

void Creature::setEnergy(double energyValue) {
    this->energy = energyValue;
}

void Creature::incrementEnergy(double energyIncrement) {
    this->energy += energyIncrement;
}

void Creature::decrementEnergy(double energyDecrement) {
    this->energy -= energyDecrement;
}