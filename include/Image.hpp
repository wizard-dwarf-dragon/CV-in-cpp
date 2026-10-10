#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv2/opencv.hpp>

class Image {
private:
    cv::Mat data;

public:
    Image();
    explicit Image(const char* filename);
    Image(const cv::Mat& sData);
    Image(int height, int width);
    bool load(const char* filename);
    void display(const char* window_name = "Image") const;
    uchar getValue(int i, int j) const;
    void setValue(int i, int j, int s);
    int width() const;
    int height() const;
    void toNegative();
    Image rotate(float rads);
    std::vector<Image> bitSlice();
    Image gammaTransform(double c = 1, double g= 1, double b=0);
    cv::Mat genShiftToCenter(int height, int width);
    cv::Mat genRotationMat(float rads);
    cv::Mat genShiftFromCenter(int height, int width);
    cv::Mat& mat();
    const cv::Mat& mat() const;
};

#endif
