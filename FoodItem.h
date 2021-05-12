//
// Created by lucas on 10.05.21.
//

#ifndef CHAOSFRACTACLE_FOODITEM_H
#define CHAOSFRACTACLE_FOODITEM_H


#include "utilities/Vector2.h"

class FoodItem {
private:

    Vector2 position;
public:
    double getX();
    double getY();
    Vector2 getPosition();
    FoodItem(Vector2 &positionVec);
};


#endif //CHAOSFRACTACLE_FOODITEM_H