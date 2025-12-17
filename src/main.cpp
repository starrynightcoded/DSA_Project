#include <iostream>
#include "lane.h"
using std::cout;
using std::endl;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
 
	Lane north("north");
	north.inputVehicles();
	north.displayLane();
	return 0;
}