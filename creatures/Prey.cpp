//
// Created by lucas on 15.05.21.
//

#include <random>
#include <iostream>
#include "Prey.h"
std::random_device randomDevice2;
std::mt19937 generator2(randomDevice2());

Prey::Prey(Vector2 &position, SimParameters &parameters) : Creature(position, parameters) {
    this->setType("prey");
    this->parameters = &parameters;
}

void Prey::stepMove(World &world1) {
    std::uniform_real_distribution<> dis(-45., 45.);
    double noise = dis(randomDevice2);

    if (!this->hunterIndex.empty()) { // If a predator is close
        double predAngle = 0.;
        for (int i : this->hunterIndex) {
            double dx = world1.getCreature(i)->getX() - this->getX();
            double dy = world1.getCreature(i)->getY() - this->getY();
            predAngle += atan2(-dx, dy) * (180 / M_PI) - 90.;
        }
        this->setAngle((predAngle / (double) this->hunterIndex.size()) + noise / 1.5);
        this->hunterIndex.clear();
    }
    if (this->isHasTarget() && !this->getIsHunted()) { // Does not eat if a predator is close
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
        if (!this->isHasTarget() && !this->getIsHunted()) {
            this->setAngle(this->getAngle() + noise); // in degrees
        }
    }

    Vector2 dVec = Vector2((cos(this->getAngle() * M_PI / 180.) * this->getSpeed()),
                           (sin(this->getAngle() * M_PI / 180.) * this->getSpeed()));
    this->setPosition(this->getPosition() + dVec);
    this->decrementEnergy(getSpeed() * getSpeed() / 2.);
}

void Prey::searchForPredator(World &world) {
    for (int i = 0; i < world.getCreaturesCount(); ++i) {
        auto creature = world.getCreature(i);
        if (creature->getType() == "predator") {
            double distance = getDistanceBetweenVectors(this->getPosition(), creature->getPosition());
            if (distance < this->getPredatorSensingRange()) {
                this->setIsHunted(true);
                this->hunterIndex.push_back(i);
            }
        }
    }
}


void Prey::searchForFood(World &world) {
    double min_distance = 1000000000000.;
    for (auto foodItem : world.getFoodItems()) {
        if (!foodItem.isEaten()) {
            double distance = getDistanceBetweenVectors(this->getPosition(), foodItem.getPosition());
            if (distance < min_distance && distance < this->getSensingRange()) {
                double dx = foodItem.getPosition().getX() - this->getX();
                double dy = foodItem.getPosition().getY() - this->getY();
                double targetAngle = atan2(-dx, dy) * (180 / M_PI) + 90;
                if (targetAngle >= this->getAngle() - this->getFieldOfView() / 2. &&
                    targetAngle <= this->getAngle() + this->getFieldOfView() / 2.) { //Cone vision
                    min_distance = distance;
                    this->setTarget(foodItem);
                    this->setHasTarget(true);
                }
            }
        }
    }
    this->searchForPredator(world);
}

void Prey::refreshTarget(World &world1) {
    if (world1.getFoodItems()[this->getTarget().getIndex()].isEaten()) { // target has been eaten
        this->clearTarget();
        this->searchForFood(world1);
    }
}

Creature *Prey::reproduce(Vector2 position) {
    return new Prey(position, *this->parameters);
}

void Prey::clearTarget() {
    Creature::clearTarget();
}


double Prey::getPredatorSensingRange() const {
    return predatorSensingRange;
}

void Prey::setPredatorSensingRange(double predatorSensingRangeDouble) {
    Prey::predatorSensingRange = predatorSensingRangeDouble;
}
