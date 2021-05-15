//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "Creature.h"
#include "../World.h"
#include "../utilities/Vector2.h"
#include <cmath>
#include <random>
#include <iostream>



double Creature::getCollectedFood() {
    return this->collectedFood;
}

void Creature::stepMove(World &world1) {
    std::uniform_real_distribution<> dis(-45., 45.);
    double noise = dis(gen);
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

Creature::Creature(Vector2 &position) {
    this->position = position;
    this->velocity = Vector2(0, 0);
    this->angle = 45.;
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    this->gen = generator;
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

void Creature::setTarget(Eatable eatableTarget) {
    Creature::target = eatableTarget;
}

void Creature::searchForFood(World &world) {
}

void Creature::clearTarget() {
    Creature::setHasTarget(false);
}

void Creature::refreshTarget(World &world1) {
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

double Creature::getSensingRange() const {
    return sensingRange;
}

void Creature::setSensingRange(double d) {
    Creature::sensingRange = d;
}

double Creature::getEatingRange() const {
    return eatingRange;
}

void Creature::setEatingRange(double eatingRange) {
    Creature::eatingRange = eatingRange;
}

double Creature::getAngle() const {
    return angle;
}

void Creature::setPosition(const Vector2 &position) {
    Creature::position = position;
}

Creature *Creature::reproduce(Vector2 position) {
    return new Creature(position);
}

Creature::Creature(const Vector2 &position) : position(position) {}

const std::string &Creature::getType() const {
    return type;
}

void Creature::setType(const std::string &type) {
    Creature::type = type;
}

