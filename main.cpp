#include <iostream>
#include "World.h"
#include "printers/CreaturesPrinter.h"
#include "printers/FoodPrinter.h"
#include "Cell.h"
#include <ctime>
#include <fstream>

int main() {
    srand((unsigned) time(0));

    int maxDays = 100;
    int startingCreatures = 4;
    int foodPerDay = 150;
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
    foodPerDay = (int) (worldXWidth * worldYWidth * foodDensity);
    std::cout << foodPerDay << std::endl;

    auto world = new World(worldXWidth, worldYWidth);

    //We prepare the printers & clear the old files
    auto creaturesPrinter = new CreaturesPrinter("results/creatures/");
    auto foodPrinter = new FoodPrinter("results/food/");
    creaturesPrinter->clearPrints(10000);
    foodPrinter->clearPrints(10000);
    fileName = "results/creatureCount.txt";
    remove(fileName.c_str());

    //We start the world and place creatures randomly
    for (int i = 0; i < startingCreatures; ++i) {
        auto position = Vector2(((-world->getX() / 2.) + ((float) rand() / RAND_MAX) * world->getX()),
                                ((-world->getY() / 2.) + ((float) rand() / RAND_MAX) * world->getY()));
//        position.setComponents(0,0);
        auto creature = new Creature(position);
        world->addCreature(*creature);
    }



    //linked cells
    double cellSize = world->getX() / 5.;
    int nCellX = (int) ((world->getX()) / cellSize);
    int nCellY = (int) ((world->getY()) / cellSize);
    int nCell = nCellX * nCellY;
    Cell *cells = new Cell[nCell];

    std::cout << "Cells values are initialized" << std::endl;
    std::cout << "nCellX " << nCellX << std::endl;
    std::cout << "nCellY " << nCellY << std::endl;
    std::cout << "nCells " << nCell << std::endl;

    int i;
    int ix, iy;
    for (i = 0; i < nCell; i++) {
        cells[i].initCell(i);
        iy = i / nCellX;
        ix = i % nCellX;
        if (ix > 0) { //if not first on the column
            cells[i].addNeighbor(ix + (iy * nCellX) - 1);
        }
        if (ix < nCellX - 1) { //if not last on the column
            cells[i].addNeighbor(ix + (iy * nCellX) + 1);
        }
        if (iy > 0) { //if not on first line
            cells[i].addNeighbor(ix + (iy - 1) * nCellX);
            if (ix > 0) { //if not first on the line
                cells[i].addNeighbor(ix + (iy - 1) * nCellX - 1);
            }
            if (ix < nCellX - 1) { //if not last on the line
                cells[i].addNeighbor(ix + (iy - 1) * nCellX + 1);
            }
        }
        if (iy < nCellY - 1) { //if not on last line
            cells[i].addNeighbor(ix + ((iy + 1) * nCellX));
            if (ix > 0) { //if not first on the line
                cells[i].addNeighbor(ix + ((iy + 1) * nCellX) - 1);
            }
            if (ix < nCellX - 1) { //if not last on the line
                cells[i].addNeighbor(ix + ((iy + 1) * nCellX) + 1);
            }
        }
    }

    std::cout << "Cells are positioned" << std::endl;

    //Days loop
    for (int day = 0; day < maxDays; ++day) {
        world->clearFood();
        world->prepareFood(foodPerDay);
        for (int i = 0; i < world->getCreaturesCount(); ++i) {
            world->getCreature(i)->setCollectedFood(0.);
            world->getCreature(i)->clearTarget();
        }
        for (int j = 0; j < stepPerDay; ++j) {

            // reset linked cells
            for (i = 0; i < nCell; i++) {
                cells[i].setHeadOfList(-9);
            }

            for (int k = 0; k < world->getCreaturesCount(); ++k) {
                auto creature = world->getCreature(k);
                if (creature->isHasTarget()) {
                    creature->refreshTarget(*world);
                }
                if (!creature->isHasTarget()) {
                    creature->searchForFood(*world);
                }
                creature->stepMove(*world);

                int cellIndex = (int) (creature->getX() / cellSize) +
                                (((int) (creature->getY() / cellSize)) * nCellX);
                if (std::abs(cellIndex) > nCell - 1) {
                    std::cout << (int) (creature->getX() / cellSize) << std::endl;
                    std::cout << ((int) (creature->getY() / cellSize)) << std::endl;
                    std::cout << ((int) (creature->getY() / cellSize)) * nCellX << std::endl;

                    creature->getPosition().display();
                    std::cout << "cellIndex " << cellIndex << std::endl;
                    std::cout << "Out of domain limits" << std::endl;
                    exit(1);
                }
                creature->setLinkedCell(cellIndex);
                int hol = cells[cellIndex].getHeadOfList();
                creature->setLinkedCreature(hol);
                cells[cellIndex].setHeadOfList(i);
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

        for (int i = 0; i < world->getCreaturesCount(); ++i) {
            if (world->getCreature(i)->getCollectedFood() > 0.) {
                if (world->getCreature(i)->getCollectedFood() > 2.) {
                    auto position = Vector2(((-world->getX() / 2.) + ((float) rand() / RAND_MAX) * world->getX()),
                                            ((-world->getY() / 2.) + ((float) rand() / RAND_MAX) * world->getY()));
                    auto creature = new Creature(position);
                    world->addCreature(*creature);
                }
            } else {
                world->removeCreature(i);
            }
        }
        std::cout << "Creatures : " << world->getCreaturesCount() << std::endl;
        std::string fileName = "results/creatureCount.txt";
        std::ofstream file;
        file.open(fileName.c_str(), std::ios::app);
        file.precision(10);
        file << std::to_string(day) << "," << world->getCreaturesCount() << std::endl;
        file.close();
    }


    return 0;
}
