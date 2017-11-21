#ifndef SvmPredict_h__
#define SvmPredict_h__

#include "svm.h"
#include <string>
#include <vector>

enum ESvmKernel
{
    eLinear,
    ePoly,
    eRBF,
    eSigmoid,
    ePrecomputed
};

class CSvmClassifier
{
public:
    CSvmClassifier();
    virtual ~CSvmClassifier();

    void LoadModel(const std::string& sModelPath);
    void FreeModel();

    double PredictLabel(const double* pFeature, int dim); // return label
    double PredictProbability(const double* pFeature, int dim, std::vector<double>& probs); // return label

private:
    void SetFeatureCache(const double* pFeature, int dim);

private:
    svm_model* m_pSvmModel;
    struct svm_node* m_plibSVMFeatureCache;
};
#endif // SvmPredict_h__