cmake_minimum_required(VERSION 3.19)
project(chaosFractacle)

set(CMAKE_CXX_STANDARD 14)

add_executable(chaosFractacle main.cpp World.cpp World.h Creature.cpp Creature.h CreaturesPrinter.cpp CreaturesPrinter.h FoodPrinter.h FoodPrinter.cpp Vector2.h Vector2.cpp)