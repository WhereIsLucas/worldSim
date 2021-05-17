//
// Created by lucas on 15.05.21.
//

#include <iostream>
#include <random>
#include "Predator.h"

std::random_device randomDevice1;
std::mt19937 generator1(randomDevice1());

void Predator::searchForFood(World &world) {
    double min_distance = 1000000000000.;
    for (int i = 0; i < world.getCreaturesCount(); ++i) {
        auto creature = world.getCreature(i);
        if (creature->getType() == "prey" && !creature->isEaten()) {
            double distance = getDistanceBetweenVectors(this->getPosition(), creature->getPosition());
            if (distance < min_distance && distance < this->getSensingRange()) {
                double dx = creature->getPosition().getX() - this->getX();
                double dy = creature->getPosition().getY() - this->getY();
                double targetAngle = atan2(-dx, dy) * (180 / M_PI) + 90;
                if (targetAngle >= this->getAngle() - this->getFieldOfView() / 2. &&
                    targetAngle <= this->getAngle() + this->getFieldOfView() / 2.) { //Cone vision
                    min_distance = distance;
                    this->setHasTarget(true);
                    this->setTargetIndex(i); // storing the index of the prey targeted by the predator
                }
            }
        }
    }
}

void Predator::refreshTarget(World &world1) {
    if (this->target_index == -9 || world1.getCreature(this->target_index)->isEaten()) { // target has been eaten
        this->clearTarget();
        this->searchForFood(world1);
    }
}

Creature *Predator::reproduce(Vector2 position) {
    return new Predator(position,*this->parameters);
}

void Predator::clearTarget() {
    Creature::clearTarget();
    this->setTargetIndex(-9);
}

int Predator::getTargetIndex() const {
    return target_index;
}

void Predator::setTargetIndex(int targetIndex) {
    target_index = targetIndex;
}

int Predator::getCollectPrey() {
    return collectPrey;
}

void Predator::setCollectPrey(int collectedPrey) {
    Predator::collectPrey = collectedPrey;
}

void Predator::stepMove(World &world1) {
    std::uniform_real_distribution<> dis(-45., 45.);
    double energyThreshold = this->parameters->energyThreshold;
    double noise = dis(randomDevice1);
    if (this->isHasTarget() && this->getEnergy() <= energyThreshold) {
        int i = this->target_index;
        if (fabs(this->getX() - world1.getCreature(i)->getX()) < this->getEatingRange() &&
            fabs(this->getY() - world1.getCreature(i)->getY()) < this->getEatingRange()) {
            this->setCollectPrey(this->getCollectPrey()+1); // One prey is caught by the predator
            this->setCollectedFood(this->getCollectedFood() + 20.);
            this->clearTarget();
            world1.setCreatureAsEaten(i); // the prey is eaten and so removed
        } else {
            double dx = world1.getCreature(i)->getX() - this->getX();
            double dy = world1.getCreature(i)->getY() - this->getY();
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
        if (!this->isHasTarget() || this->getEnergy() > energyThreshold) {
            this->setAngle(this->getAngle() + noise); // in degrees
        }
    }

    Vector2 dVec = Vector2((cos(this->getAngle() * M_PI / 180.) * this->getSpeed()),
                           (sin(this->getAngle() * M_PI / 180.) * this->getSpeed()));
    this->setPosition(this->getPosition() + dVec);
    this->decrementEnergy(getSpeed() * getSpeed() / 2.);
}

Predator::Predator(Vector2 &position, SimParameters &parameters) : Creature(position, parameters) {
    this->parameters = &parameters;
    this->setEatingRange(this->parameters->predatorEatingRange);
    this->setSpeed(this->parameters->predatorSpeed);
    this->setSensingRange(this->parameters->predatorSensingRange);
    this->reproductionThreshold = this->parameters->predatorReproductionThreshold;
    this->setFieldOfView(this->parameters->predatorFieldOfView);
    this->setType("predator");
}

