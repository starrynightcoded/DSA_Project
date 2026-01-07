#include <iostream>
#include "controller.h"
#include "structure.h"

int main() {
    // Creating intersections
    Intersection* A = new Intersection();
    Intersection* B = new Intersection();
    Intersection* C = new Intersection();

    // Marking source lanes for random generation(cars/vehicles)
    A->getLane("N")->isSourceLane = true;
    A->getLane("E")->isSourceLane = true;
    B->getLane("S")->isSourceLane = true;
    C->getLane("W")->isSourceLane = true;

    
    A->outgoing["N"] = {B, "N"};
    A->outgoing["S"] = {B, "S"};
    A->outgoing["E"] = {C, "W"};
    A->outgoing["W"] = {C, "E"};

    B->outgoing["N"] = {C, "N"};
    B->outgoing["S"] = {C, "S"};
    B->outgoing["E"] = {A, "W"};
    B->outgoing["W"] = {A, "E"};

    C->outgoing["N"] = {A, "N"};
    C->outgoing["S"] = {A, "S"};
    C->outgoing["E"] = {B, "W"};
    C->outgoing["W"] = {B, "E"};

    std::vector<Intersection*> intersections = {A, B, C};


    AdaptiveController controller(intersections, 2, 4);

    std::cout << "\nTraffic Network Diagram:\n";
    std::cout << "        W1                      W2\n";
    std::cout << "        |                       |\n";
    std::cout << "        |                       |\n";
    std::cout << "N1 ---- A --- S1 ----- N2 ----- B ------ S2\n";
    std::cout << "        |                       |\n";
    std::cout << "        |                       |\n";
    std::cout << "        E1                      E2\n";
    std::cout << "        |             \n";
    std::cout << "        |             \n";
    std::cout << "        |             \n";
    std::cout << "        W3\n";
    std::cout << "        |\n";
    std::cout << "        |\n";
    std::cout << "        |\n";
    std::cout << "N3 ---- C ---- S3\n";
    std::cout << "        |             \n";
    std::cout << "        |             \n";
    std::cout << "        |             \n";
    std::cout << "        E3\n\n";

    std::cout << "Starting Simulation...\n";

    for (int t = 1; t <= 3; t++) {
        controller.simulateStep();
    }
	controller.displayMetrics();
	
    delete A;
    delete B;
    delete C;

    return 0;
}
