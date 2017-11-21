#include "FeatureScaler.h"

CFeatureScaler::CFeatureScaler()
{
    m_scalerInfo.lower = -1;
    m_scalerInfo.upper = 1;
}

CFeatureScaler::~CFeatureScaler()
{

}

void CFeatureScaler::LoadScaleAndFeature(const std::string& sLibSVMScaleFilePath)
{
    FILE *fpScaleFile = fopen(sLibSVMScaleFilePath.c_str(), "r");

    if (fpScaleFile && fgetc(fpScaleFile) == 'x')
    {
        if (fscanf(fpScaleFile, "%lf %lf\n", &m_scalerInfo.lower, &m_scalerInfo.upper) != 2)
        {
            printf("ERROR: failed to read scaling parameters\n");
            return;
        }

        int index = 0;
        SFeatureInfo info;

        while (fscanf(fpScaleFile, "%d %lf %lf\n", &index, &info.min, &info.max) == 3)
        {
            m_FeaturesInfo.push_back(info);
        }
    }
}

void CFeatureScaler::ScaleFeature(double *feature)
{
    for (int i = 0; i < m_FeaturesInfo.size(); ++i)
    {
        feature[i] = Scaler(i, feature[i]);
    }
}

double CFeatureScaler::Scaler(int &index, double val)
{
    double ret = val;

    if (m_FeaturesInfo[index].max != m_FeaturesInfo[index].min)
    {
        double factor = (val - m_FeaturesInfo[index].min) / (m_FeaturesInfo[index].max - m_FeaturesInfo[index].min);
        ret = m_scalerInfo.lower + (m_scalerInfo.upper - m_scalerInfo.lower) * factor;
    }

    return ret;
}

