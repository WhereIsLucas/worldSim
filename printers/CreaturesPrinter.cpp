#include <fstream>
#include <iostream>

#include "CreaturesPrinter.h"

void CreaturesPrinter::print(Creature *creature, int frameNumber) const {
    std::string fileName = CreaturesPrinter::getPath()+"creature" + std::to_string(frameNumber) + ".txt";
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.precision(10);
    file << creature->getX() << "," << creature->getY() << std::endl;
    file.close();
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

void CreaturesPrinter::clearPrint(int frameNumber) {
    std::string fileName = CreaturesPrinter::getPath()+"creature" + std::to_string(frameNumber) + ".txt";
    remove(fileName.c_str());
}

CreaturesPrinter::CreaturesPrinter(const std::string &path) : path(path) {
    CreaturesPrinter::path = path;
}
