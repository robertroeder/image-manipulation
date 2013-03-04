#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#include "image.h"
#include "Stack.h"
#include "Queue.h"
#include "QuadTree.h"

using namespace std;

/*Prototypes*/

int readImageHeader(char[], int&, int&, int&, bool&, bool&);	//reads the information provided by an image when it is saved in the .pgm format
int readImage(char[], ImageType&);	//reads in an image from a file, has its pixel values stored in an array, and the image width, height, and number of gray-levels are placed under the appropriate variables
int writeImage(char[], ImageType&);	//writes out an image to a file in the format of .pgm
int computeComponents(ImageType& inputImage, ImageType& outputImage, ImageType& image3, bool BFS, SortedList& ListOfRegions); // Computes and labels the number of regions in the image
void findComponentBFS(ImageType& inputImage, ImageType& outputImage, int label, Queue& queue, nodeData& region); // Performs a breadth-first search recursively
void findComponentDFS(ImageType& inputImage, ImageType& outputImage, int label, Stack& stack); // Performs a depth-first search recursively
void deleteSmallComponents(SortedList& listOfRegions, int threshold);
double computeMoment( int p, int q, double xCenter, double yCenter, UnsortedList& list ); // Computes the p,q order moment for a region

int main()
{
	int i, j; 
	int sizeThreshold;
	int length;
	double A, B;
	int M, N, Q;
	int K;
	char choice = '\0';	
	int S, T, thresh;
	char reflectChoice = '\0';
	char searchChoice = '\0';
	bool BFSFlag;
	int components;
	bool type;
	bool vertFlag;
	bool continueProgram = true;
	bool fileRead = false;
	char filename[50];
	char filename2[50];
	char fileSave[50];
	int val;
	point pixel;
	
	SortedList ListOfRegions;
	UnsortedList pixelList;
	nodeData region;
	
	
	cout << endl << endl << endl << endl << endl;
	cout << "Welcome to Bobby and Will's image editor.";
	ImageType *image;
	
	// allocate memory for the image array
	image = new ImageType(1, 1, 255);
	
	
	ImageType *image2;
	image2 = new ImageType(1, 1, 255);
	
	ImageType *image3;
	image3 = new ImageType(1, 1, 255);
	
	// DRIVER MENU
	// Keep program running until quit
	while (continueProgram)
	{
		// Main Menu
		cout << endl << "///////////////////////////////////////////////////" << endl << "Enter the capital letter of your menu choice";
		if ( fileRead == false )
		{
			cout << endl << "WARNING: NO IMAGE FILE. YOU MUST FIRST READ A FILE.";
		}
		cout << endl << "A. Read an image file. WARNING: You will lose all unsaved changes." << endl;
		cout << "B. Save the image." << endl;
		cout << "C. Extract a subimage from the image." << endl;
		cout << "D. Compute the average gray-level value of the image." << endl;
		cout << "E. Enlarge the image." << endl;
		cout << "F. Shrink the image." << endl;
		cout << "G. Reflect the image over the horizontal or vertical axis." << endl;
		cout << "H. Translate the image." << endl;
		cout << "I. Rotate the image." << endl;
		cout << "J. Add an image to the current image." << endl;
		cout << "K. Subtract an image from the current image." << endl;
		cout << "L. Compute the negative of the image." << endl;
		cout << "M. Label and compute the number of regions in the image." << endl;
		cout << "N. Quit." << endl << endl;
		cout << "Enter Selection: ";
		cin >> choice;
		cout << endl << endl ;
		
		
		// Test for user input
		
		switch (choice)
		{
			case 'A':
				delete image;
				cout << endl << endl << "Please enter the file name of the image you would like to read/edit." << endl << "You may change this later. The name must be under 50 characters.";
				cout << endl << "File name: ";
				cin >> filename;
				
				// read image header
				readImageHeader(filename, N, M, Q, type, fileRead);
				
				// allocate memory for the image array
				
				if ( fileRead == true )
				{
				  image = new ImageType(N, M, Q);
				  readImage( filename, *image );
				  cout << "Image file read successfully." << endl;
				}
				
				else 
				{
					image = new ImageType(1,1,255);
				}
				break;
				
			case 'B':
				
				//Test that a file has been read and save the image
				if ( fileRead == true )
				{
				cout << endl << endl << "Enter the file name that you want to save the image under." << endl << " Be sure to use the .pgm extension." << endl;
				cin >> fileSave;
				writeImage(fileSave, *image);
				break;
				}
				
				cout << endl << endl << "Sorry, there is no current image.";
				break;
				
			case 'C':
				int nStart, nEnd, mStart, mEnd;
				
				//Test that a file has been read and crop the image
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
				
				// Get the subimage coordinates from the user and test that they are in the bounds
				
				cout << endl << "Enter the left column. (Between 0 and " << (N-2) << ", inclusive ): ";
				cin >> nStart;
				if ( nStart < 0 || nStart >= (N-1) )
				{
					cout << endl << "ERROR: Invalid dimension. Try again. " << endl;
					break;
				}
				cout << endl << "Enter the right column. (Between " << nStart+1 << " and " << (N-1) << ", inclusive ): ";
				cin >> nEnd;
				if ( nEnd <= nStart || nEnd >= N )
				{
					cout << endl << "ERROR: Invalid dimension. Try again. " << endl;
					break;
				}
				cout << endl << "Enter the top row. (Between 0 and " << (M-2) << ", inclusive ): ";
				cin >> mStart;
				if ( mStart < 0 || mStart >= (M-1) )
				{
					cout << endl << "ERROR: Invalid dimension. Try again. " << endl;
					break;
				}
				cout << endl << "Enter the bottom row. (Between " << mStart+1 << " and " << (M-1) << ", inclusive ): ";
				cin >> mEnd;
				if ( mEnd <= mStart || mEnd >= M )
				{
					cout << endl << "ERROR: Invalid dimension. Try again. " << endl;
					break;
				}
				(*image2).getSubImage( nStart, nEnd, mStart, mEnd, *image );
				*image = *image2;
				break;
				
			case 'D':
				
				//Test that a file has been read and compute the average gray-level
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
			    cout << endl << endl << "The average gray-level value is: " << (*image).meanGray();
				break;
								
			case 'E':
				
				//Test that a file has been read and enlarge the image
				
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
				//Get the enlargement factor from the user and test that it is between 0 and 10
			    cout << endl << endl << "Enter the enlargement factor S (Greater than 0 but less than 10): ";
				cin >> S;
				if ( S <= 0 || S >= 10)
				{
					cout << endl << "ERROR: Invalid S. Try Again." << endl;
					break;
				}
				
				(*image2).enlargeImage( S, *image );
				*image = *image2;
				
				break;
								
			case 'F':
				
				//Test that a file has been read and shrink the image
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
				//For the case that the image is tall make sure the shrinking factor is less than half of the width
				
				if ( N < M )
				{
			    cout << endl << endl << "Enter the shrinking factor S (Greater than 0 but less than " << N/2+1 << " ): ";
				cin >> S;
				if ( S <= 0 || S >= (N/2+1) )
				{
					cout << endl << "ERROR: Invalid S. Try Again." << endl;
					break;
				}
					
				}
				
				//For the case that the image is wide make sure the shrinking factor is less than half of the height
				
				else
				{
					cout << endl << endl << "Enter the shrinking factor S (Greater than 0 but less than " << M/2+1 << " ): ";
					cin >> S;
					if ( S <= 0 || S >= (M/2+1) )
					{
						cout << endl << "ERROR: Invalid S. Try Again." << endl;
						break;
					}
					
					
				}
				
				(*image2).shrinkImage( S, *image );
				*image = *image2;
				
				break;
				
			case 'G':
				
				//Test that a file has been read and reflect the image
				
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
					// Get the reflection axis from the user and test that it is within bounds. Set the vertFlag
				
					cout << endl << endl << "Please enter the capital letter of your choice." << endl << "A. Reflect over the vertical axis."; 
					cout << endl << "B. Reflect over the horizontal axis." << endl << endl << "Choice: ";
					cin >> reflectChoice;
					if ( reflectChoice == 'A' )
					{
						vertFlag = true;
					}
				
					else if ( reflectChoice == 'B' )
					{
						vertFlag = false;
					}
					
					else 					
					{
						cout << endl << "ERROR: Invalid choice. Try Again." << endl;
						break;
					}					
					
				(*image2).reflectImage( vertFlag, *image );
				*image = *image2;
				
				break;
				
			case 'H':
				
				//Test that a file has been read and translate the image
				
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
				//If the image is tall, test that the translation value is between zero and the width
				
				if ( N < M )
				{
					cout << endl << endl << "Enter the translation value T (Between 0 and " << N-1 << " ): ";
					cin >> T;
					if ( T < 0 || T >= N )
					{
						cout << endl << "ERROR: Invalid T. Try Again." << endl;
						break;
					}					
				}
				
				//If the image is wide, test that the translation value is between zero and the height
				
				else
				{
					cout << endl << endl << "Enter the translation value T (Between 0 and " << M-1 << " ): ";
					cin >> T;
					if ( T < 0 || T >= M )
					{
						cout << endl << "ERROR: Invalid T. Try Again." << endl;
						break;
					}										
				}
							
				(*image2).translateImage( T, *image );
				*image = *image2;
				
				break;
				
			case 'I':
				
				//Test that a file has been read and rotate the image
				
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
				//Test that the angle of rotation is between 0 and 360
				
			    cout << endl << endl << "Enter the angle of rotation: ";
				cin >> S;
				if ( S < 0 || S > 360)
				{
					cout << endl << "ERROR: Invalid S. Try Again." << endl;
					break;
				}
				
				(*image2).rotateImage( S, *image );
				*image = *image2;
				
				break;
				
			case 'J':
				
				//Test that a file has been read and add two images
				
				if ( fileRead == true )
				{
					int Noriginal, Moriginal;
					delete image2;
					
					//Get the second image file name from user and attempt to open image
					
					cout << endl << endl << "Enter the file name that you want to add to the current file." << endl << " Be sure the image is the same size as the first." << endl << "File: ";
					cin >> filename2;
					
					
					readImageHeader(filename2, N, M, Q, type, fileRead);
					
					if ( fileRead == true )
					{
						image2 = new ImageType(N, M, Q);
						readImage( filename2, *image2 );
						cout << "Image file read successfully." << endl;
					}
					
					else 
					{
						image = new ImageType(1,1,255);
					}
					
					(*image).getImageInfo(Noriginal, Moriginal, Q);
					
					
					if (Moriginal == M && Noriginal == N)
					{
						(*image) + (*image2);
					}
				
				//If the images are not the same size, or the image file name was invalid, return error
					
				else
				{
					cout << "Images not the same size, please try another image.";
				}

					
					break;
				}
				
				cout << endl << endl << "Sorry, there is no current image.";
				break;
				
			case 'K':
				
				//Test that a file has been read and subtract two images
				
				if ( fileRead == true )
				{
					int Noriginal, Moriginal;
					delete image2;
					
					//Get the second image file name from the user and attempt to open image
					
					cout << endl << endl << "Enter the file name that you want to subtract from the current file." << endl << " Be sure the image is the same size as the first." << endl << "File: ";
					cin >> filename2;
					
					readImageHeader(filename2, N, M, Q, type, fileRead);
					
					if ( fileRead == true )
					{
						image2 = new ImageType(N, M, Q);
						readImage( filename2, *image2 );
						cout << "Image file read successfully." << endl;
					}
					
					else 
					{
						image = new ImageType(1,1,255);
					}
					
					(*image).getImageInfo(Noriginal, Moriginal, Q);
					
					//If the images are not the same size, or the image file name was invalid, return error
					
					if (Moriginal == M && Noriginal == N)
					{
						(*image) - (*image2);
					}
					
					else
					{
						cout << "Images not the same size, please try another image.";
					}
					
					
					break;
				}
				
				cout << endl << endl << "Sorry, there is no current image.";
				break;
				
			case 'L':
				
				//Test that a file has been read and negate the image
				
				if ( fileRead == true )
				{
					(*image).negateImage();
					cout << "The image has beem negated";
				}
					
				else 
				{
					image = new ImageType(1,1,255);
					cout << endl << endl << "Sorry, there is no current image.";
				}
										
					break;
				
			case 'M':
				
				//Test that a file has been read and count the regions in the image
				
				if ( fileRead == false )
				{
					cout << endl << endl << "Sorry, there is no current image.";
					break;
				}
				
				//Obtain threshold from user and test that it is within bounds
				
				cout << endl << endl << "Please enter the threshold you would like to use." << endl << "(Hint: Approx. 127 is a good value)" << endl;
				cin >> thresh;
				
				if ( thresh < 0 || thresh > 255 )
				{
					cout << endl << "ERROR: Invalid choice. Try Again." << endl;
					break;
				}
				
				//Get search type from user and return error if invalid entry
				
				cout << endl << endl << "Please enter the capital letter of your choice." << endl << "A. Breadth-First Search."; 
				cout << endl << "B. Depth-First Search." << endl << endl << "Choice: ";
				cin >> searchChoice;
				if ( searchChoice == 'A' )
				{
					BFSFlag = true;
				}
				
				else if ( searchChoice == 'B' )
				{
					BFSFlag = false;
				}
				
				else 					
				{
					cout << endl << "ERROR: Invalid choice. Try Again." << endl;
					break;
				}					
				
				//Threshold, diate, erode, and then compute the components of the image
				*image3 = *image;
				
				(*image2).thresholdImage( thresh, *image );
				*image = *image2;
				(*image2).dilateImage( *image );
				*image = *image2;
				(*image2).erodeImage( *image );
				*image = *image2;
				components = computeComponents( *image, *image2, *image3, BFSFlag, ListOfRegions );
				
				cout << endl << "There are " << components << " regions in this image.";
				*image = *image2;
				
				// Delete small regions by getting threshold
				cout << endl << endl << "Please enter the threshold of region sizes you would like to delete." << endl;
				cin >> sizeThreshold;
				sizeThreshold = abs(sizeThreshold);
				
				deleteSmallComponents(ListOfRegions, sizeThreshold);
				
				//Print the submenu for the user
				cout << endl << endl << "Please enter the capital letter of your choice." << endl << "A. Display regions having size between X and Y."; 
				cout << endl << "B. Display regions having orientation between X and Y." << endl << "C. Display regions having eccentricity between X and Y.";
				cout << endl << "D. Display regions having mean intensity between X and Y." << endl << "E. Display the K regions closest to (X,Y)." << endl << "F. Quit to main menu and display labeled image" << endl << endl << "Choice: ";
				
				cin >> searchChoice;
				
				if (( searchChoice != 'A' )&&( searchChoice != 'B' )&&( searchChoice != 'C' )&&( searchChoice != 'D' )&&( searchChoice != 'E' ))
					break;
				
				delete image;
				(*image3).getImageInfo( N, M, Q );
				image = new ImageType( N, M, Q );
				
				
				cout << endl << endl << "Please enter the values for X and Y";
				if (( searchChoice == 'A' )&&( searchChoice == 'B' )&&( searchChoice == 'C' )&&( searchChoice == 'D' ))
				 cout << ", X being less than Y."; 
				cout << endl << "X: ";
				cin >> A;
				cout << endl << "Y: ";
				cin >> B;
				ListOfRegions.ResetList();
				
				//Find and display sizes between A and B
				
				if ( searchChoice == 'A' )
				{
					ListOfRegions.GetNextItem( region );
					
					while ( (region.size < A) && !ListOfRegions.IsLastItem() )
					{
						ListOfRegions.GetNextItem( region );
					}
						
					
					while ( (region.size <= B) && !ListOfRegions.IsLastItem() ) 
					{
						pixelList = region.coordList;
						pixelList.ResetList();
						length = pixelList.LengthIs();
						
						while ( length > 0 )
						{
							pixelList.GetNextItem(pixel);
							i = pixel.x;
							j = pixel.y;
							(*image3).getPixelVal( i, j, val );
							(*image).setPixelVal( i, j, val );
							length--;
						}
						
						ListOfRegions.GetNextItem( region );
						
					}
					
					if ( (region.size <= B) )
					{
						pixelList = region.coordList;
						pixelList.ResetList();
						length = pixelList.LengthIs();
						
						while ( length > 0 )
						{
							pixelList.GetNextItem(pixel);
							i = pixel.x;
							j = pixel.y;
							(*image3).getPixelVal( i, j, val );
							(*image).setPixelVal( i, j, val );
							length--;
						}
					}
					
				}
				
				//Find and display orientations between A and B
				if ( searchChoice == 'B' )
				{	
					while ( !ListOfRegions.IsLastItem() ) 
					{
						ListOfRegions.GetNextItem( region );
						
						if ( ( region.orientation >= A ) && ( region.orientation <= B ) )
						{
							pixelList = region.coordList;
							pixelList.ResetList();
							length = pixelList.LengthIs();
							
							while ( length > 0 )
							{
								pixelList.GetNextItem(pixel);
								i = pixel.x;
								j = pixel.y;
								(*image3).getPixelVal( i, j, val );
								(*image).setPixelVal( i, j, val );
								length--;
							}
						}
					}
				}
				
				//Find and display eccentricities between A and B
				if ( searchChoice == 'C' )
				{	
					while ( !ListOfRegions.IsLastItem() ) 
					{
						ListOfRegions.GetNextItem( region );
						
						if ( ( region.eccentricity >= A ) && ( region.eccentricity <= B ) )
						{
							pixelList = region.coordList;
							pixelList.ResetList();
							length = pixelList.LengthIs();
							
							while ( length > 0 )
							{
								pixelList.GetNextItem(pixel);
								i = pixel.x;
								j = pixel.y;
								(*image3).getPixelVal( i, j, val );
								(*image).setPixelVal( i, j, val );
								length--;
							}
						}
					}
				}
				
				
				//Find and display mean intensities between A and B
				if ( searchChoice == 'D' )
				{	
					while ( !ListOfRegions.IsLastItem() ) 
					{
						ListOfRegions.GetNextItem( region );

						if ( ( region.mean >= A ) && ( region.mean <= B ) )
						{
							pixelList = region.coordList;
							pixelList.ResetList();
							length = pixelList.LengthIs();
							
							while ( length > 0 )
							{
								pixelList.GetNextItem(pixel);
								i = pixel.x;
								j = pixel.y;
								(*image3).getPixelVal( i, j, val );
								(*image).setPixelVal( i, j, val );
								length--;
							}
						}
					}
				}
					
				if ( searchChoice == 'E' )
					{	
						coord query;
						coord closest;
						query.x = B;
						query.y = A;
						cout << endl << "Please enter the number, K, of neighbors you would like to find: ";
						cin >> K;
						
						
						
						QuadTree newTree( ListOfRegions );
						cout << endl << "An X has been placed at the query point in the new image.";
						cout << endl << "The centroids of the " << K << " nearest neighbors are at";
						for( int index = 0; index < K; index++ )
						{
							
						newTree.FindClosest( query, closest );
						cout << endl << "(" << closest.y << "," << closest.x << ")";
						ListOfRegions.ResetList();
						
						while ( !ListOfRegions.IsLastItem() ) 
						{
							ListOfRegions.GetNextItem( region );
							//Place the closest galaxy in the new image
							if ( ((region.centroid).x == closest.x ) && ((region.centroid).y == closest.y))
							{
								pixelList = region.coordList;
								pixelList.ResetList();
								length = pixelList.LengthIs();
								
								while ( length > 0 )
								{
									pixelList.GetNextItem(pixel);
									i = pixel.x;
									j = pixel.y;
									(*image3).getPixelVal( i, j, val );
									(*image).setPixelVal( i, j, val );
									length--;
								}
							}
						}
						}
						//Output an X on the query point
						(*image).setPixelVal( query.x, query.y, 255 );
						(*image).setPixelVal( query.x + 1, query.y + 1, 255 );
						(*image).setPixelVal( query.x - 1, query.y + 1, 255 );
						(*image).setPixelVal( query.x - 1, query.y - 1, 255 );
						(*image).setPixelVal( query.x + 1, query.y - 1, 255 );
						(*image).setPixelVal( query.x + 2, query.y + 2, 255 );
						(*image).setPixelVal( query.x - 2, query.y + 2, 255 );
						(*image).setPixelVal( query.x - 2, query.y - 2, 255 );
						(*image).setPixelVal( query.x + 2, query.y - 2, 255 );
						
					}
				
				
				break;
				
				
			case 'N':
				
				//Quit the program
				
				continueProgram = false;
				delete image;
				break;
		}		
	}		
	
	return (1);
}

// Supporting function implementation


int computeComponents(ImageType& inputImage, ImageType& outputImage, ImageType& image3, bool useBFS, SortedList& ListOfRegions)
{
	int N, M, Q;
	int inputPixelVal, outputPixelVal;
	int length;
	int gray;
	
	int size;
	coord centroid;
	double orientation;
	double eccentricity;
	double mean;
	double median;
	int min;
	int max;
	point pixel;
	
	double lamMin;
	double lamMax;
	double placeHolder;
	
	int connComp, label;
	nodeData region;
	coordQ queueCoords;
	coordS stackCoords;
	
	//Create the queue and stack for searches
	
	Queue queue( N*M );
	Stack stack( N*M );
	
	outputImage = inputImage;
	inputImage.getImageInfo( N, M, Q );
	
	//Clear the list of regions
	  ListOfRegions.MakeEmpty();
	
	//Set the output image to white
	
	for ( int i = 0; i < N; i++ )
	{
		for ( int j = 0; j < M; j++ )
		{
			outputImage.setPixelVal( i, j, 255 );
		}
	}
	
	connComp=0; //Initializes region count to 0
	
	// Iterate through original image and find unlabeled pixels
	
	for (int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++) 
		{
			inputImage.getPixelVal( i, j, inputPixelVal );
			outputImage.getPixelVal( i, j, outputPixelVal );
			
			//If the pixel is white in original and unlabeled in output, define its region
			
			if( inputPixelVal == 255 && outputPixelVal == 255) 
			{
				++connComp;
				label += 7; // label
				
				// IF the label goes above viewable shades, reset it to 0
				if ( label >= 250 )
				{
					label = 0;
					
				}
				
				//Test the useBFS flag and use appropriate recursive search to label region
				
				if ( useBFS )
				{
					(region.coordList).MakeEmpty();
					mean = 0;
					min = 255;
					max = 0;
					queueCoords.i = i;
					queueCoords.j = j;
					queue.enqueue( queueCoords );
					pixel.x = i;
					pixel.y = j;
					(region.coordList).InsertItem(pixel);
					findComponentBFS(inputImage, outputImage, label, queue, region);
					
					//Get the size and centroid coords of the region
					
					size = computeMoment( 0, 0, 0, 0, region.coordList );
					centroid.x = computeMoment( 1, 0, 0, 0, region.coordList ) / size;
					centroid.y = computeMoment( 0, 1, 0, 0, region.coordList ) / size;
					
					//Get the lambda min and lambda max of the region
					lamMin = 0.5*(computeMoment( 2, 0, centroid.x, centroid.y, region.coordList ) + computeMoment( 2, 0, centroid.x, centroid.y, region.coordList ) );
					placeHolder = pow( computeMoment( 2, 0, centroid.x, centroid.y, region.coordList ) , 2) + pow( computeMoment( 0, 2, centroid.x, centroid.y, region.coordList ) , 2);
					placeHolder = placeHolder - 2*( computeMoment( 2, 0, centroid.x, centroid.y, region.coordList ) * computeMoment( 0, 2, centroid.x, centroid.y, region.coordList ) );
					placeHolder = placeHolder + 4*pow(computeMoment( 1, 1, centroid.x, centroid.y, region.coordList ), 2 );
					placeHolder = pow( placeHolder, 0.5 );
					lamMin = lamMin - 0.5*(placeHolder);
					
					lamMax = 0.5*(computeMoment( 2, 0, centroid.x, centroid.y, region.coordList ) + computeMoment( 2, 0, centroid.x, centroid.y, region.coordList ) );
					lamMax = lamMax + 0.5*(placeHolder);
					
					// Get the orientation and eccentricity of the region
					placeHolder = lamMax - computeMoment( 2, 0, centroid.x, centroid.y, region.coordList );
					placeHolder = placeHolder / computeMoment( 1, 1, centroid.x, centroid.y, region.coordList );
					orientation = atan( placeHolder );
					
					placeHolder = lamMax/lamMin;
					eccentricity = pow( placeHolder, 0.5 );
					
					// Get the mean intensity, min, and max
					length = (region.coordList).LengthIs();
					(region.coordList).ResetList();
					
					
					while ( length > 0 )
					{
						(region.coordList).GetNextItem( pixel );
						image3.getPixelVal( pixel.x, pixel.y, gray );
						if ( gray < min )
						{
							min = gray;
						}
						if ( gray > max )
						{
							max = gray;
						}
						mean+= gray;
						length--;
					}
					
					mean = mean/size;
					
					//Set these values to the region and add it to the list
					region.size = size;
					region.centroid = centroid;
					region.orientation = orientation;
					region.eccentricity = eccentricity;
					region.mean = mean;
					region.median = median;
					region.min = min;
					region.max = max;
					
					ListOfRegions.InsertItem( region );
					
					
				}
				
				else 
				{
					stackCoords.i = i;
					stackCoords.j = j;
					stack.push( stackCoords );
					findComponentDFS(inputImage, outputImage, label, stack);
				}
				


			}
		}
	}
	
	//Returns the number of regions
	
	return connComp;
	
	
	
}


void findComponentBFS(ImageType& inputImage, ImageType& outputImage, int label, Queue& queue, nodeData& region)
{
	coordQ Qcoords, newCoords;
	int N, M, Q;
	point pixel;
	int val = 0, valtl = 0, valbl = 0, vall = 0, valt = 0, valb = 0, valr = 0, valtr = 0, valbr = 0;
	int out, outtl, outbl, outl, outt, outb, outr, outtr, outbr;
	
	//Test that queue is not empty
	
	if (!queue.empty()) 
	{
		//Dequeue the next pixel to be labeled
		Qcoords = queue.dequeue();
		outputImage.getImageInfo( N, M, Q );
		outputImage.setPixelVal( Qcoords.i, Qcoords.j, label ); // label this pixel
		
				//Check that you will not be reaching outside of the image and obtain all surrounding pixel vals
		
				if ( Qcoords.i-1 >= 0 )
				{
					if ( Qcoords.j-1 >= 0 )
					{
					outputImage.getPixelVal(Qcoords.i-1, Qcoords.j-1, outtl);
					inputImage.getPixelVal(Qcoords.i-1, Qcoords.j-1, valtl);
					}
					if ( Qcoords.j+1 < M )
					{
					inputImage.getPixelVal(Qcoords.i-1, Qcoords.j+1, valbl);
					outputImage.getPixelVal(Qcoords.i-1, Qcoords.j+1, outbl);
					}
					outputImage.getPixelVal(Qcoords.i-1, Qcoords.j, outl);
					inputImage.getPixelVal(Qcoords.i-1, Qcoords.j, vall);
					
				}
				
		
				if ( Qcoords.i+1 < N )
				{
					if ( Qcoords.j-1 >= 0 )
					{
						inputImage.getPixelVal(Qcoords.i+1, Qcoords.j-1, valtr);
						outputImage.getPixelVal(Qcoords.i+1, Qcoords.j-1, outtr);

						
					}
					
					if ( Qcoords.j+1 < M )
					{
						inputImage.getPixelVal(Qcoords.i+1, Qcoords.j+1, valbr);
						outputImage.getPixelVal(Qcoords.i+1, Qcoords.j+1, outbr);
					}
					
					inputImage.getPixelVal(Qcoords.i+1, Qcoords.j, valr);
					outputImage.getPixelVal(Qcoords.i+1, Qcoords.j, outr);
				}
		
			if ( Qcoords.j-1 >= 0 )
			{
				inputImage.getPixelVal(Qcoords.i, Qcoords.j-1, valt);
				outputImage.getPixelVal(Qcoords.i, Qcoords.j-1, outt);
				
			}
		
			if ( Qcoords.j+1 < M )
			{
				outputImage.getPixelVal(Qcoords.i, Qcoords.j+1, outb);
				inputImage.getPixelVal(Qcoords.i, Qcoords.j+1, valb);
			}
				
		//Test each surrounding pixel val. If it is 255, then label that pixel and enqueue it.Also add it to the region in the list		

		if ( valtl == 255 && outtl == 255 )
		{
			newCoords.i = Qcoords.i - 1;
			newCoords.j = Qcoords.j - 1;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( vall == 255 && outl == 255 )
		{
			newCoords.i = Qcoords.i - 1;
			newCoords.j = Qcoords.j;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valbl == 255 && outbl == 255 )
		{
			newCoords.i = Qcoords.i - 1;
			newCoords.j = Qcoords.j + 1;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valt == 255 && outt == 255 )
		{
			newCoords.i = Qcoords.i;
			newCoords.j = Qcoords.j - 1;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valb == 255 && outb == 255 )
		{
			newCoords.i = Qcoords.i ;
			newCoords.j = Qcoords.j + 1;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valtr == 255 && outtr == 255 )
		{
			newCoords.i = Qcoords.i + 1;
			newCoords.j = Qcoords.j - 1;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valr == 255 && outr == 255 )
		{
			newCoords.i = Qcoords.i + 1;
			newCoords.j = Qcoords.j;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valbr == 255 && outbr == 255 )
		{
			newCoords.i = Qcoords.i + 1;
			newCoords.j = Qcoords.j + 1;
			queue.enqueue( newCoords );
			
			pixel.x = newCoords.i;
			pixel.y = newCoords.j;
			(region.coordList).InsertItem(pixel);
			
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
				
				
		//Function calls itself recursively to determine next pixel in region
				
		findComponentBFS(inputImage, outputImage, label, queue, region);			
				
		
		
	
	}
	
	

}




void findComponentDFS(ImageType& inputImage, ImageType& outputImage, int label, Stack& stack)
{
	coordS Qcoords, newCoords;
	int N, M, Q;
	int val, valtl, valbl, vall, valt, valb, valr, valtr, valbr;
	int out, outtl, outbl, outl, outt, outb, outr, outtr, outbr;
	
	//Test that stack is not empty
	
	if (!stack.empty()) 
	{
		//Pop the next pixel to be labeled
		
		Qcoords = stack.pop();
		
		outputImage.getImageInfo( N, M, Q );
		
		outputImage.setPixelVal( Qcoords.i, Qcoords.j, label ); // label this pixel
		
		//Check that you will not be reaching outside of the image and obtain all surrounding pixel vals
		
		if ( Qcoords.i-1 >= 0 )
		{
			if ( Qcoords.j-1 >= 0 )
			{
				outputImage.getPixelVal(Qcoords.i-1, Qcoords.j-1, outtl);
				inputImage.getPixelVal(Qcoords.i-1, Qcoords.j-1, valtl);
			}
			if ( Qcoords.j+1 < M )
			{
				inputImage.getPixelVal(Qcoords.i-1, Qcoords.j+1, valbl);
				outputImage.getPixelVal(Qcoords.i-1, Qcoords.j+1, outbl);
			}
			outputImage.getPixelVal(Qcoords.i-1, Qcoords.j, outl);
			inputImage.getPixelVal(Qcoords.i-1, Qcoords.j, vall);
			
		}
		
		
		if ( Qcoords.i+1 < N )
		{
			if ( Qcoords.j-1 >= 0 )
			{
				inputImage.getPixelVal(Qcoords.i+1, Qcoords.j-1, valtr);
				outputImage.getPixelVal(Qcoords.i+1, Qcoords.j-1, outtr);
				
				
			}
			
			if ( Qcoords.j+1 < M )
			{
				inputImage.getPixelVal(Qcoords.i+1, Qcoords.j+1, valbr);
				outputImage.getPixelVal(Qcoords.i+1, Qcoords.j+1, outbr);
			}
			
			inputImage.getPixelVal(Qcoords.i+1, Qcoords.j, valr);
			outputImage.getPixelVal(Qcoords.i+1, Qcoords.j, outr);
		}
		
		if ( Qcoords.j-1 >= 0 )
		{
			inputImage.getPixelVal(Qcoords.i, Qcoords.j-1, valt);
			outputImage.getPixelVal(Qcoords.i, Qcoords.j-1, outt);
			
		}
		
		if ( Qcoords.j+1 < M )
		{
			outputImage.getPixelVal(Qcoords.i, Qcoords.j+1, outb);
			inputImage.getPixelVal(Qcoords.i, Qcoords.j+1, valb);
		}
		
		//Test each surrounding pixel val. If it is 255, then label that pixel and push it on to the stack.	
		
		if ( valtl == 255 && outtl == 255 )
		{
			newCoords.i = Qcoords.i - 1;
			newCoords.j = Qcoords.j - 1;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( vall == 255 && outl == 255 )
		{
			newCoords.i = Qcoords.i - 1;
			newCoords.j = Qcoords.j;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valbl == 255 && outbl == 255 )
		{
			newCoords.i = Qcoords.i - 1;
			newCoords.j = Qcoords.j + 1;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valt == 255 && outt == 255 )
		{
			newCoords.i = Qcoords.i;
			newCoords.j = Qcoords.j - 1;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valb == 255 && outb == 255 )
		{
			newCoords.i = Qcoords.i ;
			newCoords.j = Qcoords.j + 1;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valtr == 255 && outtr == 255 )
		{
			newCoords.i = Qcoords.i + 1;
			newCoords.j = Qcoords.j - 1;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valr == 255 && outr == 255 )
		{
			newCoords.i = Qcoords.i + 1;
			newCoords.j = Qcoords.j;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		if ( valbr == 255 && outbr == 255 )
		{
			newCoords.i = Qcoords.i + 1;
			newCoords.j = Qcoords.j + 1;
			stack.push( newCoords );
			outputImage.setPixelVal( newCoords.i, newCoords.j, label );				
		}
		
		
		
		//Function calls itself recursively to determine next pixel in region
		findComponentDFS(inputImage, outputImage, label, stack);			
		
		
		
		
	}
	
	
	
}

void deleteSmallComponents(SortedList& listOfRegions, int threshold)
{
	nodeData region;
	listOfRegions.ResetList();
	
	listOfRegions.GetNextItem( region );
	
	while ( (region.size < threshold) && !listOfRegions.IsLastItem() )
	{
		listOfRegions.DeleteItem( region );
		if( !listOfRegions.IsLastItem())
		listOfRegions.GetNextItem( region );
	}
	
	
	
	
}




double computeMoment( int p, int q, double xCenter, double yCenter, UnsortedList& list )
{
	double product;
	double x, y;
	double sum = 0;
	point coords;
	int length;
	
	length = list.LengthIs();
	list.ResetList();
	
	while ( length > 0 )
	{
		list.GetNextItem( coords );
		x = coords.x;
		y = coords.y;
		product = pow( x- xCenter, p )* pow( y - yCenter, q );
		sum+= product;
		length--;
	}
	
	return sum;
	
	
	
	
}

















