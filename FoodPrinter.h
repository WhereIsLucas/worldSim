//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_FOODPRINTER_H
#define CHAOSFRACTACLE_FOODPRINTER_H

#include "World.h"

class FoodPrinter {
private:
    std::string path;
public:
    explicit FoodPrinter(const std::string &path);

    const std::string &getPath() const;
    void setPath(std::string path);

    void print(World *world, int day) const;
    void clearPrint(int day);
};


#endif //CHAOSFRACTACLE_FOODPRINTER_H
