#include <iostream>
#include "World.h"
#include "AgentsPrinter.h"
#include "FoodPrinter.h"
#include <ctime>

int main() {
    srand((unsigned) time(0));

    int maxDays = 15;
    int startingAgents = 25;
    int foodPerDay = 25;
    int stepPerDay = 10;
    int worldXWidth = 100;
    int worldYWidth = 100;
    auto world = new World(worldXWidth,worldYWidth);
    auto agentsPrinter = new AgentsPrinter("results/agents/");
    auto foodPrinter = new FoodPrinter("results/food/");
    for (int l = 0; l <= maxDays; l++) {
        agentsPrinter->clearPrint(l);
    }
    for (int i = 0; i < startingAgents; ++i) {
        auto agent = new Agent((rand() % worldXWidth),(rand() % worldYWidth));
        world->addAgent(*agent);
    }
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        world->prepareFood(foodPerDay);
        for (int j = 0; j < stepPerDay; ++j) {
            for (int k = 0; k < world->getAgentsCount(); ++k) {
                world->getAgent(k)->stepMove(*world);
                //TODO eat
            }
            for (int i = 0; i < world->getAgentsCount(); ++i) {
                agentsPrinter->print(world->getAgent(i), day*stepPerDay + j);
            }
            foodPrinter->print(world,day*stepPerDay + j);
        }
    }
    return 0;
}
