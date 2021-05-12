cmake_minimum_required(VERSION 3.19)
project(chaosFractacle)

set(CMAKE_CXX_STANDARD 14)

add_executable(chaosFractacle main.cpp World.cpp World.h Creature.cpp Creature.h Cell.cpp Cell.h printers/CreaturesPrinter.cpp printers/CreaturesPrinter.h printers/FoodPrinter.h printers/FoodPrinter.cpp utilities/Vector2.h utilities/Vector2.cpp FoodItem.cpp FoodItem.h)