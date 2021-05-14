//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_CREATURESPRINTER_H
#define CHAOSFRACTACLE_CREATURESPRINTER_H


#include "../Creature.h"

class CreaturesPrinter {
private:
    std::string path;
public:
    explicit CreaturesPrinter(const std::string &path);

    const std::string &getPath() const;
    void setPath(std::string path);

    void print(Creature *creature, int day, const std::string& filename, bool noMorePred) const;
    void clearPrint(int day, const std::string& filename);

    void printNull(int frameNumber) const;

    void clearPrints(int quantity, const std::string& filename);
};


#endif //CHAOSFRACTACLE_CREATURESPRINTER_H
