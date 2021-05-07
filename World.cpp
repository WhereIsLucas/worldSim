//
// Created by lucas on 07.05.21.
//

#include "World.h"

World::World(int x, int y) : x(x), y(y) {
    World::x = x;
    World::y = y;
}

void World::addAgent(Agent agent) {
    World::agents.push_back(agent);
}

unsigned long World::getAgentsCount() {
    return World::agents.size();
}

Agent * World::getAgent(int index) {
    return &World::agents[index];
}



