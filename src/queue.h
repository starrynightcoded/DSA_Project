#ifndef QUEUE_H
#define QUEUE_H



//template <typename T>
//class Node;

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
//	Node<T>* getPrev(){}
	void setData(T data);
	void setNext(Node<T>* next);
	//void setPrev(Node<T>* prev){}
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
#endif