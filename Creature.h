//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_CREATURE_H
#define CHAOSFRACTACLE_CREATURE_H

class World;

#include "World.h"
#include "utilities/Vector2.h"

class Creature {
public:
    Creature(Vector2 &position);

    float getCollectedFood() const;

    void stepMove(World &world1);

    const Vector2 &getPosition() const;
    const Vector2 &getTarget() const;

    const Vector2 &getVelocity() const;

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 target;
public:
    void setTarget(const Vector2 &target);

private:
    bool hasTarget = false;
public:
    bool isHasTarget() const;

    void setHasTarget(bool hasTargetBool);

private:
    float collectedFood = 0.;
    int linkedCell = -9;
    int linkedCreature = -9;
    double angle;
    float eatingRange = 0.3; //Creatures can eat food within this range


public:
    void setCollectedFood(float collectedFoodArg);

    double getX();
    double getY();

    void setLinkedCell(int i);

    void setLinkedCreature(int creatureIndex);

    void searchForFood(const World& world);
};


#endif //CHAOSFRACTACLE_CREATURE_H