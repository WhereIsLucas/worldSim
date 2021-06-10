#include <fstream>
#include <iostream>

#include "CreaturesPrinter.h"

void CreaturesPrinter::print(Creature *creature, int frameNumber, const std::string& filename, bool noMorePred) const {
    std::string fileName = CreaturesPrinter::getPath()+filename+ std::to_string(frameNumber) + ".txt";
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.precision(10);
    if(noMorePred){ // If there are no more predators
        file << " , , " << std::endl;
        file.close();
    }else {
        file
        << creature->getX() << ","
        << creature->getY() << ","
        << creature->getEnergy() + creature->getCollectedFood() << ","
        << creature->getSpeed()
        << std::endl;
        file.close();
    }

}


void CreaturesPrinter::printNull(int frameNumber) const {
    std::string fileName = CreaturesPrinter::getPath()+"creature" + std::to_string(frameNumber) + ".txt";
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.close();
}

const std::string &CreaturesPrinter::getPath() const {
    return path;
}

void CreaturesPrinter::setPath(const std::string path) {
    CreaturesPrinter::path = path;
}

void CreaturesPrinter::clearPrint(int frameNumber, const std::string& filename) {
    std::string fileName = CreaturesPrinter::getPath()+filename+ std::to_string(frameNumber) + ".txt";
    remove(fileName.c_str());
}

CreaturesPrinter::CreaturesPrinter(const std::string &path) : path(path) {
    CreaturesPrinter::path = path;
}

void CreaturesPrinter::clearPrints(int quantity, const std::string& filename) {
    for (int i = 0; i < quantity; ++i) {
        CreaturesPrinter::clearPrint(i, filename);
    }
}
