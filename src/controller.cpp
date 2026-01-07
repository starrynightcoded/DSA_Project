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
                int numCars = rand() % 4 + 1; // 1-5 cars
                for (int i = 0; i < numCars; ++i) {
                    Car* c = new Car(nextCarId++);
                    totalCarsGenerated++;
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
                        carsForwardToConnectedLane++;
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
         int chosenPriority;
        if (nsPriority >= ewPriority) {
            green1 = "N";
            green2 = "S";
            chosenPriority = nsPriority;
        } else {
            green1 = "E";
            green2 = "W";
            chosenPriority = ewPriority;
        }

        //int greenTime = baseGreenTime + rand() % (maxGreenTime - baseGreenTime + 1);
		
		int scalingFactor = 3;
        int greenTime = baseGreenTime + (chosenPriority / scalingFactor);
        if (greenTime > maxGreenTime)
            greenTime = maxGreenTime;
		
        inter->getLane(green1)->setState("GREEN");
        inter->getLane(green2)->setState("GREEN");

        for (auto& pair : inter->getAllLanes()) {
            Lane* lane = pair.second;
            if (lane->getName() != green1 && lane->getName() != green2) {
                lane->setState("RED");
                if (!lane->isEmpty()){
                	lane->waitingTime++;
                	totalWaitingTime += lane->waitingTime;
					maxWaitingTime = std::max(maxWaitingTime, lane->waitingTime);
				} 
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
    std::cout << "\n--- Simulation Step " << currentTime << " ---\n";

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

void AdaptiveController::displayMetrics() {
    int carsInSystem = 0;
    int totalLanes = 0;

    for (auto* inter : intersections) {
        for (auto& pair : inter->getAllLanes()) {
            Lane* lane = pair.second;
            carsInSystem += lane->getLaneLength();
            totalLanes++;
            carsExited += lane->totalCarsExited;
        }
    }
	carsExited = carsExited - carsForwardToConnectedLane;
    double avgWaitingTime = (carsExited> 0)
        ? (double)totalWaitingTime / carsExited
        : 0.0;
	std::cout << "\n-----------------------------------------\n";
    std::cout << "\n---------- SIMULATION METRICS ----------\n";
    std::cout << "Total Simulation Steps: " << currentTime << "\n";
    std::cout << "Total Cars Generated: " << totalCarsGenerated << "\n";
    std::cout << "Total Cars Exited: " << carsExited << "\n";
    std::cout << "Cars Still in Network: " << carsInSystem << "\n";
    //std::cout<< "Cars forwarded to connected lanes: "<<carsForwardToConnectedLane<<" \n";
    std::cout << "Average Waiting Time: " << avgWaitingTime << " Units\n";
    std::cout << "Maximum Waiting Time Observed: " << maxWaitingTime << " Units\n";
//    std::cout << "Average Cars per Lane: "
//              << (double)carsInSystem / totalLanes << "\n";
    std::cout << "----------------------------------------\n";
}

