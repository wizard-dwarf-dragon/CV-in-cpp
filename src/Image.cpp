#include "Image.hpp"
#define CVUINT CV_8UC1
#define CVDOUBLE CV_64FC1
#include <cmath>
#include <algorithm>
Image::Image()
{
}

Image::Image(const char* filename)
{
    load(filename);
}
Image::Image(const cv::Mat& sData){
	data = sData.clone();
}
Image::Image(int height, int width){
    data = cv::Mat::zeros(height, width, CVUINT);
}
bool Image::load(const char* filename)
{
    data = cv::imread(filename, cv::IMREAD_GRAYSCALE);

    return !data.empty();
}

void Image::display(const char* window_name) const
{
    cv::imshow(window_name, data);
    cv::waitKey(0);
}
uchar Image::getValue(int i, int j) const
{
    return mat().at<uchar>(i,j);
}
void Image::setValue(int i, int j,int  s){
    mat().at<uchar>(i,j) = s;
}
int Image::width() const
{
    return data.cols;
}

int Image::height() const
{
    return data.rows;
}
cv::Mat Image::genShiftToCenter(int height, int width){
   cv::Mat outData = cv::Mat::zeros(3, 3, CVDOUBLE);
   outData.at<double>(0,0) = 1;
   outData.at<double>(1,1) = 1;
   outData.at<double>(2,2) = 1;
   outData.at<double>(0,2) = -height/2;
   outData.at<double>(1,2) = -width/2;
   return outData;
}

cv::Mat Image::genRotationMat(float rads){
	cv::Mat outData = cv::Mat::zeros(3, 3, CVDOUBLE);
   outData.at<double>(0,0) = cos(rads);
   outData.at<double>(0,1) = -sin(rads);
   outData.at<double>(1,0) = sin(rads);
   outData.at<double>(1,1) = cos(rads);
   outData.at<double>(2,2) = 1;
   return outData;
}
cv::Mat Image::genShiftFromCenter(int height, int width){
	cv::Mat outData = cv::Mat::zeros(3, 3, CVDOUBLE);
   outData.at<double>(0,0) = 1;
   outData.at<double>(1,1) = 1;
   outData.at<double>(2,2) = 1;
   outData.at<double>(0,2) = height/2;
   outData.at<double>(1,2) = width/2;
   return outData;
}
void Image::toNegative(){
	for (int i = 0; i < height(); i++)
		for(int j = 0; j < width(); j++)
			data.at<uint>(i,j) = data.at<uint>(i,j) ^ 255;
}
void getNewDim(int& height, int& width, float rads){
int w1 = ( (width * std::cos(rads) - height * std::sin(rads))/2.0);
int h1 =  ( ( width * std::sin(rads) + height * std::cos(rads))/2.0);

int w2 =  ( (width * std::cos(rads) + height * std::sin(rads))/2.0);
int h2 =  (   (width * std::sin(rads) - height * std::cos(rads))/2.0);

int w3 = ((-width * std::cos(rads) + height * std::sin(rads))/2.0);
int h3 = ( (-width * std::sin(rads) - height * std::cos(rads))/2.0);

int w4 = ((-width * std::cos(rads) - height * std::sin(rads))/2.0);
int h4 = ( (-width * std::sin(rads) + height * std::cos(rads))/2.0);

int newHeight =std::ceil( 2.0*std::max({h1,h2,h3,h4}));
int newWidth = std::ceil(2.0*std::max({w1,w2,w3,w4}));
height = newHeight;
width = newWidth;
}
Image Image::rotate(float rads){
	int newHeight = height();
	int newWidth = width();
	getNewDim(newHeight, newWidth, rads);
	printf("\n HERE: %d, %d \n   \n", newHeight, newWidth);
	Image outImage = Image(newHeight, newWidth);
	cv::Mat A = genShiftFromCenter(width(), height()) * genRotationMat(-rads) * genShiftToCenter(outImage.width(), outImage.height());
    	for(int i = 0; i < outImage.height(); i++)
		for(int j = 0; j < outImage.width(); j++)
		{
			cv::Mat coordVec = (cv::Mat_<double>(3, 1) << j, i, 1);
			coordVec = A*coordVec;
			int x = cvRound(coordVec.at<double>(0,0));
			int y = cvRound(coordVec.at<double>(1,0));
			if (y >= 0 && y < height() && x >= 0 && x < width()){
				uint value = data.at<uchar>(y,x); 
				outImage.data.at<uchar>(i,j) = value;
			}

		}
	return outImage;	
}

cv::Mat& Image::mat()
{
    return data;
}

const cv::Mat& Image::mat() const
{
    return data;
}
