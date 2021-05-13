//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include <random>
#include "World.h"

World::World(double x, double y) : x(x), y(y) {
    World::x = x;
    World::y = y;
}

void World::addCreature(Creature creature) {
    World::creatures.push_back(creature);
}

unsigned long World::getCreaturesCount() {
    return World::creatures.size();
}

Creature *World::getCreature(int index) {
    return &World::creatures[index];
}

double World::getX() const {
    return x;
}

double World::getY() const {
    return y;
}

void World::prepareFood(int foodQuantity) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-.5, .5);

    for (int i = 0; i < foodQuantity; ++i) {
        auto position = Vector2(this->getX() * dis(gen),
                                this->getY() * dis(gen));
        auto foodItem = new FoodPlant(position);
        foodItem->setIndex(i);
        World::addFoodItem(*foodItem, i);
    }

}

void World::clearFood() {
    World::foodItems.clear();
}

std::vector<FoodPlant> &World::getFoodItems() {
    return foodItems;
}

void World::removeCreature(int index) {
    World::creatures.erase(World::creatures.begin() + index);
}

void World::removeFoodItem(int index) {
//    World::foodItems.erase(World::foodItems.begin() + index);
//    for (int i = 0; i < World::getFoodItems().size(); ++i) {
//        auto item = World::getFoodItems()[i];
//        item.setIndex(i);
//    }
}


void World::setX(double x) {
    World::x = x;
}

void World::setY(double y) {
    World::y = y;
}

void World::addFoodItem(FoodPlant foodItem, int index) {
    World::foodItems.push_back(foodItem);
}
