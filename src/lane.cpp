#include <iostream>
#include "lane.h"
#include "functions.h"
using std::cout;

Lane::Lane(std::string n){
	name = n;
}
void Lane::inputVehicles(){
			//comment for partner/+ myself: apply restriction here, like a range that permits 10 max vehicles in a certain lane and even that has to be random like north will have 7 vehicles (randomly generated) or 13 etc
	 maxForThis = generateRandomAmountForVehiclesInEachLane();
	 for(int i=0; i<maxForThis; i++){
	 	//if(lane.isEmpty()){
	 			lane.enqueue('*');
		//}
	 }
}
//void Lane::permitGreenFor(double time){
//
//}

void Lane::vehiclesArrive(){ //this function will not work for horizontal ones
    int totalCars = maxForThis;
    const int CARS_PER_ROW = 2;
    cout << "\n";
    for(int carNum = 0; carNum < totalCars; carNum++){
        if(carNum % CARS_PER_ROW == 0){
            if(carNum > 0) cout << "\n";
            cout << "      ";
        }
        
        cout << "[C] ";
    }
    if(totalCars > 0) {
        cout << "\n";
    }
}

void Lane::displayLane(){ //this is for horizontal ones 
	cout<<"----------------------------------------";
	cout<<"\n";
	vehiclesArrive();
	cout<<"\n";
	cout<<"----------------------------------------";
}
		

void Lane::showTrafficLights(){
	//hardcoding it right now as schedular will handle it 
	cout<<"  Red  ";
} 