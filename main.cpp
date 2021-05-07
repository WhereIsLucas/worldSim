#include <iostream>
#include "World.h"
#include "AgentsPrinter.h"
#include <ctime>

int main() {
    srand((unsigned) time(0));

    int maxDays = 100;
    int stepPerDay = 24;
    int worldXWidth = 100;
    int worldYWidth = 100;
    auto world = new World(worldXWidth,worldYWidth);
    auto agentsPrinter = new AgentsPrinter("results/");
    for (int l = 0; l <= maxDays; l++) {
        agentsPrinter->clearPrint(l);
    }
    for (int i = 0; i < 10; ++i) {
        auto agent = new Agent((rand() % worldXWidth),(rand() % worldYWidth));
        world->addAgent(*agent);
        agentsPrinter->print(agent, 0);
    }
    for (int day = 1; day < maxDays; ++day) {
        for (int j = 0; j < stepPerDay; ++j) {
            for (int k = 0; k < world->getAgentsCount(); ++k) {
                world->getAgent(k)->stepMove();
            }
        }
        for (int j = 0; j < world->getAgentsCount(); ++j) {
            agentsPrinter->print(world->getAgent(j), day);
        }
    }
    return 0;
}
