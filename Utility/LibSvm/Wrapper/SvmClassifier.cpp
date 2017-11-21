#include "SvmClassifier.h"

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(p) { if((p) != NULL) { delete[] (p);   (p)=NULL; } }

CSvmClassifier::CSvmClassifier()
    : m_pSvmModel(NULL)
    , m_plibSVMFeatureCache(NULL)
{
}

CSvmClassifier::~CSvmClassifier()
{
    FreeModel();
}

void CSvmClassifier::LoadModel(const std::string& sModelPath)
{
    FreeModel();
    m_pSvmModel = svm_load_model(sModelPath.c_str());
}

void CSvmClassifier::FreeModel()
{
    svm_free_and_destroy_model(&m_pSvmModel);
    m_pSvmModel = NULL;
    SAFE_DELETE_ARRAY(m_plibSVMFeatureCache);
}

double CSvmClassifier::PredictLabel(const double* pFeature, int dim)
{
    SetFeatureCache(pFeature, dim);
    return svm_predict(m_pSvmModel, m_plibSVMFeatureCache);
}

double CSvmClassifier::PredictProbability(const double* pFeature, int dim, std::vector<double>& probs)
{
    SetFeatureCache(pFeature, dim);
    probs.resize(m_pSvmModel->nr_class);
    return svm_predict_probability(m_pSvmModel, m_plibSVMFeatureCache, probs.data());
}

void CSvmClassifier::SetFeatureCache(const double* pFeature, int dim)
{
    if (m_plibSVMFeatureCache == NULL)
    {
        m_plibSVMFeatureCache = new svm_node[dim + 1];
    }

    for (int i = 0; i < dim; ++i)
    {
        m_plibSVMFeatureCache[i].index = i + 1;
        m_plibSVMFeatureCache[i].value = pFeature[i];
    }

    m_plibSVMFeatureCache[dim].index = -1;
    m_plibSVMFeatureCache[dim].value = 0;
}

