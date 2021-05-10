//
// Created by lucas on 22/04/2020.
//

#include <cmath>
#include <iostream>
#include "Vector2.h"

Vector2::Vector2(double x, double y) {
    Vector2::setX(x);
    Vector2::setY(y);
}

double Vector2::getX() {
    return x;
}

void Vector2::setX(double x) {
    Vector2::x = x;
}

double Vector2::getY() {
    return y;
}

void Vector2::setY(double y) {
    Vector2::y = y;
}

Vector2::Vector2(double value) {
    Vector2::setX(value);
    Vector2::setY(value);
}

Vector2::Vector2() {}

Vector2 Vector2::normalize() {
    Vector2 vector2 = *this;
    double norm = vector2.getNorm();
    if (norm > 0){
        vector2.x = vector2.x/norm;
        vector2.y = vector2.y/norm;
    }else{
        vector2 = Vector2(0.);
    }
    return vector2;
}

double Vector2::getNorm() {
    return sqrt(pow(x,2)+pow(y,2));
}

void Vector2::setComponents(double xValue, double yValue) {
    x = xValue;
    y = yValue;
}

[[maybe_unused]] void Vector2::display() const {
    std::cout << x << " "<< y << std::endl;
}

Vector2 projectOntoVector(Vector2 vec, Vector2 vec2) {
    return  Vector2(vec.getX() * vec2.getX(),vec.getY() * vec2.getY());
}


double getDistanceBetweenVectors(Vector2 vector1, Vector2 vector2) {
    return sqrt(pow(vector1.getX() - vector2.getX(),2) +pow(vector1.getY() - vector2.getY(),2));
}


Vector2 operator+(Vector2 vector1, Vector2 vector2) {
    return Vector2(vector1.getX() + vector2.getX(), vector1.getY() + vector2.getY());
}

Vector2 operator*(double coefficient, Vector2 vector) {
    return Vector2(vector.getX() * coefficient, vector.getY() * coefficient);
}

Vector2 operator-(Vector2 vector1, Vector2 vector2) {
    return Vector2(  vector1.getX()-vector2.getX(), vector1.getY() - vector2.getY());
}
