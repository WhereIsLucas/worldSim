//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_CREATURE_H
#define CHAOSFRACTACLE_CREATURE_H

class World;

#include "../World.h"
#include "../food/FoodPlant.h"
#include "../utilities/Vector2.h"
#include <optional>
#include <random>

class Creature {
private:
    Vector2 position;
public:
    void setPosition(const Vector2 &position);

private:
    Vector2 velocity;
    Eatable target;
    double angle = 0.;
public:
    double getAngle() const;

private:
    double eatingRange = 0.5;
public:
    double getEatingRange() const;

    void setEatingRange(double eatingRange);

private:
    //Creatures can eat food within this range
    double sensingRange = 15;

public:
    double getSensingRange() const;
    void setSensingRange(double sensingRange);

private:
    //Creatures can detect food within this range
    double speed = 1.;
    double energy = 0.;
    double collectedFood = 0.;
    bool hasTarget = false;
    std::string type = "";
public:
    const std::string &getType() const;

    void setType(const std::string &type);

public:
    Creature(Vector2 &position);

    Creature(const Vector2 &position);

    void setTarget(Eatable target);

    virtual void clearTarget();

    bool isHasTarget() const;

    void setHasTarget(bool hasTarget);

    void setCollectedFood(double collectedFoodArg);

    double getX();

    double getY();

    virtual void searchForFood(World &world);

    virtual void refreshTarget(World &world);

    double getCollectedFood();

    virtual void stepMove(World &world1);

    Vector2 &getPosition();

    Eatable &getTarget();

    Vector2 &getVelocity();

    double getEnergy();

    void setEnergy(double energyValue);

    void incrementEnergy(double energyIncrement);

    void decrementEnergy(double energyDecrement);

    void setAngle(double newAngle);

    void putOnSide(int direction, World &world1);

    double getSpeed() const;

    void setSpeed(double speed);

    virtual Creature *reproduce(Vector2 position);

    std::mt19937 gen;
};


#endif //CHAOSFRACTACLE_CREATURE_H