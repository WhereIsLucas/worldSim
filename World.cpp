//
// Created by lucas on 07.05.21.
//

#include <cstdlib>
#include <random>
#include "World.h"
#include "creatures/Prey.h"
#include "creatures/Predator.h"

World::World(double x, double y) : x(x), y(y) {
    World::x = x;
    World::y = y;
}

void World::addCreature(Creature &creature) {
    World::creatures.push_back(&creature);
}

void World::addNewCreature(Creature &creature){
    World::newCreatures.push_back(&creature);
}

void World::clearNewCreature(){
    World::newCreatures.clear();
}
unsigned long World::getNewCreaturesCount() {
    return World::newCreatures.size();
}

void World::appendVec(){
    World::creatures.insert(creatures.end(), newCreatures.begin(), newCreatures.end());
}
unsigned long World::getCreaturesCount() {
    return World::creatures.size();
}

unsigned long World::getPreysCount() {
    unsigned long count = 0;
    for (int i = 0; i < this->getCreaturesCount(); ++i) {
        auto creature = this->getCreature(i);
        if (creature->getType() == "prey") {
            count++;
        }
    }
    return count;
}

unsigned long World::getPredatorsCount() {
    unsigned long count = 0;
    for (int i = 0; i < this->getCreaturesCount(); ++i) {
        auto creature = this->getCreature(i);
        if (creature->getType() == "predator") {
            count++;
        }
    }
    return count;
}

Creature* World::getCreature(int index) {
    return World::creatures[index];
}

double World::getX() const {
    return x;
}

double World::getY() const {
    return y;
}

void World::prepareFood(int foodQuantity, SimParameters &simParameters) {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-.5, .5);

    for (int i = 0; i < foodQuantity; ++i) {
        auto position = Vector2(this->getX() * dis(gen),
                                this->getY() * dis(gen));
        auto foodItem = new FoodPlant(position);
        foodItem->setIndex(i);
        foodItem->setFoodQuantity(simParameters.preyEatingSupply);
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

void World::setCreatureAsEaten(int index){
    auto creature = World::getCreature(index);
    creature->setEaten(true);
}

void World::removeFoodItem(int index) {
//    World::foodItems.erase(World::foodItems.begin() + index);
//    for (int i = 0; i < World::getFoodItems().size(); ++i) {
//        auto item = World::getFoodItems()[i];
//        item.setIndex(i);
//    }
}


void World::setX(double newX) {
    World::x = newX;
}

void World::setY(double newY) {
    World::y = newY;
}

void World::addFoodItem(FoodPlant foodItem, int index) {
    World::foodItems.push_back(foodItem);
}
