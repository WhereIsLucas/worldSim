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
public:
    Creature(Vector2 &position);

    double getCollectedFood();

    void stepMove(World &world1);

    Vector2 &getPosition();

    Eatable &getTarget();

    Vector2 &getVelocity();

private:
    Vector2 position;
    Vector2 velocity;
    Eatable target;
public:
    void setTarget(Eatable target);

    void clearTarget();

private:

public:
    bool isHasTarget() const;

    void setHasTarget(bool hasTarget);

private:
    int linkedCell = -9;
    int linkedCreature = -9;
    double angle;
    double eatingRange = 0.5; //Creatures can eat food within this range
    double sensingRange = 15; //Creatures can detect food within this range
    double speed = 1.;
    double collectedFood = 0.;
    bool hasTarget = false;

public:
    void setCollectedFood(double collectedFoodArg);

    double getX();

    double getY();

    void setLinkedCell(int i);

    void setLinkedCreature(int creatureIndex);

    void searchForFood(World &world);

    void refreshTarget(World &world);
};


#endif //CHAOSFRACTACLE_CREATURE_H