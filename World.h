//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_WORLD_H
#define CHAOSFRACTACLE_WORLD_H

class Agent;

#include <vector>
#include "Agent.h"

class World {
public:
    World(int x, int y);
    void removeAgent(int index);
    void setFoodAtPosition(int xPosition, int y, double  foodQty);
    double getFoodAtPosition(int xPosition, int y);
    void addAgent(Agent agent);

    unsigned long getAgentsCount();

    Agent *getAgent(int index);

    void prepareFood(int foodQuantity);

private:
    int x;
public:
    int getX() const;

    void clearFood();

    int getY() const;

private:
    int y;
    std::vector<Agent> agents;
    std::vector<std::vector <double>> food;
public:
    const std::vector<std::vector<double>> &getFood() const;

};


#endif //CHAOSFRACTACLE_WORLD_H
