#ifndef LANE_H
#define LANE_H

#include "queue.h"

class Lane{
	public:
		int maxForThis;
		std::string name; //nagan chowrangi ki north wali lane XD
	//	bool isGreen;
		NodeBasedQueue<char> lane; //will fill vehicles in it
		void inputVehicles(); 
		void vehiclesArrive(); //gotta figure out: how to do it smoothly
		Lane(std::string n);
		
		//void permitGreenFor(double time); //schedular will handle / implement it
		void showTrafficLights(); //for that lane
		void displayLane();
};


#endif