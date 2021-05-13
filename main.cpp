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
    std::uniform_int_distribution<> dis(0, 3);

    int maxDays = 100;
    int startingCreatures = 4;
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
    double foodDensity = 0.00375 * 2.;
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

    //We start the world and place creatures on the sides
    for (int i = 0; i < startingCreatures; ++i) {
        int location = dis(gen);
        auto position = Vector2(0, 0);
        auto newCreature = new Creature(position);
        newCreature->putOnSide(location, *world);
        world->addCreature(*newCreature);
    }

    std::cout << "Cells are positioned" << std::endl;

    //Days loop
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        world->prepareFood(foodPerDay);
        for (int i = 0; i < world->getCreaturesCount(); ++i) { //Morning loop
            int location = dis(gen);
            auto creature = world->getCreature(i);
            creature->setCollectedFood(0.);
            creature->setEnergy(0.);
            creature->clearTarget();
            creature->putOnSide(location, *world);
        }
        for (int j = 0; j < stepPerDay; ++j) {

            // reset linked cells

            for (int k = 0; k < world->getCreaturesCount(); ++k) {
                auto creature = world->getCreature(k);
                if (creature->isHasTarget()) {
                    creature->refreshTarget(*world);
                }
                if (!creature->isHasTarget()) {
                    creature->searchForFood(*world);
                }
                creature->stepMove(*world);
            }
            if (world->getCreaturesCount()) {
                for (int k = 0; k < world->getCreaturesCount(); ++k) {
                    creaturesPrinter->print(world->getCreature(k), day * stepPerDay + j);
                }
            } else {
                creaturesPrinter->printNull(day * stepPerDay + j);
            }
            foodPrinter->print(world, day * stepPerDay + j);
        }

        double energyTotal = 0.;
        for (int i = 0; i < world->getCreaturesCount(); ++i) { //Night loop
            auto creature = world->getCreature(i);
            double energyBalance = creature->getEnergy() + creature->getCollectedFood();
            energyTotal += energyBalance;
            if (energyBalance > 0.) {
                if (energyBalance > 2.) {
                    int location = dis(gen);
                    auto position = Vector2(0, 0);
                    auto newCreature = new Creature(position);
                    newCreature->putOnSide(location, *world);
                    world->addCreature(*newCreature);
                }
            } else {
                world->removeCreature(i); // The creature dies is energyBalance < 0
            }
        }
        std::cout << "Creatures : " << world->getCreaturesCount() << std::endl;
        fileName = "results/creatureCount.txt";
        file.open(fileName.c_str(), std::ios::app);
        file.precision(10);
        file << std::to_string(day) << "," << world->getCreaturesCount() << "," << energyTotal << std::endl;
        file.close();
    }


    return 0;
}
