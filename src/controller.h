#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "structure.h"
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unordered_map>
#include <string>

class AdaptiveController {
private:
    std::vector<Intersection*> intersections;
    int currentTime;
    int baseGreenTime;
    int maxGreenTime;
    int nextCarId;

    struct PQNode {
        std::string lane;
        Lane* lanePtr;
        int priority;
    };

    struct Compare {
        bool operator()(const PQNode& a, const PQNode& b) {
            return a.priority < b.priority;
        }
    };

public:
    AdaptiveController(std::vector<Intersection*> inters, int baseTime, int maxTime);

    void generateRandomCars();
    void forwardCars();
    void allocateGreenLights();
    void simulateStep();
};

#endif
