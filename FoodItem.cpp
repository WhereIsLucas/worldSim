//
// Created by lucas on 10.05.21.
//

#include "FoodItem.h"

FoodItem::FoodItem(Vector2 &positionVec) {
    FoodItem::position = positionVec;
}

double FoodItem::getX() {
    return FoodItem::position.getX();
}

double FoodItem::getY() {
    return FoodItem::position.getY();
}

Vector2 FoodItem::getPosition() {
    return FoodItem::position;
}
