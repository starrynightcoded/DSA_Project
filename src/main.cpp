#include <iostream>
#include "queue.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	std::cout<<"Hello World"<<std::endl;
	std::cout<<"Testing queue:\n";
	NodeBasedQueue<int> queue;
	for(int i=0; i<4; i++){
		queue.enqueue(i);
	}
	queue.print();
	return 0;
}