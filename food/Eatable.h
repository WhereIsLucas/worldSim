//
// Created by lucas on 13.05.21.
//

#ifndef CHAOSFRACTACLE_EATABLE_H
#define CHAOSFRACTACLE_EATABLE_H


#include "../utilities/Vector2.h"

class Eatable {
private:
    double foodQuantity = 1.;
    int index = -1;
    bool eaten = false;
public:
    bool isEaten() const;

    void setEaten(bool eaten);

public:
    int getIndex() const;

    void setIndex(int index);

private:
    Vector2 position = Vector2(0, 0);

public:
    double getX();

    double getY();

    Vector2 getPosition();

    Vector2 setPosition(Vector2 newPos);

    double getFoodQuantity() const;

    void setFoodQuantity(double foodQuantity);

};


#endif //CHAOSFRACTACLE_EATABLE_H
