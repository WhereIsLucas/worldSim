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
    World(int x, int y);
    void removeCreature(int index);
    void setFoodAtPosition(int xPosition, int y, double  foodQty);
    double getFoodAtPosition(int xPosition, int y);
    void addCreature(Creature creature);

    unsigned long getCreaturesCount();

    Creature *getCreature(int index);

    void prepareFood(int foodQuantity);

private:
    int x;
    int y;

private:
    std::vector<Creature> creatures;
    std::vector<std::vector <double>> food;

public:
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    void clearFood();


private:
public:
    const std::vector<std::vector<double>> &getFood() const;

};


#endif //CHAOSFRACTACLE_WORLD_H
