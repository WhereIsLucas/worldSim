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

    void stepMove(World world1);

    const Vector2 &getPosition() const;

    const Vector2 &getVelocity() const;

private:
    Vector2 position;
    Vector2 velocity;
    float collectedFood = 0.;
    float eatingRange = 0.3; //Creatures can eat food within this range

public:
    void setCollectedFood(float collectedFoodArg);

    double getX();
    double getY();
};


#endif //CHAOSFRACTACLE_CREATURE_H
