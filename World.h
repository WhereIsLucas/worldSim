//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_WORLD_H
#define CHAOSFRACTACLE_WORLD_H

class Creature;

#include <vector>
#include "Creature.h"

class World {
public:
    World(double x, double y);

    void removeCreature(int index);

    void setFoodAtPosition(double xPosition, double yPosition, double foodQty);

    double getFoodAtPosition(double xPosition, double yPosition);

    void addCreature(Creature creature);

    unsigned long getCreaturesCount();

    Creature *getCreature(int index);

    void prepareFood(int foodQuantity);

    double getX() const;

    double getY() const;

    void setX(double x);

    void setY(double y);

    void clearFood();

    const std::vector<std::vector<double>> &getFood() const;


private:
    double x;
    double y;
    std::vector<Creature> creatures;
//    std::vector<std::vector<double>> food;

};


#endif //CHAOSFRACTACLE_WORLD_H
