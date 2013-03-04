/*
 *  Queue.cpp
 */

#include "Queue.h"

using namespace std;

Queue::Queue( int maxSize )
{
	max = maxSize;
	front = 0;
	rear = -1;
	data = new coordQ [max];
}

Queue::Queue( const Queue& copiedQueue )
{
	max = copiedQueue.max;
	data = new coordQ [max];
	front = copiedQueue.front;
	rear = copiedQueue.rear;
	coordQ * copiedPtr = copiedQueue.data;
	coordQ * newArray = data;
	for( int index = 0; index < max; index ++ )
	{
		newArray[index] = copiedPtr[index];
	}
	
}

Queue::~Queue()
{
	delete [] data;
}

bool Queue::enqueue( coordQ insert )
{

	if (rear == (max - 1) )
	{
		return false;
	}

	rear++;
	data[rear] = insert;
	return true;
}

coordQ Queue::dequeue()
{
	if (rear != -1 )
	{
	coordQ returned = data[front];
	for ( int index = front; index < rear; index ++ )
	{
		data[index] = data[index+1];
	}
	rear--;

	return returned;
	}
}

bool Queue::empty() const
{
	if (rear == -1)
	{
		return true;
	}

	return false;

}

bool Queue::full() const
{
	if (rear == (max-1))
	{
		return true;
	}
	
	return false;
}

bool Queue::clear ()
{
	rear = -1;
	return true;
}

Queue& Queue::operator=( const Queue& copiedQueue )
{
	max = copiedQueue.max;
	data = new coordQ [max];
	front = copiedQueue.front;
	rear = copiedQueue.rear;
	coordQ * copiedPtr = copiedQueue.data;
	coordQ * newArray = data;
	for( int index = 0; index < max; index ++ )
	{
		newArray[index] = copiedPtr[index];
	}
	
}






