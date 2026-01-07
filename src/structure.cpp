#include <iostream>
#include "structure.h"
Car::Car(){id = 0;}
Car::Car(int id): id(id){}
int Car::getId(){return id; }

Lane::Lane(int id, std::string n): laneId(id), name(n), state("RED"), waitingTime(0), greenTime(0) {isSourceLane= false;}
void Lane::addCar(Car* car){
	 if(cars.getSize() < 10){
		cars.enqueue(car);
	}
}
Car* Lane::removeCar(){
	if(cars.isEmpty()){
		return NULL;
	}
	totalCarsExited++;
	return cars.dequeue();
}
Car* Lane::peekCar() const{
	if(cars.isEmpty()){
		return NULL;
	}
	return cars.peek();
}
int Lane::getLaneLength() const {
    return cars.getSize();
}
bool Lane::isEmpty() const {
    return cars.isEmpty();
}
std::string Lane::getName() const {
    return name;
}
int Lane::getId() const {
    return laneId;
}
void Lane::setGreenTime(int g){
	greenTime = g;
}
void Lane::updateGreenTime(int g) {
	this->setGreenTime(g);
}

void Lane::resetWaitingTime(){
    waitingTime = 0;
}
void Lane::incrementWaitingTime(){
    waitingTime++;
}
void Lane::setState(std::string s){state = s;}
std::string Lane::getState(){return state;}

void Lane::display() const {
	int size = getLaneLength();
	for(int i=0; i<size; i++){
		std::cout<<"* ";
	}
	std::cout<<"\n";
}

Intersection::Intersection(){
			Lanes["N"] = new Lane(0, "N");
			Lanes["S"] = new Lane(1, "S");
			Lanes["E"] = new Lane(2, "E");
			Lanes["W"] = new Lane(3, "W");
	}
Intersection::~Intersection(){
			for(auto &i : Lanes){
				delete i.second;
			}
}
bool Intersection::addCarToLane(const std::string &name, Car* car){
		//int count = lanes[name]->getQueueLength(); 
		if (Lanes.find(name) != Lanes.end()) {
			 		Lanes[name]->addCar(car);
			return true;
	    }
	    return false;
	}
	
	//dequeueing according to algo 
	void Intersection::processGreen(const std::string& lane1,
                                	const std::string& lane2,
                                	int greenTime){
		for(int i=0; i<greenTime; i++){
			 if(!Lanes[lane1]->isEmpty())
            	Lanes[lane1]->removeCar();
	        if(!Lanes[lane2]->isEmpty())
	            Lanes[lane2]->removeCar();
			}
	}
void Intersection::updateWaitingTimes(const std::string& g1,
                                      const std::string& g2) {
    	for(auto& pair : Lanes) {
	        if(pair.first == g1 || pair.first == g2)
	            pair.second->resetWaitingTime();
	        else
	            pair.second->incrementWaitingTime();
	    }
}
Lane* Intersection::getLane(const std::string& name) {
    return Lanes[name];
}

std::unordered_map<std::string, Lane*>& Intersection::getAllLanes() {
    return Lanes;
}
