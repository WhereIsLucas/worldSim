#include <fstream>
#include <iostream>

#include "FoodPrinter.h"

void FoodPrinter::print(World *world, int frameNumber) const {
    std::string fileName = FoodPrinter::getPath() + "food" + std::to_string(frameNumber) + ".txt";
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.precision(10);
    if (!world->getFoodItems().empty()){
        for (auto foodItem : world->getFoodItems()) {
            if (!foodItem.isEaten()){
                file << foodItem.getX() << "," << foodItem.getY() << "," << foodItem.getIndex() << std::endl;
            }
        }
    }
    file.close();
}

const std::string &FoodPrinter::getPath() const {
    return path;
}

void FoodPrinter::setPath(const std::string path) {
    FoodPrinter::path = path;
}

void FoodPrinter::clearPrint(int frameNumber) {
    std::string fileName = FoodPrinter::getPath() + "food" + std::to_string(frameNumber) + ".txt";
    remove(fileName.c_str());
}

FoodPrinter::FoodPrinter(const std::string &path) : path(path) {
    FoodPrinter::path = path;
}

void FoodPrinter::clearPrints(int quantity) {
    for (int i = 0; i < quantity; ++i) {
        FoodPrinter::clearPrint(i);
    }
}
