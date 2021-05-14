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

std::random_device rd;
std::mt19937 gen(rd());

double Creature::getCollectedFood() {
    return this->collectedFood;
}

void Creature::stepMove(World &world1) {
    std::uniform_real_distribution<> dis(-45., 45.);
    double noise = dis(gen);
    if (this->hasTarget) {
        if(!this->isPredator()) {
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
        }else{
            int i = this->target_index;
            if (fabs(this->getX() - world1.getCreature(i)->getX()) < this->eatingRangePred &&
                fabs(this->getY() - world1.getCreature(i)->getY()) < this->eatingRangePred) { // TODO change eatingRange for predators
                this->setCollectPrey(1); // One prey is caught by the predator
                this->setCollectedFood((this->getCollectedFood() + this->collectPrey));
                this->clearTarget();
                world1.removeCreature(i); // the prey is eaten and so removed
                this->target_index = 999; // To know that the prey has been eaten
            } else {
                double dx = world1.getCreature(i)->getX() - this->getX();
                double dy = world1.getCreature(i)->getY() - this->getY();
                double targetAngle = atan2(-dx, dy) * (180 / M_PI) + 90;
                Creature::angle = targetAngle + noise / 3.;
            }
        }
    }
    if (fabs(this->getX()) >= world1.getX() / 2. || fabs(this->getY()) >= world1.getY() / 2.) { //If close to the borders
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
        double dx = 0 - this->getX();
        double dy = 0 - this->getY();
        this->angle = atan2(-dx, dy) * (180 / M_PI) + 90; //angle towards the center
    } else {
        if (!this->isHasTarget()) {
            this->angle = this->angle + noise; // in degrees
        }
    }

    Vector2 dVec = Vector2((cos(this->angle * M_PI / 180.) * this->speed),
                           (sin(this->angle * M_PI / 180.) * this->speed));
    this->position = this->position + dVec;
    this->decrementEnergy(speed*speed/100.);
}


void Creature::setCollectedFood(double collectedFoodArg) {
    this->collectedFood = collectedFoodArg;
}

Creature::Creature(Vector2 &position, bool &predator) {
    this->position = position;
    this->velocity = Vector2(0, 0);
    this->angle = 45.;
    this->predator = predator;
}

bool Creature::isPredator() const {
    return predator;
}

void Creature::setAngle(double newAngle) {
    Creature::angle = newAngle;
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
    if(!this->isPredator()){
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
    }else{
        for (int i = 0; i < world.getCreaturesCount(); ++i) {
            auto creature = world.getCreature(i);
            if (!creature->isPredator()){
                double distance = getDistanceBetweenVectors(this->getPosition(),creature->getPosition());
                if(distance < min_distance && distance < this->sensingRange){ // TODO modify the sensing range for predators
                    min_distance = distance;
                    this->setHasTarget(true);
                    this->target_index = i; // storing the index of the prey targeted by the predator
                }
            }
        }
    }
}

void Creature::clearTarget() {
    Creature::setHasTarget(false);
}

void Creature::refreshTarget(World &world1) {
    if (world1.getFoodItems()[this->target.getIndex()].isEaten() || this->target_index == 999) { // target has been eaten
        this->clearTarget();
        this->target_index = 10000;
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

void Creature::putOnSide(int direction, World &world1){
    std::uniform_real_distribution<> dis(-.5, .5);
    double newAngle = 0.;
    Vector2 newPosition(0,0);
    switch (direction) {
        case 0:
            newPosition.setComponents(((-world1.getX() / 2.)),
                                   ((world1.getY()) * dis(gen)));
            newAngle = 0.;
            break;
        case 1:
            newPosition.setComponents(((world1.getX() / 2.)),
                                   ((world1.getY())*dis(gen)));
            newAngle = 180.;
            break;
        case 2:
            newPosition.setComponents((((world1.getX())*dis(gen))),
                                   ((-world1.getY() / 2.)));
            newAngle = 90.;
            break;
        case 3:
            newPosition.setComponents((((world1.getX())*dis(gen))),
                                   ((world1.getY() / 2.)));
            newAngle = 270.;
            break;
    }
    this->setAngle(newAngle);
    this->position.setComponents(newPosition.getX(),newPosition.getY());
}

double Creature::getSpeed() const {
    return speed;
}

void Creature::setSpeed(double newSpeed) {
    Creature::speed = newSpeed;
}

//void Creature::setTargetIndex(int targetIndex) {
//    target_index = targetIndex;
//}
//int Creature::getTargetIndex() const {
//    return target_index;
//}

void Creature::setCollectPrey(int newCollectPrey) {
    Creature::collectPrey = newCollectPrey;
}
