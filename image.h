#ifndef IMAGE_H
#define IMAGE_H

class ImageType {
 public:
   ImageType();
   ImageType(int, int, int);
	ImageType( ImageType& );
	~ImageType();
	ImageType& operator=( ImageType& );
	
   void getImageInfo(int&, int&, int&);
   void setImageInfo(int, int, int);
   void setPixelVal(int, int, int);
   void getPixelVal(int, int, int&);
	void getSubImage( int, int, int, int, ImageType& );
	int meanGray();
	void enlargeImage( int, ImageType& );
	void shrinkImage( int, ImageType& );
	void reflectImage( bool, ImageType& );
	void translateImage( int, ImageType& );
	void rotateImage( double, ImageType& );
	void thresholdImage( int, ImageType& );
	void dilateImage( ImageType& );
	void erodeImage( ImageType& original );
	ImageType& operator+( ImageType& );
	ImageType& operator-( ImageType& );
	void negateImage();
 private:
   int N, M, Q;
   int **pixelValue;
};

#endif
