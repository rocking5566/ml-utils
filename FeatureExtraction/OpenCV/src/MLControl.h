#ifndef MLControl_h__
#define MLControl_h__

#include <string>

enum EImageProcess
{
    eOriginal,
    eFlip
};

namespace MLControl
{
    void WriteHogToLibSvmFromImg(const std::string& sImgpath, const std::string& sSvmDataPath, const std::string& sFilter, int label, EImageProcess type = eOriginal);
    void GenerateTrainingData();
    void GenerateTestingData();
}

#endif // MLControl_h__
