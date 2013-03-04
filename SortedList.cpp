/*
 *  SortedList.cpp
 */
 

#include "SortedList.h"

SortedList::SortedList()
{
	length = 0;
	listData = NULL;
	currentPos = NULL;
}

/*SortedList::~SortedList()
{
	sortedNode* ptr;
	while (listData!=NULL) 
	{
		ptr = listData->next;
		delete listData;
		listData = ptr;
		length--;
		
	}
}
*/
void SortedList::MakeEmpty()
{
	sortedNode* ptr;
	while (length > 0) 
	{
		ptr = listData->next;
		delete listData;
		listData = ptr;
		length--;
		
	}	
}

bool SortedList::IsFull()
{
	sortedNode* ptr;
	ptr = new sortedNode;
	if ( ptr == NULL )
	{
		return true;
	}
	
	else
	{
		delete ptr;
		return false;
	}
}

int SortedList::LengthIs()
{
	return length;
}

void SortedList::RetrieveItem(nodeData& retrieve, bool& found)
{
	sortedNode* location;
	
	location = listData;
	found = false;
	
	while( (location != NULL) && !found) {
		
		if ((location->data).size < retrieve.size) 
			location = location->next;
		
		else if ((location->data).size == retrieve.size) 
		{
			if ((((location->data).centroid).x == (retrieve.centroid).x ) && (((location->data).centroid).y == (retrieve.centroid).y ))
			{	
				retrieve = location->data;
			found = true;	
			}
			
			else 
			location = location->next;
		}
		else
			location = NULL;
	
	}
}

void SortedList::InsertItem( nodeData newItem )
{	
	sortedNode* newNode;
	sortedNode* predLoc; 
	sortedNode* location;
	bool found;

	found = false;
	location = listData;
	predLoc = NULL;
	
	while( location != NULL && !found) {
		if ((location->data).size < newItem.size) {
			predLoc = location;
			location = location->next;
		}
		else
			found = true;
	} 
	
	newNode = new sortedNode;
	(newNode->data) = newItem;
	(newNode->data).size =newItem.size;
	(newNode->data).centroid.x = newItem.centroid.x;
	(newNode->data).centroid.y = newItem.centroid.y;
	(newNode->data).orientation = (-1)*newItem.orientation;
	(newNode->data).eccentricity = newItem.eccentricity;
	(newNode->data).mean = newItem.mean;
	(newNode->data).median = newItem.median;
	(newNode->data).min = newItem.min;
	(newNode->data).max = newItem.max;
	(newNode->data).coordList = newItem.coordList;
	
	if (predLoc == NULL) {
		newNode->next = listData;    //cases (1) and (4)
		listData = newNode;
	}
	else {
		newNode->next = location;
		predLoc->next = newNode;    //cases (2) and (3)
	}
	length++;
} 
	

void SortedList::DeleteItem(nodeData item)
{
		sortedNode* location = listData;
		sortedNode* tempLocation;
	
	
		if((item.size == (listData->data).size)&&((item.centroid).x == ((listData->data).centroid).x)&&((item.centroid).y == ((listData->data).centroid).y))
		{
			tempLocation = listData; // special case
			listData = listData->next;  
		}
		else {

			while(!((item.size == ((location->next)->data).size)&&((item.centroid).x == (((location->next)->data).centroid).x)&&((item.centroid).y == (((location->next)->data).centroid).y)))
				location = location->next;
			
			// delete node at location->next
			tempLocation=location->next;
			location->next = tempLocation->next;
		} 
		

		delete tempLocation;
		length--;
} 
	
void SortedList::ResetList()
{
	currentPos = listData;
}

bool SortedList::IsLastItem()
{
	return(currentPos == NULL);
} 
	

void SortedList::GetNextItem(nodeData& item)
{
	item.size = (currentPos->data).size;
	item.centroid.x = (currentPos->data).centroid.x;
	item.centroid.y = (currentPos->data).centroid.y;
	item.orientation =(currentPos->data).orientation;
	item.eccentricity = (currentPos->data).eccentricity;
	item.mean = (currentPos->data).mean;
	item.median = (currentPos->data).median;
	item.min = (currentPos->data).min;
	item.max = (currentPos->data).max;
	item.coordList = (currentPos->data).coordList;
	currentPos = currentPos->next;
}






