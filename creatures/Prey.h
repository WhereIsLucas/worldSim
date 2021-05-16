//
// Created by lucas on 15.05.21.
//

#ifndef CHAOSFRACTACLE_PREY_H
#define CHAOSFRACTACLE_PREY_H


#include "Creature.h"
#include "../utilities/SimParameters.h"

class Prey : public Creature {
private:

    std::vector<int> hunterIndex;
    double predatorSensingRange = 10.;

public:
    Prey(Vector2 &position, SimParameters &parameters);

    void refreshTarget(World &world) override;

    void searchForFood(World &world) override;

    void stepMove(World &world1) override;

    void clearTarget() override;

    Creature *reproduce(Vector2 position) override;

    void searchForPredator(World &world);

    double getPredatorSensingRange() const;


    void setPredatorSensingRange(double predatorSensingRange);
};


#endif //CHAOSFRACTACLE_PREY_H
