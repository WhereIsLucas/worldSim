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

void World::addCreature(Creature creature) {
    World::creatures.push_back(creature);
}

unsigned long World::getCreaturesCount() {
    return World::creatures.size();
}

Creature * World::getCreature(int index) {
    return &World::creatures[index];
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

void World::removeCreature(int index) {
    World::creatures.erase(World::creatures.begin() + index);
}

void World::setFoodAtPosition(int xPosition, int yPosition, double foodQty) {
    World::food[xPosition][yPosition] = foodQty;
}

double World::getFoodAtPosition(int xPosition, int yPosition) {
    return World::food[xPosition][yPosition];
}

void World::setX(int x) {
    World::x = x;
}

void World::setY(int y) {
    World::y = y;
}



