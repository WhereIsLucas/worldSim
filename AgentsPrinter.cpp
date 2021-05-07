#include <fstream>
#include <iostream>

#include "AgentsPrinter.h"

void AgentsPrinter::print(Agent *agent, int frameNumber) const {
    std::string fileName = AgentsPrinter::getPath()+"agent" + std::to_string(frameNumber) + ".txt";
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    file.precision(10);
    file << agent->getX() << "," << agent->getY() << std::endl;
    file.close();
}

const std::string &AgentsPrinter::getPath() const {
    return path;
}

void AgentsPrinter::setPath(const std::string path) {
    AgentsPrinter::path = path;
}

void AgentsPrinter::clearPrint(int frameNumber) {
    std::string fileName = AgentsPrinter::getPath()+"agent" + std::to_string(frameNumber) + ".txt";
    remove(fileName.c_str());
}

AgentsPrinter::AgentsPrinter(const std::string &path) : path(path) {
    AgentsPrinter::path = path;
}
