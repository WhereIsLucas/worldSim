//
// Created by lucas on 15.05.21.
//

#ifndef CHAOSFRACTACLE_PREDATOR_H
#define CHAOSFRACTACLE_PREDATOR_H


#include "Creature.h"

class Predator : public Creature {
private:
    int target_index = 10000;
public:
    Predator(Vector2 &position);

    int getTargetIndex() const;

    void setTargetIndex(int targetIndex);

    int getCollectPrey();

    void setCollectPrey(int collectPrey);

    void stepMove(World &world1) override;

private:
    double collectPrey = 0;

public:
    void searchForFood(World &world) override;

    void refreshTarget(World &world) override;

    void clearTarget() override;

    Creature *reproduce(Vector2 position) override;
};


#endif //CHAOSFRACTACLE_PREDATOR_H
