//
// Created by lucas on 15.05.21.
//

#include <random>
#include <iostream>
#include "Prey.h"


Prey::Prey(Vector2 &position) : Creature(position) {
    this->setType("prey");
}

void Prey::stepMove(World &world1) {
    std::uniform_real_distribution<> dis(-45., 45.);
    double noise = dis(this->gen);
    if (this->isHasTarget()) {
        if (fabs(this->getPosition().getX() - this->getTarget().getPosition().getX()) < this->getEatingRange() &&
            fabs(this->getPosition().getY() - this->getTarget().getPosition().getY()) < this->getEatingRange()) {
            world1.getFoodItems()[this->getTarget().getIndex()].setEaten(true);
            this->setCollectedFood((this->getCollectedFood() + this->getTarget().getFoodQuantity()));
            this->clearTarget();
        } else {
            double dx = this->getTarget().getPosition().getX() - this->getX();
            double dy = this->getTarget().getPosition().getY() - this->getY();
            double targetAngle = atan2(-dx, dy) * (180 / M_PI) + 90;
            this->setAngle(targetAngle + noise / 3.);
        }
    }
    if (fabs(this->getX()) >= world1.getX() / 2. ||
        fabs(this->getY()) >= world1.getY() / 2.) { //If close to the borders
        if (this->getX() >= world1.getX() / 2.) {
            this->getPosition().setX(world1.getX() / 2.);
        } else if (this->getX() <= -world1.getX() / 2.) {
            this->getPosition().setX(-world1.getX() / 2.);
        }
        if (this->getY() >= world1.getY() / 2.) {
            this->getPosition().setY(world1.getY() / 2.);
        } else if (this->getY() <= -world1.getY() / 2.) {
            this->getPosition().setY(-world1.getY() / 2.);
        }
        double dx = 0 - this->getX();
        double dy = 0 - this->getY();
        this->setAngle(atan2(-dx, dy) * (180 / M_PI) + 90); //angle towards the center
    } else {
        if (!this->isHasTarget()) {
            this->setAngle(this->getAngle() + noise); // in degrees
        }
    }

    Vector2 dVec = Vector2((cos(this->getAngle() * M_PI / 180.) * this->getSpeed()),
                           (sin(this->getAngle() * M_PI / 180.) * this->getSpeed()));
    this->setPosition(this->getPosition() + dVec);
    this->decrementEnergy(getSpeed() * getSpeed() / 100.);
}

void Prey::searchForFood(World &world) {
    double min_distance = 1000000000000.;
    for (auto foodItem : world.getFoodItems()) {
        if (!foodItem.isEaten()) {
            double distance = getDistanceBetweenVectors(this->getPosition(), foodItem.getPosition());
            if (distance < min_distance && distance < this->getSensingRange()) {
                min_distance = distance;
                this->setTarget(foodItem);
                this->setHasTarget(true);
            }
        }
    }
}

void Prey::refreshTarget(World &world1) {
    if (world1.getFoodItems()[this->getTarget().getIndex()].isEaten()) { // target has been eaten
        this->clearTarget();
        this->searchForFood(world1);
    }
}

Creature *Prey::reproduce(Vector2 position) {
    return new Prey(position);
}

void Prey::clearTarget() {
    Creature::clearTarget();
}
