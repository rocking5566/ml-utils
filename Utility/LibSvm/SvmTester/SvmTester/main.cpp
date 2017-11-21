#include "Wrapper/SvmClassifier.h"
#include <vector>
#include <ctime>

using namespace std;

vector<double> GenerateRandomData(int dim)
{
    static bool bFirstCall = true;
    if (bFirstCall)
    {
        srand(time(NULL));
        bFirstCall = false;
    }

    vector<double> descriptors;
    descriptors.resize(dim);
    for (int j = 0; j < dim; ++j)
    {
        descriptors[j] = double((rand() % 2000)) / 1000 - 1;  // -1 ~ 1
    }

    return move(descriptors);
}

int main()
{
    srand(time(NULL));

    CSvmClassifier svm;
    svm.LoadModel("test.model");

    vector<double> featrue = GenerateRandomData(81);
    vector<double> prob;
    double label = svm.PredictLabel(featrue.data(), featrue.size());
    label = svm.PredictProbability(featrue.data(), featrue.size(), prob);
}