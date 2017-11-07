#ifndef Feature_h__
#define Feature_h__

#include "opencv2/opencv.hpp"

namespace Feature
{
    std::vector<float> GetHogDescriptor8316(const cv::Mat& img);
    std::vector<float> GetHogDescriptor1764(const cv::Mat& img);
    std::vector<float> GetHogDescriptor_64x128_324(const cv::Mat& img);
    std::vector<float> GetHogDescriptor_64x128_144(const cv::Mat& img);
    std::vector<float> GetHogDescriptor_32x64_324(const cv::Mat& img);
    std::vector<float> GetHogDescriptor_32x64_144(const cv::Mat& img);
}


#endif // Feature_h__