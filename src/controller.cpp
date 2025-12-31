#include "controller.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

AdaptiveController::AdaptiveController(std::vector<Intersection*> inters, int baseTime, int maxTime)
    : intersections(inters), currentTime(0), baseGreenTime(baseTime), maxGreenTime(maxTime), nextCarId(1)
{
    srand(time(0));
}

void AdaptiveController::generateRandomCars() {
    char interLabel = 'A';
    for (auto* inter : intersections) {
        for (auto& pair : inter->getAllLanes()) {
            Lane* lane = pair.second;
            if (lane->isSourceLane) {
                int numCars = rand() % 3 + 1; // 1-3 cars
                for (int i = 0; i < numCars; ++i) {
                    Car* c = new Car(nextCarId++);
                    lane->addCar(c);
                    std::cout << "Generated Car " << c->getId() 
                              << " in lane " << lane->getName() 
                              << " of Intersection " << interLabel << "\n";
                }
            }
        }
        interLabel++;
    }
}


void AdaptiveController::forwardCars() {
    char interLabel = 'A';
    for (auto* inter : intersections) {
        for (auto& pair : inter->getAllLanes()) {
            Lane* lane = pair.second;

            if (lane->getState() == "GREEN" && !lane->isEmpty()) {
                if (inter->outgoing.find(lane->getName()) != inter->outgoing.end()) {
                    auto next = inter->outgoing[lane->getName()];
                    Intersection* nextInter = next.first;
                    std::string nextLaneName = next.second;

                    Car* car = lane->removeCar();

                    if (nextInter != nullptr) {
                        nextInter->addCarToLane(nextLaneName, car);
                        std::cout << "Car " << car->getId()
                                  << " moved from lane " << lane->getName() 
                                  << " of Intersection " << interLabel
                                  << " to lane " << nextLaneName
                                  << " of next Intersection\n";
                    } else {
                        std::cout << "Car " << car->getId()
                                  << " left the network from lane " << lane->getName()
                                  << " of Intersection " << interLabel << "\n";
                        delete car;
                    }
                } else {
                
                    Car* car = lane->removeCar();
                    std::cout << "Car " << car->getId()
                              << " left the network from lane " << lane->getName()
                              << " of Intersection " << interLabel << "\n";
                    delete car;
                }
            }
        }
        interLabel++;
    }
}


void AdaptiveController::allocateGreenLights() {
    char interLabel = 'A';
    for (auto* inter : intersections) {

        int nsPriority = inter->getLane("N")->getLaneLength() + inter->getLane("N")->waitingTime +
                         inter->getLane("S")->getLaneLength() + inter->getLane("S")->waitingTime;

        int ewPriority = inter->getLane("E")->getLaneLength() + inter->getLane("E")->waitingTime +
                         inter->getLane("W")->getLaneLength() + inter->getLane("W")->waitingTime;

        std::string green1, green2;
        if (nsPriority >= ewPriority) {
            green1 = "N";
            green2 = "S";
        } else {
            green1 = "E";
            green2 = "W";
        }

        int greenTime = baseGreenTime + rand() % (maxGreenTime - baseGreenTime + 1);

        inter->getLane(green1)->setState("GREEN");
        inter->getLane(green2)->setState("GREEN");

        for (auto& pair : inter->getAllLanes()) {
            Lane* lane = pair.second;
            if (lane->getName() != green1 && lane->getName() != green2) {
                lane->setState("RED");
                if (!lane->isEmpty()) lane->waitingTime++;
            }
        }

        std::cout << "\nIntersection " << interLabel
                  << ": Allocating GREEN to " << green1
                  << " & " << green2
                  << " for " << greenTime << " time units\n";

        inter->processGreen(green1, green2, greenTime);

        interLabel++;
    }
}


void AdaptiveController::simulateStep() {
    currentTime++;
    std::cout << "\n=== Simulation Step " << currentTime << " ===\n";

    generateRandomCars();
    allocateGreenLights();
    forwardCars();


    char interLabel = 'A';
    for (auto* inter : intersections) {
        std::cout << "\nIntersection " << interLabel << ":\n";
        for (auto& pair : inter->getAllLanes()) {
            Lane* lane = pair.second;
            std::cout << "  Lane " << lane->getName()
                      << " | State: " << lane->getState()
                      << " | Cars: " << lane->getLaneLength()
                      << " | WT: " << lane->waitingTime << " ";
            lane->display();
        }
        interLabel++;
    }
}
