#include "queue.h"
#include <iostream>

template <typename T>
	Node<T>::Node(){
		next = NULL;
	}
template <typename T>
	Node<T>::Node(T data)
	{
		this->data = data;
		next = NULL;
	}
template <typename T>
	T Node<T>::getData()
	{
		return data;
	}
template <typename T>
	Node<T>* Node<T>:: getNext()
	{
		return next;
	}
//template <typename T>
//	Node<T>::Node<T>* getPrev()
//	{
//		return prev;
//	}
template <typename T>
	void Node<T>:: setData(T data)
	{
		this->data = data;
	}
template <typename T>
	void Node<T>:: setNext(Node<T>* next)
	{
		this->next = next;
	}
//template <typename T>
//	Node<T>::void setPrev(Node<T>* prev)
//	{
//		this->prev = prev;
//	}
	
template <typename T>
NodeBasedQueue<T>::NodeBasedQueue() {
	front = NULL;
	back = NULL;
	size = 0;
}
template <typename T>
NodeBasedQueue<T>::NodeBasedQueue(const NodeBasedQueue& other) {
//	size = other.size; self note: can't do this if I want to use enqueue to handle the insertion
	Node<T>* current = other.front;
	while(current != NULL){
		enqueue(current->getData());
		current = current->getNext();
	}
}
template <typename T>
NodeBasedQueue<T>& NodeBasedQueue<T>::operator = (const NodeBasedQueue& other) { 
	if(this!=&other){
		// 1. delete the existing list
		Node<T>* toDelete = front;
		while(toDelete != NULL){
			Node<T>* saveToDelete_s_next = toDelete->getNext();
			delete toDelete;
			toDelete = saveToDelete_s_next;
		}
		front = back = NULL;
		size = 0;
		//2. copying the other list
		Node<T>* current = other.front;
		while(current != NULL){
		enqueue(current->getData());
		current = current->getNext();
		}
	}
	
return *this;
}
template <typename T>
NodeBasedQueue<T>::~NodeBasedQueue() {
	Node<T>* toDelete = front;
		while(toDelete != NULL){
			Node<T>* saveToDelete_s_next = toDelete->getNext();
			delete toDelete;
			toDelete = saveToDelete_s_next;
		}
		front = back = NULL;
		size = 0;
}
template <typename T>
void NodeBasedQueue<T>::enqueue (const T& data) {
	Node<T>* newNode = new Node<T>(data);
	if(front == NULL){
		front = newNode;
		back = newNode;
		size++;
	}else{
		back->setNext(newNode);
		back = newNode;
		back->setNext(NULL);
		size++;
	}
}
template <typename T>
T NodeBasedQueue<T>::dequeue () {
	if(front == NULL){
	//	std::cout<<"UnderFlow!"<<std::endl;
	//	return -1; //-1
	 throw std::runtime_error("Underflow!\n");
	}
	
		Node<T>* temp = front;
		T removedData = temp->getData();
		front = front->getNext();
		if(front == NULL){ //yani keh aik hi node thi list main, tou ab dequeue k baad whole list becomes empty
			back = NULL; 
		}
		delete temp;
		size--;
		return removedData; //returning the deleted data
}
template <typename T>
T NodeBasedQueue<T>::peek() const {
	if(isEmpty()){
//		std::cout<<"Nothing to see!\n";
		//return;
		 throw std::runtime_error("Queue is empty\n");
	}
			return front->getData();
}
template <typename T>
bool NodeBasedQueue<T>::isEmpty() const { return front == NULL; }
template <typename T>
int NodeBasedQueue<T>::getSize() const {
//	int count = 0;
//	Node* current = front;
//	while(current->getNext()!=NULL){
//		current = current->getNext();
//		count++;
//	}
//	return count;
	return size;
}
template <typename T>
void NodeBasedQueue<T>::print() const{
	Node<T>* current = front;
	for(int i=0; i<size; i++){
		std::cout<<current->getData()<<" ";
		current = current->getNext();
	}
}


template class Node<int>;
template class Node<double>;
template class Node<char>;
template class Node<std::string>;

template class NodeBasedQueue<int>;
template class NodeBasedQueue<double>;
template class NodeBasedQueue<char>;
template class NodeBasedQueue<std::string>;