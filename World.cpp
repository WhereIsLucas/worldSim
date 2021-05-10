//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include "World.h"

World::World(double x, double y) : x(x), y(y) {
    World::x = x;
    World::y = y;
//    std::vector<std::vector<double>> food2(x, std::vector<double>(y,0.));
//    World::food = food2;
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

double World::getX() const {
    return x;
}

double World::getY() const {
    return y;
}

void World::prepareFood(int foodQuantity) {
    for (int i = 0; i < foodQuantity; ++i) {
        auto position = Vector2((((float) rand()/RAND_MAX) * World::getX()), ((float) rand()/RAND_MAX) * World::getY());
        auto foodItem = new FoodItem(position);
        World::addFoodItem(*foodItem);
    }
}

void World::clearFood(){
    World::foodItems.clear();
}

const std::vector<FoodItem> &World::getFoodItems() const {
    return foodItems;
}

void World::removeCreature(int index) {
    World::creatures.erase(World::creatures.begin() + index);
}


void World::setX(double x) {
    World::x = x;
}

void World::setY(double y) {
    World::y = y;
}

void World::addFoodItem(FoodItem foodItem) {
    World::foodItems.push_back(foodItem);
}



