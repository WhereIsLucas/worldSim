//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_CREATURE_H
#define CHAOSFRACTACLE_CREATURE_H

class World;

#include "World.h"
#include "food/FoodPlant.h"
#include "utilities/Vector2.h"
#include <optional>

class Creature {
private:
    Vector2 position;
    Vector2 velocity;
    Eatable target;
    int linkedCell = -9;
    int linkedCreature = -9;
    double angle;
    double eatingRange = 0.5; //Creatures can eat food within this range
    double sensingRange = 15; //Creatures can detect food within this range
    double speed = 1.;
    double energy = 0.;
    double collectedFood = 0.;
    bool hasTarget = false;
    bool predator; // If true --> predator
    int target_index = 10000;
    int collectPrey = 0.;
public:
//    void setTargetIndex(int targetIndex);
//    int getTargetIndex() const;

    void setCollectPrey(int collectPrey);

public:
    Creature(Vector2 &position, bool &predator);

    void setTarget(Eatable target);

    void clearTarget();

    bool isHasTarget() const;

    void setHasTarget(bool hasTarget);

    void setCollectedFood(double collectedFoodArg);

    double getX();

    double getY();

    void setLinkedCell(int i);

    void setLinkedCreature(int creatureIndex);

    void searchForFood(World &world);

    void refreshTarget(World &world);

    double getCollectedFood();

    void stepMove(World &world1);

    Vector2 &getPosition();

    Eatable &getTarget();

    Vector2 &getVelocity();

    double getEnergy();

    void setEnergy(double energyValue);

    void incrementEnergy(double energyIncrement);

    void decrementEnergy(double energyDecrement);

    void setAngle(double newAngle);

    void putOnSide(int direction, World &world1);

    double getSpeed() const;

    void setSpeed(double speed);

    bool isPredator() const;
};


#endif //CHAOSFRACTACLE_CREATURE_H