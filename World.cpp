//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "World.h"

World::World(int x, int y) : x(x), y(y) {
    World::x = x;
    World::y = y;
    std::vector<std::vector<double>> food2(x, std::vector<double>(y,0.));
    World::food = food2;
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

int World::getX() const {
    return x;
}

int World::getY() const {
    return y;
}

void World::prepareFood(int foodQuantity) {
    for (int i = 0; i < foodQuantity; ++i) {
        World::food[rand() % World::x][rand() % World::y]= World::food[rand() % World::x][rand() % World::y] + 1;
    }
}

void World::clearFood(){
    for (int i = 0; i < World::x; ++i) {
        for (int j = 0; j < World::y; ++j) {
            World::food[i][j] = 0.;
        }
    }
}

const std::vector<std::vector<double>> &World::getFood() const {
    return food;
}

void World::removeAgent(int index) {
    World::agents.erase(World::agents.begin() + index);
}

void World::setFoodAtPosition(int xPosition, int yPosition, double foodQty) {
    World::food[xPosition][yPosition] = foodQty;
}

double World::getFoodAtPosition(int xPosition, int yPosition) {
    return World::food[xPosition][yPosition];
}



