//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_CREATURE_H
#define CHAOSFRACTACLE_CREATURE_H

class World;
#include "World.h"

class Creature {
public:
    Creature(int x, int y);

    int x;
public:
    int getX() const;

    int getY() const;

    float getCollectedFood() const;
    void stepMove(World world1);

private:
    int y;
    float collectedFood;
public:
    void setCollectedFood(float collectedFood);

private:

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

};


#endif //CHAOSFRACTACLE_CREATURE_H
