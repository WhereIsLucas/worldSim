//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_WORLD_H
#define CHAOSFRACTACLE_WORLD_H


#include <vector>
#include "Agent.h"

class World {
public:
    World(int x, int y);
    void addAgent(Agent agent);
    unsigned long getAgentsCount();
    Agent * getAgent(int index);

private:
    int x;
    int y;
    std::vector<Agent> agents;
};


#endif //CHAOSFRACTACLE_WORLD_H
