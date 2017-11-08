#ifndef MLControl_h__
#define MLControl_h__

#include <string>

enum EImageProcess
{
    eOriginal,
    eFlip
};

enum EIteratorOperation
{
    ePlotHogFeature
};


namespace MLControl
{
    void WriteHogToLibSvmFromImg(const std::string& sImgpath, const std::string& sSvmDataPath, const std::string& sFilter, int label, EImageProcess type = eOriginal);
    void GenerateTrainingData();
    void GenerateTestingData();

    void IterateImages(const std::string& sImgpath, const std::string& sFilter, EIteratorOperation type = ePlotHogFeature);
    void PlotHogFeature(const std::string& sImgpath, EImageProcess type = eOriginal);
}

#endif // MLControl_h__
