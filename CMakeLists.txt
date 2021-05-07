cmake_minimum_required(VERSION 3.19)
project(chaosFractacle)

set(CMAKE_CXX_STANDARD 14)

add_executable(chaosFractacle main.cpp World.cpp World.h Agent.cpp Agent.h AgentsPrinter.cpp AgentsPrinter.h FoodPrinter.h FoodPrinter.cpp)