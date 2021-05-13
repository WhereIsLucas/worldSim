//
// Created by lucas on 13.05.21.
//

#include "Eatable.h"

double Eatable::getX() {
    return Eatable::position.getX();
}

double Eatable::getY() {
    return Eatable::position.getY();
}

Vector2 Eatable::getPosition() {
    return Eatable::position;
}

Vector2 Eatable::setPosition(Vector2 newPos) {
    Eatable::position = newPos;
}

double Eatable::getFoodQuantity() const {
    return foodQuantity;
}

void Eatable::setFoodQuantity(double newFoodQuantity) {
    Eatable::foodQuantity = newFoodQuantity;
}

int Eatable::getIndex() const {
    return index;
}

void Eatable::setIndex(int newIndex) {
    Eatable::index = newIndex;
}
