//
// Created by lucas on 10.05.21.
//

#ifndef CHAOSFRACTACLE_FOODPLANT_H
#define CHAOSFRACTACLE_FOODPLANT_H


#include "../utilities/Vector2.h"
#include "Eatable.h"

class FoodPlant : public Eatable {

public:
    FoodPlant(Vector2 &positionVec);
};


#endif //CHAOSFRACTACLE_FOODPLANT_H