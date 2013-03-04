#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

#include "image.h"

ImageType::ImageType()	//default constructor
{
 N = 0;
 M = 0;
 Q = 0;

 pixelValue = NULL;
}

ImageType::ImageType(int tmpN, int tmpM, int tmpQ)	//constructor
{
 int i, j;

 N = tmpN;
 M = tmpM;
 Q = tmpQ;

 pixelValue = new int* [N];
 for(i=0; i<N; i++) {
   pixelValue[i] = new int[M];
   for(j=0; j<M; j++)
     pixelValue[i][j] = 0;
 }
}

ImageType::ImageType( ImageType& copied)	//copy constructor
{
	int i, j;
	
	copied.getImageInfo( N, M, Q );
	
	pixelValue = new int* [N];
	for(i=0; i<N; i++) {
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
			copied.getPixelVal( i, j, pixelValue[i][j] );
	}
}

ImageType::~ImageType ()	//destructor
{
	int i;
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
	}
	
	delete[] pixelValue;
}

ImageType& ImageType::operator=( ImageType &copied) //overloaded operator which copies one imageType into another
{
	int i, j;
	
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	copied.getImageInfo( N, M, Q );
	
	pixelValue = new int* [N];
	for(i=0; i<N; i++) {
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
			copied.getPixelVal( i, j, pixelValue[i][j] );
	
	}
}

void ImageType::getImageInfo(int& rows, int& cols, int& levels)	//inputs the imageInfo into the user assigned variables
{
 rows = N;
 cols = M;
 levels = Q;
} 

void ImageType::setImageInfo(int rows, int cols, int levels)	//retrieves the info from the user and places it in the imageInfo
{
 N= rows;
 M= cols;
 Q= levels;
} 

void ImageType::setPixelVal(int i, int j, int val)	//sets the current pixel value
{
 pixelValue[i][j] = val;
}

void ImageType::getPixelVal(int i, int j, int& val)	//returns the current pixel val in a user assigned variable
{
 val = pixelValue[i][j];
}

void ImageType::getSubImage( int nStart, int nEnd, int mStart, int mEnd, ImageType& original )	//crops a rectangular area from the original image
{
	int nSub = nEnd - nStart + 1;
	int mSub = mEnd - mStart + 1;
	int nCurrent = nStart;
	int mCurrent = mStart;
	int i, j;
	int pixelNum;
	
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
	}
	
	delete[] pixelValue;
	
	N = nSub;
	M = mSub;
	
	pixelValue = new int*[N];
	
	for(i=0; i<N; i++) {
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
		{
			original.getPixelVal( nCurrent, mCurrent, pixelNum );
			pixelValue[i][j] = pixelNum;
			mCurrent++;
		}
		mCurrent = mStart;
		nCurrent++;
	}
}

int ImageType::meanGray()	//computes the average gray level value of the original image
{
	int sum = 0;
	int mean;
	int i,j;
	for ( i=0; i<N; i++ )
	{
		for ( j=0; j<M; j++ )
		{
			sum+=pixelValue[i][j];
		}
	}
	
	mean = sum/(N*M);
	
	return mean;
}
	
void ImageType::enlargeImage( int S, ImageType& original )	//enlarges the original image by some integer factor
{
	int nOriginal, mOriginal, qOriginal;
	int nCounter = 0;
	int mCounter = 0;
	int pixelNum;
	int columnS, rowS;
	int i = 0; 
	int j = 0;
	
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	
	original.getImageInfo( nOriginal, mOriginal, qOriginal );
	N = (nOriginal * S);
	M = (mOriginal * S);
	Q = qOriginal;
	
	
	pixelValue = new int*[N];
	
	for(i=0; i<N; i = i) 
	{
		rowS = 0;
		for ( rowS = 0; rowS < S; rowS++ )
		{
			mCounter = 0;
		 pixelValue[i] = new int[M];
		 for(j=0; j<M; j= j)
		 {
			
			 for ( columnS = 0; columnS < S; columnS++)
			{
			 original.getPixelVal( nCounter, mCounter, pixelNum );
			 pixelValue[i][j] = pixelNum;
			 j++;
			 
			}
			mCounter++;
		 }
			i++;
	    }
		nCounter++;		
	}		
}

void ImageType::shrinkImage( int S, ImageType& original )	//shrinks the original image by some integer factor
{
	
	int nOriginal, mOriginal, qOriginal;
	int nCounter = 0;
	int mCounter = 0;
	int pixelNum;
	int columnS, rowS;
	int i = 0; 
	int j = 0;
	
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	original.getImageInfo( nOriginal, mOriginal, qOriginal );
	N = (nOriginal / S);
	M = (mOriginal / S);
	Q = qOriginal;
	
	pixelValue = new int*[N];
	
	for(i=0; i<N; i++) 
	{
			mCounter = 0;
			pixelValue[i] = new int[M];
			for(j=0; j<M; j++)
			{
					original.getPixelVal( nCounter, mCounter, pixelNum );
					pixelValue[i][j] = pixelNum;
				    mCounter+= S;
			}

		nCounter+= S;
	}		
}


void ImageType::reflectImage( bool verticalFlag, ImageType& original)	//reflects the original image along the horizontal or vertical directions
{
	int i ,j ,k;
	int nCounter, mCounter, pixelNum;
	
	for(i=0; i<N; i++) 
	{
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	
	original.getImageInfo( N, M, Q );
	
	
	if ( verticalFlag == true )
	{
		
		pixelValue = new int*[N];
		nCounter = 0;
		
		for(i=0; i<N; i++) 
		{
			mCounter = M-1;
			pixelValue[i] = new int[M];
			for(j=0; j<M; j++)
			{
				original.getPixelVal( nCounter, mCounter, pixelNum );
				pixelValue[i][j] = pixelNum;
				mCounter--;
			}
			
			nCounter++;
		}				
	}

	else
	{
		
		pixelValue = new int*[N];
		nCounter = N-1;
		
		for(i=0; i<N; i++) 
		{
			mCounter = 0;
			pixelValue[i] = new int[M];
			for(j=0; j<M; j++)
			{
				original.getPixelVal( nCounter, mCounter, pixelNum );
				pixelValue[i][j] = pixelNum;
				mCounter++;
			}
			
			nCounter--;
		}		
	}		
}

void ImageType::translateImage( int t, ImageType& original )	//translates the original image by some amount entered by the user
{
	int nCurrent = 0;
	int mCurrent = 0;
	int i, j;
	int pixelNum;
	
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	original.getImageInfo( N, M, Q );
	
	pixelValue = new int*[N];
	
	for(i=0; i<t; i++) 
	{
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
		{
			pixelValue[i][j] = 0;
		}
		
	}
	
	for(i=t; i<N; i++) 
	{
		pixelValue[i] = new int[M];
		for(j=0; j<t; j++)
		{
			pixelValue[i][j] = 0;
		}
		
		for(j=t; j<M; j++)
		{
			original.getPixelVal( nCurrent, mCurrent, pixelNum );
			pixelValue[i][j] = pixelNum;
			mCurrent++;
		}
		mCurrent = 0;
		nCurrent++;
	}	
}


void ImageType::rotateImage(double theta, ImageType& original)	//rotates the original image by some angle entered by the user
{
	int i, j, pixelNum, r, c;
	
	double radians = (theta/180)*3.14159;
	
	for(i=0; i<N; i++) 
	{
		delete[] pixelValue[i];
	}
	
	delete[] pixelValue;
	
	original.getImageInfo( N, M, Q);
	
	pixelValue = new int*[N];
	
	for(i=0; i<N; i++) 
	{
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
		{
			pixelValue[i][j] = 0;
		}
	}
	
	for(i=0; i<N; i++) 
	{
		for(j=0; j<M; j++)
		{
			original.getPixelVal(i, j, pixelNum);
			r = i*cos(radians)-j*sin(radians);
			c = i*sin(radians)+j*cos(radians);
			if ((r >= 0 && r < N) && (c >= 0 && c < M))
			{
				pixelValue[r][c] = pixelNum;
			}
		}
	}
	
	for(i=0; i<N; i++) 
	{
		for(j=0; j<M; j++)
		{
			if ( pixelValue[i][j] == 0 );
			{
				if ( i > 0 && i < N-1 && j > 0 && j < M-1 )
				{
					int average = pixelValue[i-1][j-1] + pixelValue[i][j-1] +
					pixelValue[i+1][j-1] + pixelValue[i-1][j] + pixelValue[i+1][j] + pixelValue[i-1][j+1] + pixelValue[i][j+1] + pixelValue[i+1][j+1]; 
					average = average / 8;
					pixelValue[i][j] = average;
				}
			}
		}
	}	
}

ImageType& ImageType::operator+(ImageType &newImage)	//computes the sum of two images and effectively overlays two images together
{
	int i, j, pixelNum, pixelNum2;
	
	for(i=0; i<N; i++) 
	{
		for(j=0; j<M; j++)
		{
			newImage.getPixelVal(i, j, pixelNum);
			pixelValue[i][j] += pixelNum;
			pixelValue[i][j] /= 2;
		}
	}
}

ImageType& ImageType::operator-(ImageType &newImage)	//computes the difference of two images, effectively finding the difference in the two images and representing that with a third image
{
	int i, j, pixelNum, pixelNum2;
	
	for(i=0; i<N; i++) 
	{
		for(j=0; j<M; j++)
		{
			newImage.getPixelVal(i, j, pixelNum);
			pixelValue[i][j] -= pixelNum;
			pixelValue[i][j] = abs(pixelValue[i][j]);
		}
	}
}

void ImageType::negateImage()	//computes the negative of an image
{
	int i, j;
	
	for(i=0; i<N; i++) 
	{
		for(j=0; j<M; j++)
		{
			pixelValue[i][j] = 255 - pixelValue[i][j];
		}
	}
}


void ImageType::thresholdImage( int T, ImageType& original )
{
	int i, j, val;
	
	
	// Delete old image
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	original.getImageInfo( N, M, Q );
	
	//Create new image of same size
	pixelValue = new int*[N];
	
	for(i=0; i<N; i++) 
	{
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
		{
			pixelValue[i][j] = 0;
		}
		
	}
	
	
	//Iterate through the image. If pixel is greater than thresh, set to white. If not, set to black
	for(i=0; i<N; i++)
		for(j=0; j<M; j++) {
			original.getPixelVal(i, j, val);
			if(val > T) 
				pixelValue[i][j] = 255;
			else
				pixelValue[i][j] = 0;
		}
	
}

void ImageType::dilateImage( ImageType& original )
{
	int type;			//Defines type of pixel
	int i, j;
	int val, valtl, valbl, vall, valt, valb, valr, valtr, valbr;
	
	
	// Delete old image array
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	
	// Create new image array of same size
	original.getImageInfo( N, M, Q );
	
	pixelValue = new int*[N];
	
	for(i=0; i<N; i++) 
	{
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
		{
			pixelValue[i][j] = 0;
		}
		
	}
	
	
	
	
	// Iterate through every pixel
	
	for(i=0; i<N; i++)
		for(j=0; j<M; j++) 
		{
			if ( i == 0 && j == 0 )
			{
				type = 1;			//Type 1 is top left corner pixel
			}
			else if ( i == 0 && j == M-1)
			{
				type = 2;			//Type 2 is bottom left corner pixel
			}
			else if ( i == 0 )
			{
				type = 3;			//Type 3 is left edge pixel
			}
			else if ( i == N-1 && j == 0)
			{
				type = 4;			//Type 4 is top right corner pixel
			}
			else if ( i == N-1 && j == M-1)
			{
				type = 5;			//Type 5 is bottom right corner pixel
			}
			else if ( i == N-1)
			{	
				type = 6;			//Type 6 is right edge pixel
			}
			else if ( j == 0)
			{
				type = 7;			//Type 7 is top edge pixel
			}
			else if ( j == M-1)
			{
				type = 8;			//Type 8 is bottom edge pixel
			}
			else
			{
				type = 9;			//Type 9 is all pixels not on border
			}
			
			
			
			
			// Switch to test each type of pixel seperately for neighboring white pixels
			switch ( type )
			{
				case 1:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( valb == 255 || valr == 255 || valbr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 2:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					
					if (  valt == 255 || valtr == 255 || valr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 3:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( valt == 255 || valb == 255 || valtr == 255 || valr == 255 || valbr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 4:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j+1, valb);
					
					if ( vall == 255 || valbl == 255 || valb == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 5:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i, j-1, valt);
					
					if ( valtl == 255 || vall == 255 ||valt == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 6:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i, j+1, valb);
					
					if ( valtl == 255 || vall == 255 || valbl == 255 || valt == 255 || valb == 255 || valtr == 255 || valr == 255 || valbr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 7:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( vall == 255 || valbl == 255 || valb == 255 ||  valr == 255 || valbr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 8:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					
					if ( valtl == 255 || vall == 255 || valt == 255 || valtr == 255 || valr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
					
				case 9:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( valtl == 255 || vall == 255 || valbl == 255 || valt == 255 || valb == 255 || valtr == 255 || valr == 255 || valbr == 255 )
					{
						pixelValue[i][j] = 255;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
					
			}
			
			
		}
	
	
}


void ImageType::erodeImage( ImageType& original )
{
	int type;			//Defines type of pixel
	int i, j;
	int val, valtl, valbl, vall, valt, valb, valr, valtr, valbr;
	
	
	// Delete old image array
	for(i=0; i<N; i++) {
		delete[] pixelValue[i];
		
	}
	
	delete[] pixelValue;
	
	
	// Create new image array of same size
	original.getImageInfo( N, M, Q );
	
	pixelValue = new int*[N];
	
	for(i=0; i<N; i++) 
	{
		pixelValue[i] = new int[M];
		for(j=0; j<M; j++)
		{
			pixelValue[i][j] = 0;
		}
		
	}
	
	
	
	
	// Iterate through every pixel
	
	for(i=0; i<N; i++)
		for(j=0; j<M; j++) 
		{
			if ( i == 0 && j == 0 )
			{
				type = 1;			//Type 1 is top left corner pixel
			}
			else if ( i == 0 && j == M-1)
			{
				type = 2;			//Type 2 is bottom left corner pixel
			}
			else if ( i == 0 )
			{
				type = 3;			//Type 3 is left edge pixel
			}
			else if ( i == N-1 && j == 0)
			{
				type = 4;			//Type 4 is top right corner pixel
			}
			else if ( i == N-1 && j == M-1)
			{
				type = 5;			//Type 5 is bottom right corner pixel
			}
			else if ( i == N-1)
			{	
				type = 6;			//Type 6 is right edge pixel
			}
			else if ( j == 0)
			{
				type = 7;			//Type 7 is top edge pixel
			}
			else if ( j == M-1)
			{
				type = 8;			//Type 8 is bottom edge pixel
			}
			else
			{
				type = 9;			//Type 9 is all pixels not on border
			}
			
			
			
			
			// Switch to test each type of pixel seperately for neighboring black pixels
			switch ( type )
			{
				case 1:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( valb == 0 || valr == 0 || valbr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 2:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					
					if (  valt == 0 || valtr == 0 || valr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 3:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( valt == 0 || valb == 0 || valtr == 0 || valr == 0 || valbr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 4:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j+1, valb);
					
					if ( vall == 0 || valbl == 0 || valb == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 5:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i, j-1, valt);
					
					if ( valtl == 0 || vall == 0 ||valt == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 6:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i, j+1, valb);
					
					if ( valtl == 0 || vall == 0 || valbl == 0 || valt == 0 || valb == 0 || valtr == 0 || valr == 0 || valbr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 7:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( vall == 0 || valbl == 0 || valb == 0 ||  valr == 0 || valbr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
				case 8:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					
					if ( valtl == 0 || vall == 0 || valt == 0 || valtr == 0 || valr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
					
				case 9:
					original.getPixelVal(i, j, val);
					original.getPixelVal(i-1, j-1, valtl);
					original.getPixelVal(i-1, j, vall);
					original.getPixelVal(i-1, j+1, valbl);
					original.getPixelVal(i, j-1, valt);
					original.getPixelVal(i, j+1, valb);
					original.getPixelVal(i+1, j-1, valtr);
					original.getPixelVal(i+1, j, valr);
					original.getPixelVal(i+1, j+1, valbr);
					
					if ( valtl == 0 || vall == 0 || valbl == 0 || valt == 0 || valb == 0 || valtr == 0 || valr == 0 || valbr == 0 )
					{
						pixelValue[i][j] = 0;
					}
					else
					{
						pixelValue[i][j] = val;
					}
					
					break;
					
					
					
					
					
					
			}
			
			
		}
	
	
	
	
	
	
	
	
}
