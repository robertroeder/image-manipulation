/*
 *  QuadTree.cpp
 */
 

#include "QuadTree.h"

QuadTree::QuadTree()
{
	treeData = NULL;
	currentPos = treeData;
	length = 0;
}


QuadTree::QuadTree( SortedList& source )
{
	//Create the first node in the tree
	nodeData next;
	source.ResetList();
	source.GetNextItem( next );
	treeData = new treeNode;
	treeData -> tagged = false;
	treeData -> NW = NULL;
	treeData -> SW = NULL;
	treeData -> SE = NULL;
	treeData -> NE = NULL;
	currentPos = treeData;
	(currentPos->point).x = (next.centroid).x;
	(currentPos->point).y = (next.centroid).y;
	length = 1;
	
	//Iterate through the sorted list and insert items into tree
	while ( !source.IsLastItem() )
	{
		source.GetNextItem( next );
		insert( treeData, next.centroid );
	}
	
}


QuadTree::~QuadTree()
{
	//destroy( treeData );
}

void destroy( treeNode* tree )
{
	//If the pointer points to something, destroy what it points to
	if( tree != NULL )
	{
		destroy( tree->NW );
		destroy( tree->SW );
		destroy( tree->NE );
		destroy( tree->SE );
		delete tree;
	}
}

void QuadTree::MakeEmpty()
{
	//Destroy everything and set length to 0
	destroy( treeData );
	length = 0;
}

int QuadTree::LengthIs()
{
	return length;
}

void QuadTree::FindClosest( coord query, coord& returned )
{
	coord closest;
	coord current;
	double minDist;
	bool found = false;
	double dist;
	
	//Initialize the minimum distance
	if( treeData -> tagged == false )
	{
	current.x = (treeData->point).x;
	current.y = (treeData->point).y;
	dist = pow( current.x - query.x, 2) + pow( current.y- query.y, 2);
	dist = pow( dist, 0.5 );
	minDist = dist;
	closest = current;
	}
	else {
		minDist = 10000;
	}

	currentPos = treeData;
	
	//Traverse the tree through the path that the query falls in
	if((query.x < (currentPos->point).x) && (query.y < (currentPos->point).y))
		currentPos = currentPos->SW;
	
	else if((query.x < (currentPos->point).x) && (query.y >= (currentPos->point).y))
		currentPos = currentPos->NW;
	
	else if((query.x >= (currentPos->point).x) && (query.y < (currentPos->point).y))
		currentPos = currentPos->SE;
	
	else if((query.x >= (currentPos->point).x) && (query.y >= (currentPos->point).y))
		currentPos = currentPos->NE;
	
	while ( currentPos != NULL )
	{
		if ( currentPos -> tagged == false)
		{
		current.x = (currentPos->point).x;
		current.y = (currentPos->point).y;
		dist = pow( current.x - query.x, 2) + pow( current.y- query.y, 2);
		dist = pow( dist, 0.5 );
		if (dist < minDist )
		{
			minDist = dist;
			closest.x = current.x;
			closest.y = current.y;
		}
		}
		if((query.x < (currentPos->point).x) && (query.y < (currentPos->point).y))
			currentPos = currentPos->SW;
		
		else if((query.x < (currentPos->point).x) && (query.y >= (currentPos->point).y))
			currentPos = currentPos->NW;
		
		else if((query.x >= (currentPos->point).x) && (query.y < (currentPos->point).y))
			currentPos = currentPos->SE;
		
		else if((query.x >= (currentPos->point).x) && (query.y >= (currentPos->point).y))
			currentPos = currentPos->NE;
		
	}
	
	//Go back to the top of the tree and search only those subtrees falling withing the circle of min distance from query
	currentPos = treeData;
	minFind ( currentPos, query, closest, minDist );
	currentPos = treeData;
	
	//Find the final closest point and tag it
	while ( !found )
	{
		if ( ((currentPos->point).x == closest.x) && ((currentPos->point).y == closest.y))
		{
			currentPos -> tagged = true;
			found = true;
		}
		if((closest.x < (currentPos->point).x) && (closest.y < (currentPos->point).y))
			currentPos = currentPos->SW;
		
		else if((closest.x < (currentPos->point).x) && (closest.y >= (currentPos->point).y))
			currentPos = currentPos->NW;
		
		else if((closest.x >= (currentPos->point).x) && (closest.y < (currentPos->point).y))
			currentPos = currentPos->SE;
		
		else if((closest.x >= (currentPos->point).x) && (closest.y >= (currentPos->point).y))
			currentPos = currentPos->NE;
		
	}
	
	
	
	returned = closest;
	
}

void minFind ( treeNode* tree, coord query, coord& closest, double& minDist )
{
	coord current;
	double dist;
	
	//Make sure that the pointer points to something
	if ( tree!=NULL)
	{
		//Make sure that the point is not tagged
		if ( tree -> tagged == false)
		{
			
		//Test the distance at the current point
		current = tree->point;
		dist = pow( current.x - query.x, 2) + pow( current.y- query.y, 2);
		dist = pow( dist, 0.5 );
		if (dist < minDist )
		{
			minDist = dist;
			closest = current;
		}
		}
		
		//Test if each subtree has a place inside the circle of min distance from query
		if((query.x < (tree->point).x) && (query.y < (tree->point).y))
		{
			minFind( tree->SW, query, closest, minDist );
			
			if ( abs( query.x - (tree->point).x ) < minDist )
				minFind( tree->SE, query, closest, minDist );
			
			if ( abs( query.y - (tree->point).y ) < minDist )
				minFind( tree->NW, query, closest, minDist );
			
			
		}
		
		else if((query.x < (tree->point).x) && (query.y >= (tree->point).y))
		{
			minFind( tree->NW, query, closest, minDist );
			
			if ( abs( query.x - (tree->point).x ) < minDist )
				minFind( tree->NE, query, closest, minDist );
			
			if ( abs( query.y - (tree->point).y ) < minDist )
				minFind( tree->SW, query, closest, minDist );
			
			
		}
		
		else if((query.x >= (tree->point).x) && (query.y < (tree->point).y))
		{
			minFind( tree->SE, query, closest, minDist );
			
			if ( abs( query.x - (tree->point).x ) < minDist )
				minFind( tree->SW, query, closest, minDist );
			
			if ( abs( query.y - (tree->point).y ) < minDist )
				minFind( tree->NE, query, closest, minDist );
			
			
		}
		
		else if((query.x >= (tree->point).x) && (query.y >= (tree->point).y))
		{
			minFind( tree->NE, query, closest, minDist );
			
			if ( abs( query.x - (tree->point).x ) < minDist )
				minFind( tree->NW, query, closest, minDist );
			
			if ( abs( query.y - (tree->point).y ) < minDist )
				minFind( tree->SE, query, closest, minDist );
			
		}
	}
}


void QuadTree::InsertItem( coord inserted )
{
	insert( treeData, inserted );
}



void QuadTree::insert( treeNode*& tree, coord inserted )
{
	//If the pointer is NULL, create a new node. End of recursion
	
	if (tree == NULL)   // base case
	{	
		tree = new treeNode;
		tree -> NW = NULL;
		tree -> SW = NULL;
		tree -> SE = NULL;
		tree -> NE = NULL;
		tree -> tagged = false;
		(tree->point).x = inserted.x;
		(tree->point).y = inserted.y;
		length++;
	}
	
	//If not, determine the appropriate tree to traverse
	else if((inserted.x < (tree->point).x) && (inserted.y < (tree->point).y))
		insert(tree->SW, inserted);
	
	else if((inserted.x < (tree->point).x) && (inserted.y >= (tree->point).y))
		insert(tree->NW, inserted);
	
	else if((inserted.x >= (tree->point).x) && (inserted.y < (tree->point).y))
		insert(tree->SE, inserted);
	
	else if((inserted.x >= (tree->point).x) && (inserted.y >= (tree->point).y))
		insert(tree->NE, inserted);

}


void QuadTree::ResetTree()
{
	currentPos = treeData;	
}

bool QuadTree::IsLeaf()
{
	return ( (currentPos->SW == NULL ) && (currentPos->NW == NULL ) && (currentPos->SE == NULL ) && (currentPos->NE == NULL ) );
}






