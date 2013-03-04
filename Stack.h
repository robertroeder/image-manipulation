/*
 *  Robert_Roeder
 *
 */



#ifndef Stack_h
#define Stack_h

#include "Stack.h"

using namespace std;

struct coordS {
	int i;
	int j;
};


class Stack
{
 public:
	// constructors and destructors
    Stack( int = 15 );
    ~Stack();
	
    void push( coordS );
    coordS pop();
    bool empty();
    bool full();
    void clear();
	
private:
    int max;
    int top;
    coordS* data;
};

#endif
