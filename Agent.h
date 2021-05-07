//
// Created by lucas on 07.05.21.
//

#ifndef CHAOSFRACTACLE_AGENT_H
#define CHAOSFRACTACLE_AGENT_H


class Agent {
public:
    Agent(int x, int y);

    void stepMove();

private:
    int x;
public:
    int getX() const;

    int getY() const;

    float getCollectedFood() const;

private:
    int y;
    float collectedFood;

    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();
};


#endif //CHAOSFRACTACLE_AGENT_H
