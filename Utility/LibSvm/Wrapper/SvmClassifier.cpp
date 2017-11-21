#include "SvmClassifier.h"

CSvmClassifier::CSvmClassifier()
    : m_pSvmModel(NULL)
{
}

CSvmClassifier::~CSvmClassifier()
{

}

void CSvmClassifier::LoadModel(const std::string& sModelPath)
{
    FreeModel();
    m_pSvmModel = svm_load_model(sModelPath.c_str());
}

void CSvmClassifier::FreeModel()
{
    if (m_pSvmModel)
    {
        svm_free_and_destroy_model(&m_pSvmModel);
        m_pSvmModel = NULL;
    }
}

double CSvmClassifier::PredictLabel(const double* pFeature, int dim)
{
    // [TODO]
    return 0;
}

double CSvmClassifier::PredictProbability(const double* pFeature, int dim, std::vector<double> probs)
{
    // [TODO]
    return 0;
}

