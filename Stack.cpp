/*
 *  Robert_Roeder
 *
 */

#include "Stack.h"

using namespace std;

Stack::Stack(int maxsize)
{
	max = maxsize;
	data = new coordS [max];
	top = -1;
}

Stack::~Stack()
{
	delete [] data;
}



void Stack::push(coordS value)
{
 if( !full() )
 {
  top++;
  data[top] = value;
 }
}

coordS Stack::pop()
{
 coordS toReturn;
 
 if( !empty() )
 {
  toReturn = data[top];
  top--;

  return toReturn;
 }
}

bool Stack::empty()
{
 return top == -1;
}

bool Stack::full()
{
 return top == (max - 1);
}

void Stack::clear()
{
 top = -1;
}

