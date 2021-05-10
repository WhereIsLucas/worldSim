//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_WORLD_H
#define CHAOSFRACTACLE_WORLD_H

class Creature;

#include <vector>
#include "Creature.h"
#include "FoodItem.h"

class World {
public:
    World(double x, double y);

    void removeCreature(int index);

    void setFoodAtPosition(double xPosition, double yPosition, double foodQty);

    void addCreature(Creature creature);
    void addFoodItem(FoodItem foodItem);

    unsigned long getCreaturesCount();

    Creature *getCreature(int index);

    void prepareFood(int foodQuantity);

    double getX() const;

    double getY() const;

    void setX(double x);

    void setY(double y);

    void clearFood();
    const std::vector<FoodItem> &getFoodItems() const;

private:
    double x;
    double y;
    std::vector<Creature> creatures;
    std::vector<FoodItem> foodItems;

};


#endif //CHAOSFRACTACLE_WORLD_H
