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
    eWriteFileName,
    ePlotHogFeature,
};


namespace MLControl
{
    void WriteHogToLibSvmFromImg(const std::string& sImgpath, const std::string& sSvmDataPath, const std::string& sFilter, int label, EImageProcess type = eOriginal);
    void GenerateTrainingData();
    void GenerateTestingData();
    void GenerateRandomData(double max, int vecSize, int dataCount);

    void IterateImages(const std::string& sImgpath, const std::string& sFilter, EIteratorOperation type = ePlotHogFeature);
    void PlotHogFeature(const std::string& sImgpath, EImageProcess type = eOriginal);
    void CopySVMPredictFalseImage();
    void CopySVMPredictFalseImage(const std::string& srcPath, const std::string& sFilter, const std::string& dstPath, const std::string& sSVMPredictResult, int trueIndex);
}

#endif // MLControl_h__
