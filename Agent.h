//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_AGENT_H
#define CHAOSFRACTACLE_AGENT_H

class World;
#include "World.h"

class Agent {
public:
    Agent(int x, int y);

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


#endif //CHAOSFRACTACLE_AGENT_H
