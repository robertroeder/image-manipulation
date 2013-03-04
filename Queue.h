/*
 *  Queue.h
 *
 */
#include <iostream>

using namespace std;

struct coordQ {
	int i;
	int j;
};



class Queue
{
	private:
	int max;
	int front;
	int rear;
	coordQ * data;
	
	public:
	Queue (int=10); //defaults to 10
	Queue (const Queue&);
	~Queue ( );
	bool enqueue (coordQ);
	coordQ dequeue ( );
	bool empty ( ) const;
	bool full ( ) const;
	bool clear ( );
	Queue& operator = (const Queue&);
	
};

 