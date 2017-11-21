#ifndef FeatureScaler_h__
#define FeatureScaler_h__

#include <string>
#include <vector>

struct SFeatureInfo
{
    double min;
    double max;
};

struct SScalerParam
{
    double lower;
    double upper;
};

class CFeatureScaler
{

public:
    CFeatureScaler();
    ~CFeatureScaler();

    void LoadScaleAndFeatureInfo(const std::string& sLibSVMScaleFilePath);
    void ScaleFeature(double *feature);

private:
    double Scaler(int &index, double value);

private:
    std::vector<SFeatureInfo> m_FeaturesInfo;
    SScalerParam m_scalerInfo;

};
#endif // FeatureScaler_h__