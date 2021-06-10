//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_WORLD_H
#define CHAOSFRACTACLE_WORLD_H

class Creature;

#include <vector>
#include "creatures/Creature.h"
#include "food/FoodPlant.h"
#include "utilities/SimParameters.h"

class World {
public:
    World(double x, double y);

    void removeCreature(int index);

    void addCreature(Creature &creature);
    void addFoodItem(FoodPlant foodItem, int index);

    unsigned long getCreaturesCount();

    Creature *getCreature(int index);

    void prepareFood(int foodQuantity, SimParameters &simParameters);

    double getX() const;

    double getY() const;

    void setX(double x);

    void setY(double y);

    void clearFood();
    std::vector<FoodPlant> &getFoodItems();

    void removeFoodItem(int index);

    unsigned long getPreysCount();

    unsigned long getPredatorsCount();

    void setCreatureAsEaten(int index);
    unsigned long getNewCreaturesCount();
    void addNewCreature(Creature &creature);
    void clearNewCreature();
    void appendVec();
private:
    double x;
    double y;
    std::vector<Creature*> creatures;
    std::vector<Creature*> newCreatures;
    std::vector<FoodPlant> foodItems;



};


#endif //CHAOSFRACTACLE_WORLD_H
