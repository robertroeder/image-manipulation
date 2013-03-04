/*
 *  SortedList.h
 *
 */
#include <iostream>
#include "UnsortedList.h"

using namespace std;

struct coord {
	double x;
	double y;
};

struct nodeData {
	int size;
	coord centroid;
	double orientation;
	double eccentricity;
	double mean;
	double median;
	int min;
	int max;
 	UnsortedList coordList;
};


struct sortedNode {
	nodeData data;
	sortedNode* next; 
};

class SortedList {
public:
    SortedList();
   // ~SortedList();
    void MakeEmpty();
    bool IsFull();
    int LengthIs();
    void RetrieveItem(nodeData&, bool&);
    void InsertItem(nodeData);
    void DeleteItem(nodeData);
    void ResetList();
    bool IsLastItem();
    void GetNextItem(nodeData&); 
	
private:
    int length;
    sortedNode* listData;
    sortedNode* currentPos;
	
};