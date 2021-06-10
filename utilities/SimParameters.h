//
// Created by lucas on 15.05.21.
//

#ifndef CHAOSFRACTACLE_SIMPARAMETERS_H
#define CHAOSFRACTACLE_SIMPARAMETERS_H


#include <string>
#include <iostream>
#include <fstream>

#include "json.hpp"

class SimParameters {
public:
    double worldWidthX;
    double worldWidthY;
    int maxDays;
    int startingPreys;
    int startingPredators;
    int stepPerDay;
    double foodDensity;
    double preyEatingRange;
    double preySensingRange;
    double preySpeed;
    double preyFieldOfView;
    double preyReproductionThreshold;
    double predatorEatingRange;
    double predatorSensingRange;
    double predatorSpeed;
    double predatorFieldOfView;
    double predatorReproductionThreshold;
    double energyThreshold;
    double preyEatingSupply;
    double predatorEatingSupply;

    SimParameters(const std::string &parameters_location);
};


#endif //CHAOSFRACTACLE_SIMPARAMETERS_H
