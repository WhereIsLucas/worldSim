#include <iostream>
#include "World.h"
#include "printers/CreaturesPrinter.h"
#include "printers/FoodPrinter.h"
#include "Cell.h"
#include <fstream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());

    int maxDays = 5;
    int startingCreatures = 5;
    int stepPerDay = 100;

    double worldXWidth = 200.;
    double worldYWidth = 200.;
    std::string fileName = "results/world.txt";
    remove(fileName.c_str());

    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.precision(10);
    file << worldXWidth << "," << worldYWidth << std::endl;
    file.close();

    //Maybe we should work with food density
    double foodDensity = 0.00375;
    int foodPerDay = (int) (worldXWidth * worldYWidth * foodDensity);
    std::cout << foodPerDay << std::endl;

    auto world = new World(worldXWidth, worldYWidth);

    //We prepare the printers & clear the old files
    auto creaturesPrinter = new CreaturesPrinter("results/creatures/");
    auto foodPrinter = new FoodPrinter("results/food/");
    creaturesPrinter->clearPrints(25000);
    foodPrinter->clearPrints(25000);
    fileName = "results/creatureCount.txt";
    remove(fileName.c_str());

    std::uniform_int_distribution<> dis(0, 3);
    //We start the world and place creatures on the sides
    for (int i = 0; i < startingCreatures; ++i) {
        int location = dis(gen);
        auto position = Vector2(0, 0);
        bool predator = false;
        if(i == startingCreatures-1){
            predator = true; // adding one predator
        }
        auto newCreature = new Creature(position, predator);
        newCreature->putOnSide(location, *world);
        world->addCreature(*newCreature);
    }

    std::cout << "Cells are positioned" << std::endl;

    //Days loop
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        world->prepareFood(foodPerDay);
        for (int i = 0; i < world->getCreaturesCount(); ++i) { //Morning loop
            auto creature = world->getCreature(i);
            creature->setCollectedFood(0.);
            creature->setCollectPrey(0);
            creature->setEnergy(0.);
            creature->clearTarget();
            int location = dis(gen);
            creature->putOnSide(location, *world);
        }
        int nbOfFilesPred;
        for (int j = 0; j < stepPerDay; ++j) { //Day loop
            for (int k = 0; k < world->getCreaturesCount(); ++k) {
                auto creature = world->getCreature(k);
                if (creature->isHasTarget()) {
                    creature->refreshTarget(*world);
                }
                if (!creature->isHasTarget()) {
                    creature->searchForFood(*world);
                }
                creature->stepMove(*world);
                if(creature->isPredator()){ // Printing in different files for different colours
                    creaturesPrinter->print(creature, day * stepPerDay + j, "predator", false);
                    nbOfFilesPred = day * stepPerDay + j;
                } else{
                    creaturesPrinter->print(creature, day * stepPerDay + j, "prey", false);
                }
            }
            foodPrinter->print(world, day * stepPerDay + j);
        }
        if((day * stepPerDay + 100 - 1) - nbOfFilesPred > 0){ // if there are no more predators
            for (int j = nbOfFilesPred+1; j < day * stepPerDay + 100; ++j) {
                creaturesPrinter->print(world->getCreature(1), j, "predator", true);
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
                if (energyBalance > 2.) {
                    int location = dis(gen);
                    auto position = Vector2(0, 0);
                    bool predator = false;
                    if(creature->isPredator()){ // Reproduction of the predator
                        predator = true;
                    }
                    auto newCreature = new Creature(position,predator);
                    newCreature->putOnSide(location, *world);
//                    double parentSpeed = creature->getSpeed();
//                    double noise = noiseDis(gen);
//                    newCreature->setSpeed(parentSpeed * (1. + noise)); //Speed mutation
                    world->addCreature(*newCreature);
                }
            } else {
                world->removeCreature(i); // The creature dies if energyBalance < 0
            }
        }
        std::cout << "Day " << day << " - creatures : " << world->getCreaturesCount() << std::endl;
        fileName = "results/creatureCount.txt";
        file.open(fileName.c_str(), std::ios::app);
        file.precision(10);
        file << std::to_string(day) << "," << world->getCreaturesCount() << "," << energyTotal << "," << meanSpeed
             << std::endl;
        file.close();
    }


    return 0;
}
