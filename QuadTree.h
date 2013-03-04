/*
 *  QuadTree.h
 *
 */
#include <iostream>
#include <cmath>
#include "SortedList.h"

using namespace std;


struct treeNode {
	coord point;
	bool tagged;
	treeNode* NW;
	treeNode* SW;
	treeNode* SE;
	treeNode* NE;
};

class QuadTree {
public:
    QuadTree();
	QuadTree( SortedList& );
    ~QuadTree();
    void MakeEmpty();
    int LengthIs();
	void FindClosest( coord, coord& );
	void insert( treeNode*&, coord );
    void InsertItem( coord );
    void ResetTree();
    bool IsLeaf();
	
private:
    int length;
    treeNode* treeData;
    treeNode* currentPos;
	
};

void destroy( treeNode* );
void minFind ( treeNode* tree, coord query, coord& closest, double& minDist );

