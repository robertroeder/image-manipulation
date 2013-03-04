/*
 *  UnsortedList.h
 */

#include <iostream>

struct point{
	int x;
	int y;
};


struct node {
	point pixel;
	node* next;
};

class UnsortedList {
public:
    UnsortedList();
//    ~UnsortedList();
    void MakeEmpty();
    bool IsFull();
    int LengthIs();
    void RetrieveItem(point&, bool&);
    void InsertItem(point);
    void DeleteItem(point);
    void ResetList();
    bool IsLastItem();
    void GetNextItem(point&);
	void operator=( UnsortedList&);
	
private:
    int length;
    node* listData;
    node* currentPos;
	
};