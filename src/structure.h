#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "queue.h"
#include <unordered_map>
class Car{
	public:
		Car();
		Car(int id);
		int id;
		int getId();
};

class Lane{
	int laneId;
	std::string name;//N-S E-W

	int greenTime; //assigned by algo
	NodeBasedQueue <Car*> cars;

	public:
		int waitingTime;
		std::string state; //red or green
		bool isSourceLane;
		NodeBasedQueue<Car*> lane; //will fill vehicles in it
		int totalCarsExited = 0;
		Lane(int id, std::string n);
	    void addCar(Car* car);
	    Car* removeCar();
	    Car* peekCar() const;

   		int getLaneLength() const;
    	bool isEmpty() const;
    	std::string getName() const;
		int getId() const;
		int getGreenTime() const;
		void setGreenTime(int g);
		void setState(std::string s);
		std::string getState();
    	void resetWaitingTime();
    	void incrementWaitingTime();
    void updateGreenTime(int greenTime);
    void display() const; //display no of cars by a * in that particular lane
    
};

class Intersection{
	public:
		int intersectionId;
	
		std::unordered_map<std::string, Lane*> Lanes; // <"A", lane(N S E W)>
		Intersection();
		~Intersection();
		void processGreen(const std::string& lane1,
                          const std::string& lane2,
                        int greenTime);
        void updateWaitingTimes(const std::string& g1, const std::string& g2);
		Lane* getLane(const std::string& name);
		std::unordered_map<std::string, Lane*>& getAllLanes();
		bool addCarToLane(const std::string &name, Car* car);
		std::unordered_map<std::string, std::pair<Intersection*, std::string>> outgoing; 
};

#endif
