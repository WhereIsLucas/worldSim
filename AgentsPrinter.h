//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_AGENTSPRINTER_H
#define CHAOSFRACTACLE_AGENTSPRINTER_H


#include "Agent.h"

class AgentsPrinter {
private:
    std::string path;
public:
    explicit AgentsPrinter(const std::string &path);

    const std::string &getPath() const;
    void setPath(std::string path);

    void print(Agent *agent, int day) const;
    void clearPrint(int day);

    void printNull(int frameNumber) const;
};


#endif //CHAOSFRACTACLE_AGENTSPRINTER_H
