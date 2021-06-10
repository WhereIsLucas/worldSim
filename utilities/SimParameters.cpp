//
// Created by lucas on 15.05.21.
//

#include "SimParameters.h"

SimParameters::SimParameters(const std::string &parameters_location) {
    nlohmann::json data;
    std::ifstream file(parameters_location + "/parameters.json");
    if (file.is_open()) {
        file >> data;
        this->worldWidthX = data["worldWidthX"];
        this->worldWidthY = data["worldWidthY"];
        this->maxDays = data["maxDays"];
        this->startingPreys = data["startingPreys"];
        this->startingPredators = data["startingPredators"];
        this->stepPerDay = data["stepPerDay"];
        this->foodDensity = data["foodDensity"];
        this->preyEatingRange = data["prey"]["baseEatingRange"];
        this->preySensingRange = data["prey"]["baseSensingRange"];
        this->preySpeed = data["prey"]["baseSpeed"];
        this->preyFieldOfView = data["prey"]["baseFieldOfView"];
        this->preyReproductionThreshold = data["prey"]["baseReproductionThreshold"];
        this->preyEatingSupply = data["prey"]["eatingSupply"];

        this->predatorSensingRange = data["prey"]["predatorSensingRange"];
        this->predatorEatingRange = data["predator"]["baseEatingRange"];
        this->predatorSpeed = data["predator"]["baseSpeed"];
        this->predatorFieldOfView = data["predator"]["baseFieldOfView"];
        this->predatorReproductionThreshold = data["predator"]["baseReproductionThreshold"];
        this->energyThreshold = data["predator"]["energyThreshold"];
        this->predatorEatingSupply = data["predator"]["eatingSupply"];
        this->energyThreshold = data["predator"]["energyThreshold"];

    } else {
        std::cout << "File error" << std::endl;
    }
}
