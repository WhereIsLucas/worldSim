#include <iostream>
#include "World.h"
#include "AgentsPrinter.h"
#include "FoodPrinter.h"
#include <ctime>

int main() {
    srand((unsigned) time(0));

    int maxDays = 10;
    int startingAgents = 25;
    int foodPerDay = 10;
    int stepPerDay = 60;
    int worldXWidth = 100;
    int worldYWidth = 100;
    auto world = new World(worldXWidth, worldYWidth);
    auto agentsPrinter = new AgentsPrinter("results/agents/");
    auto foodPrinter = new FoodPrinter("results/food/");
    for (int l = 0; l <= maxDays; l++) {
        agentsPrinter->clearPrint(l);
    }
    for (int l = 0; l <= maxDays; l++) {
        foodPrinter->clearPrint(l);
    }
    for (int i = 0; i < startingAgents; ++i) {
        auto agent = new Agent((rand() % worldXWidth), (rand() % worldYWidth));
        world->addAgent(*agent);
    }
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        for (int i = 0; i < world->getAgentsCount(); ++i) {
            world->getAgent(i)->setCollectedFood(0);
        }
        world->prepareFood(foodPerDay);
        for (int j = 0; j < stepPerDay; ++j) {
            for (int k = 0; k < world->getAgentsCount(); ++k) {
                world->getAgent(k)->stepMove(*world);
                //EAT
                if (world->getFoodAtPosition(world->getAgent(k)->getX(), world->getAgent(k)->getY()) > 0) {
                    world->setFoodAtPosition(world->getAgent(k)->getX(), world->getAgent(k)->getY(),
                                             world->getFoodAtPosition(world->getAgent(k)->getX(),
                                                                      world->getAgent(k)->getY()) - 1);
                    world->getAgent(k)->setCollectedFood(1);
                }
            }
            if (world->getAgentsCount()) {
                for (int i = 0; i < world->getAgentsCount(); ++i) {
                    agentsPrinter->print(world->getAgent(i), day * stepPerDay + j);
                }
            } else {
                agentsPrinter->printNull(day * stepPerDay + j);
            }

            foodPrinter->print(world, day * stepPerDay + j);
        }
        for (int i = 0; i < world->getAgentsCount(); ++i) {
            if (world->getAgent(i)->getCollectedFood() > 0) {

            } else {
                world->removeAgent(i);
            }
        }
        std::cout << "Agents : " << world->getAgentsCount() << std::endl;
    }
    return 0;
}
