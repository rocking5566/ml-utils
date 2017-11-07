#include "Feature.h"
#include <iostream>

using namespace std;
using namespace cv;

std::vector<float> Feature::GetHogDescriptor8316(const Mat& img)
{
    Mat imgResize = img;
    if (imgResize.size() != Size(100, 180))
    {
        resize(imgResize, imgResize, Size(100, 180));
    }

    //     dimension per block = 4 * 9 = 36
    //     winndow size = 16 * (100 / 16) = 96, 16 * (180 / 16) = 176
    //     number of block per window = [(96 - 16) / 8 + 1] * [(176 - 16) / 8 + 1] = 11 * 21 = 231
    //     dimension per window = 231 * 36 = 8316
    vector<float> retHogDescriptor;
    int bins = 9;
    Size winSize(16 * (imgResize.cols / 16), 16 * (imgResize.rows / 16));
    Size blockSize = Size(16, 16);
    Size strideSize = Size(8, 8);
    Size cellSize = Size(8, 8);

    static HOGDescriptor *hog = new  HOGDescriptor(winSize, blockSize, strideSize, cellSize, bins);

    hog->compute(imgResize, retHogDescriptor);

    return move(retHogDescriptor);
}

std::vector<float> Feature::GetHogDescriptor1764(const cv::Mat& img)
{
    Mat imgResize = img;
    if (imgResize.size() != Size(64, 128))
    {
        resize(imgResize, imgResize, Size(64, 128));
    }

    //     dimension per block= 4 * 9 = 36
    //     number of block per window = [(64 - 16) / 8 + 1] * [(128 - 32) / 16 + 1] = 7 * 7 = 49
    //     dimension per window = 49 * 36 = 1764
    vector<float> retHogDescriptor;
    int bins = 9;
    Size winSize(64, 128);
    Size blockSize = Size(16, 32);
    Size strideSize = Size(8, 16);
    Size cellSize = Size(8, 16);

    static HOGDescriptor *hog = new  HOGDescriptor(winSize, blockSize, strideSize, cellSize, bins);

    hog->compute(imgResize, retHogDescriptor);

    return move(retHogDescriptor);
}

std::vector<float> Feature::GetHogDescriptor_64x128_324(const cv::Mat& img)
{
    Mat imgResize = img;
    if (imgResize.size() != Size(64, 128))
    {
        resize(imgResize, imgResize, Size(64, 128));
    }

    //     dimension per block= 4 * 9 = 36
    //     number of block per window = [(64 - 32) / 16 + 1] * [(128 - 64) / 32 + 1] = 3 * 3 = 9
    //     dimension per window = 9 * 36 = 324
    vector<float> retHogDescriptor;
    int bins = 9;
    Size winSize(64, 128);
    Size blockSize = Size(32, 64);
    Size strideSize = Size(16, 32);
    Size cellSize = Size(16, 32);

    static HOGDescriptor *hog = new  HOGDescriptor(winSize, blockSize, strideSize, cellSize, bins);

    hog->compute(imgResize, retHogDescriptor);

    return move(retHogDescriptor);
}

std::vector<float> Feature::GetHogDescriptor_64x128_144(const cv::Mat& img)
{
    Mat imgResize = img;
    if (imgResize.size() != Size(64, 128))
    {
        resize(imgResize, imgResize, Size(64, 128));
    }

    //     dimension per block= 4 * 9 = 36
    //     number of block per window = [(64 - 32) / 32 + 1] * [(128 - 64) / 64 + 1] = 2 * 2 = 4
    //     dimension per window = 4 * 36 = 144
    vector<float> retHogDescriptor;
    int bins = 9;
    Size winSize(64, 128);
    Size blockSize = Size(32, 64);
    Size strideSize = Size(32, 64);
    Size cellSize = Size(16, 32);

    static HOGDescriptor *hog = new  HOGDescriptor(winSize, blockSize, strideSize, cellSize, bins);

    hog->compute(imgResize, retHogDescriptor);

    return move(retHogDescriptor);
}

std::vector<float> Feature::GetHogDescriptor_32x64_324(const cv::Mat& img)
{
    Mat imgResize = img;
    if (imgResize.size() != Size(32, 64))
    {
        resize(imgResize, imgResize, Size(32, 64));
    }

    //     dimension per block= 4 * 9 = 36
    //     number of block per window = [(32 - 16) / 8 + 1] * [(64 - 32) / 16 + 1] = 3 * 3 = 9
    //     dimension per window = 9 * 36 = 324
    vector<float> retHogDescriptor;
    int bins = 9;
    Size winSize(32, 64);
    Size blockSize = Size(16, 32);
    Size strideSize = Size(8, 16);
    Size cellSize = Size(8, 16);

    static HOGDescriptor *hog = new  HOGDescriptor(winSize, blockSize, strideSize, cellSize, bins);

    hog->compute(imgResize, retHogDescriptor);

    return move(retHogDescriptor);
}

std::vector<float> Feature::GetHogDescriptor_32x64_144(const cv::Mat& img)
{
    Mat imgResize = img;
    if (imgResize.size() != Size(32, 64))
    {
        resize(imgResize, imgResize, Size(32, 64));
    }

    //     dimension per block= 4 * 9 = 36
    //     number of block per window = [(32 - 16) / 16 + 1] * [(64 - 32) / 32 + 1] = 2 * 2 = 4
    //     dimension per window = 4 * 36 = 144
    vector<float> retHogDescriptor;
    int bins = 9;
    Size winSize(32, 64);
    Size blockSize = Size(16, 32);
    Size strideSize = Size(16, 32);
    Size cellSize = Size(8, 16);

    static HOGDescriptor *hog = new  HOGDescriptor(winSize, blockSize, strideSize, cellSize, bins);

    hog->compute(imgResize, retHogDescriptor);

    return move(retHogDescriptor);
}
