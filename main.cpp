#include <iostream>
#include "World.h"
#include "printers/CreaturesPrinter.h"
#include "printers/FoodPrinter.h"
#include "Cell.h"
#include "creatures/Prey.h"
#include "creatures/Predator.h"
#include "utilities/SimParameters.h"
#include <fstream>
#include <random>

int main() {

    std::random_device rd;
    std::mt19937 gen(rd());
    auto parameters = new SimParameters("settings");


    int maxDays = parameters->maxDays;
    int startingPreys = parameters->startingPreys;
    int startingPredators = parameters->startingPredators;
    int stepPerDay = parameters->stepPerDay;

    std::string fileName = "results/world.txt";
    remove(fileName.c_str());

    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.precision(10);
    file << parameters->worldWidthX << "," << parameters->worldWidthY << "," << stepPerDay << std::endl;
    file.close();

    //Maybe we should work with food density
    double foodDensity = parameters->foodDensity;
    int foodPerDay = (int) (parameters->worldWidthX * parameters->worldWidthY * foodDensity);
    std::cout << foodPerDay << std::endl;

    auto world = new World(parameters->worldWidthX, parameters->worldWidthY);

    //We prepare the printers & clear the old files
    auto preysPrinter = new CreaturesPrinter("results/preys/");
    auto predatorsPrinter = new CreaturesPrinter("results/predators/");
    auto foodPrinter = new FoodPrinter("results/food/");
    preysPrinter->clearPrints(25000, "prey");
    predatorsPrinter->clearPrints(25000, "predator");
    foodPrinter->clearPrints(25000);
    fileName = "results/creatureCount.txt";
    remove(fileName.c_str());

    std::uniform_int_distribution<> dis(0, 3);
    std::uniform_real_distribution<> positionDistribution(-0.5, 0.5);
    //We start the world and place creatures on the sides
    for (int i = 0; i < startingPreys; ++i) {
        auto position = Vector2(0, 0);
        auto newCreature = new Prey(position, *parameters);
//        int location = dis(gen);
//        newCreature->putOnSide(location, *world);
        world->addCreature(*newCreature);
    }
    for (int i = 0; i < (startingPredators); ++i) {
//        int location = dis(gen);
        auto position = Vector2(0, 0);
        auto newCreature = new Predator(position, *parameters);
//        newCreature->putOnSide(location, *world);
        world->addCreature(*newCreature);
    }
    //Days loop
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        world->prepareFood(foodPerDay);
        for (int i = 0; i < world->getCreaturesCount(); ++i) { //Morning loop
            auto creature = world->getCreature(i);
            creature->setCollectedFood(0.);
            creature->setEnergy(50.);
            creature->clearTarget();
            creature->setIsHunted(false);
            auto position = Vector2(positionDistribution(gen) * parameters->worldWidthX,
                                    positionDistribution(gen) * parameters->worldWidthY);
            creature->setPosition(position);
//            if(creature->getType() == "prey"){
//                int location = dis(gen);
//                creature->putOnSide(location, *world);
//            }
//            if (creature->getType() == "predator"){
//                auto position = Vector2(0, 0);
//                creature->setPosition(position);
//            }
        }
        for (int j = 0; j < stepPerDay; ++j) { //Day loop
            for (int k = 0; k < world->getCreaturesCount(); ++k) {
                auto creature = world->getCreature(k);
                if (!creature->isEaten()) {
                    if (creature->isHasTarget()) {
                        creature->refreshTarget(*world);
                    }else {
                        creature->searchForFood(*world);
                    }
                    creature->stepMove(*world);
                    creature->setIsHunted(false);
                    if (creature->getType() == "predator") { // Printing in different files for different colours
                        predatorsPrinter->print(creature, day * stepPerDay + j, "predator", false);
                    } else {
                        preysPrinter->print(creature, day * stepPerDay + j, "prey", false);
                    }

                }
            }
            foodPrinter->print(world, day * stepPerDay + j);
        }

        for (int i = 0; i < world->getCreaturesCount(); ++i) {
            auto creature = world->getCreature(i);
            if (creature->isEaten()) {
                world->removeCreature(i);
            }
        }

        double meanSpeed = 0.;
        unsigned long count = world->getCreaturesCount(); //We take it now before adding other creatures;
        for (int i = 0; i < world->getCreaturesCount(); ++i) { //Speed mean loop
            auto creature = world->getCreature(i);
            meanSpeed += creature->getSpeed();
        }
        meanSpeed = meanSpeed / (double) count;

        double energyTotal = 0.;
        // This is the noise used for genetic mutations
        std::uniform_real_distribution<> noiseDis(-0.05, 0.05);
        for (int i = 0; i < world->getCreaturesCount(); ++i) { //Night loop
            auto creature = world->getCreature(i);
            double energyBalance = creature->getEnergy() + creature->getCollectedFood();
            energyTotal += energyBalance;
            if (energyBalance > 0.) {
                if (energyBalance > creature->reproductionThreshold) {
//                    int location = dis(gen);
                    auto position = Vector2(0, 0);
                    auto newCreature = creature->reproduce(position);
//                    double parentSpeed = creature->getSpeed();
//                    double noise = noiseDis(gen);
//                    newCreature->setSpeed(parentSpeed * (1. + noise)); //Speed mutation
                    world->addNewCreature(*newCreature); // Vector of world with the new creatures
                }
            } else {
                world->removeCreature(i); // The creature dies if energyBalance < 0
            }
        }

        world->appendVec(); // We append the vector &creatures with the vector &newCreatures
        world->clearNewCreature();

        std::cout << "Day " << day << " - preys : " << world->getPreysCount() << " - predator : "
                  << world->getPredatorsCount() << std::endl;
//        std::cout << "Day " << day << " - creatures : " << world->getCreaturesCount() << std::endl;
        fileName = "results/creatureCount.txt";
        file.open(fileName.c_str(), std::ios::app);
        file.precision(10);
        file << std::to_string(day) << "," << world->getCreaturesCount() << "," << energyTotal << "," << meanSpeed
             << "," << world->getPreysCount()
             << "," << world->getPredatorsCount()
             << std::endl;
        file.close();
        if ((world->getPredatorsCount() == 0 && parameters->startingPredators > 0) ||
            (world->getPreysCount() == 0 && parameters->startingPreys > 0)) {
            exit(0);
        }
    }


    return 0;
}
