#include <iostream>
#include <cstdlib>  
#include <ctime>
bool isSeeded = false;

void seedRandom() {
    if (!isSeeded) {
        srand(time(0));  
        isSeeded = true;
    }
}
int generateRandomAmountForVehiclesInEachLane(){
	int random = rand() % 10; 
	return 5;
}