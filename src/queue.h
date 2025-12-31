#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include <string>
class Car;
template <typename T>
class Node{
private:
	T data;
	Node<T>* next;

public:
	Node();
	Node(T data);
	T getData();
	Node<T>* getNext();
	void setData(T data);
	void setNext(Node<T>* next);
};

template <typename T>
class Queue{
public:
	virtual ~Queue() {}
    virtual void enqueue(const T& data) = 0;
    virtual T dequeue() = 0;
    virtual T peek() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int getSize() const = 0;
};

template <typename T>
class NodeBasedQueue : public Queue<T>{
private:
    Node<T>* front;
    Node<T>* back;
    int size;

public:
    NodeBasedQueue();
    NodeBasedQueue(const NodeBasedQueue<T>& other);
    NodeBasedQueue<T>& operator=(const NodeBasedQueue<T>& other);
    ~NodeBasedQueue();

    void enqueue(const T& data) override;
    T dequeue() override;
    T peek() const override;
    bool isEmpty() const override;
    int getSize() const override;
    void print() const;
};

/* ================= Node ================= */

template <typename T>
Node<T>::Node(){
	next = NULL;
}

template <typename T>
Node<T>::Node(T data){
	this->data = data;
	next = NULL;
}

template <typename T>
T Node<T>::getData(){
	return data;
}

template <typename T>
Node<T>* Node<T>::getNext(){
	return next;
}

template <typename T>
void Node<T>::setData(T data){
	this->data = data;
}

template <typename T>
void Node<T>::setNext(Node<T>* next){
	this->next = next;
}

/* ================= NodeBasedQueue ================= */

template <typename T>
NodeBasedQueue<T>::NodeBasedQueue(){
	front = NULL;
	back = NULL;
	size = 0;
}

template <typename T>
NodeBasedQueue<T>::NodeBasedQueue(const NodeBasedQueue<T>& other){
	front = back = NULL;
	size = 0;

	Node<T>* current = other.front;
	while(current != NULL){
		enqueue(current->getData());
		current = current->getNext();
	}
}

template <typename T>
NodeBasedQueue<T>& NodeBasedQueue<T>::operator=(const NodeBasedQueue<T>& other){
	if(this != &other){
		Node<T>* toDelete = front;
		while(toDelete != NULL){
			Node<T>* next = toDelete->getNext();
			delete toDelete;
			toDelete = next;
		}

		front = back = NULL;
		size = 0;

		Node<T>* current = other.front;
		while(current != NULL){
			enqueue(current->getData());
			current = current->getNext();
		}
	}
	return *this;
}

template <typename T>
NodeBasedQueue<T>::~NodeBasedQueue(){
	Node<T>* toDelete = front;
	while(toDelete != NULL){
		Node<T>* next = toDelete->getNext();
		delete toDelete;
		toDelete = next;
	}
	front = back = NULL;
	size = 0;
}

template <typename T>
void NodeBasedQueue<T>::enqueue(const T& data){
	Node<T>* newNode = new Node<T>(data);

	if(front == NULL){
		front = back = newNode;
	}else{
		back->setNext(newNode);
		back = newNode;
	}
	size++;
}

template <typename T>
T NodeBasedQueue<T>::dequeue(){
	if(front == NULL){
		throw std::runtime_error("Underflow!");
	}

	Node<T>* temp = front;
	T removedData = temp->getData();
	front = front->getNext();

	if(front == NULL){
		back = NULL;
	}

	delete temp;
	size--;
	return removedData;
}

template <typename T>
T NodeBasedQueue<T>::peek() const{
	if(isEmpty()){
		throw std::runtime_error("Queue is empty");
	}
	return front->getData();
}

template <typename T>
bool NodeBasedQueue<T>::isEmpty() const{
	return front == NULL;
}

template <typename T>
int NodeBasedQueue<T>::getSize() const{
	return size;
}

template <typename T>
void NodeBasedQueue<T>::print() const{
	Node<T>* current = front;
	while(current != NULL){
		std::cout << current->getData() << " ";
		current = current->getNext();
	}
}
template class Node<Car*>;
template class NodeBasedQueue<Car*>;

#endif
