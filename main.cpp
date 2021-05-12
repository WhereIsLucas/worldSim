#include <iostream>
#include "World.h"
#include "printers/CreaturesPrinter.h"
#include "printers/FoodPrinter.h"
#include <ctime>

int main() {
    srand((unsigned) time(0));

    int maxDays = 10;
    int startingCreatures = 25;
    int foodPerDay = 50;
    int stepPerDay = 100;
    double worldXWidth = 100;
    double worldYWidth = 100;
    auto world = new World(worldXWidth, worldYWidth);
    //We prepare the printers
    auto creaturesPrinter = new CreaturesPrinter("results/creatures/");
    auto foodPrinter = new FoodPrinter("results/food/");
    //We clear the old files
    for (int l = 0; l <= maxDays * stepPerDay; l++) {
        creaturesPrinter->clearPrint(l);
    }
    for (int l = 0; l <= maxDays * stepPerDay; l++) {
        foodPrinter->clearPrint(l);
    }
    //We start the world and place creatures randomly
    for (int i = 0; i < startingCreatures; ++i) {
        auto position = Vector2((-50 + ((float) rand() / RAND_MAX) * world->getX()),
                                (-50 + ((float) rand() / RAND_MAX) * world->getY()));
        auto creature = new Creature(position);
        world->addCreature(*creature);
    }
    //Days loop
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        world->prepareFood(foodPerDay);
        for (int i = 0; i < world->getCreaturesCount(); ++i) {
            world->getCreature(i)->setCollectedFood(0);
        }
        for (int j = 0; j < stepPerDay; ++j) {
            for (int k = 0; k < world->getCreaturesCount(); ++k) {
                world->getCreature(k)->stepMove(*world);
//                //EAT
////                if (world->getFoodAtPosition(world->getCreature(k)->getPosition(), world->getCreature(k)->getY()) > 0) {
////                    world->setFoodAtPosition(world->getCreature(k)->getX(), world->getCreature(k)->getY(),
////                                             world->getFoodAtPosition(world->getCreature(k)->getX(),
////                                                                      world->getCreature(k)->getY()) - 1);
////                    world->getCreature(k)->setCollectedFood(1);
////                }
            }
            if (world->getCreaturesCount()) {
                for (int i = 0; i < world->getCreaturesCount(); ++i) {
                    creaturesPrinter->print(world->getCreature(i), day * stepPerDay + j);
                }
            } else {
                creaturesPrinter->printNull(day * stepPerDay + j);
            }
            foodPrinter->print(world, day * stepPerDay + j);
        }

//        for (int i = 0; i < world->getCreaturesCount(); ++i) {
//            if (world->getCreature(i)->getCollectedFood() > 0) {
//
//            } else {
//                world->removeCreature(i);
//            }
//        }
        std::cout << "Creatures : " << world->getCreaturesCount() << std::endl;
    }
    return 0;
}
