cmake_minimum_required(VERSION 3.19)
project(chaosFractacle)

set(CMAKE_CXX_STANDARD 17)

add_executable(chaosFractacle main.cpp World.cpp World.h creatures/Creature.cpp creatures/Creature.h Cell.cpp Cell.h printers/CreaturesPrinter.cpp printers/CreaturesPrinter.h printers/FoodPrinter.h printers/FoodPrinter.cpp utilities/Vector2.h utilities/Vector2.cpp food/FoodPlant.cpp food/FoodPlant.h food/Eatable.cpp food/Eatable.h creatures/Predator.cpp creatures/Predator.h creatures/Prey.cpp creatures/Prey.h utilities/json.hpp utilities/SimParameters.cpp utilities/SimParameters.h)