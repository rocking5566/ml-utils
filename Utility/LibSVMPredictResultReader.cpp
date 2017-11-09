#include "LibSVMPredictResultReader.h"
#include <sstream>
#include <string>

using namespace std;

CLibSVMPredictResultReader::CLibSVMPredictResultReader()
{

}

CLibSVMPredictResultReader::~CLibSVMPredictResultReader()
{
    Close();
}

void CLibSVMPredictResultReader::Open(std::string filePath)
{
    if (m_fp.is_open())
    {
        Close();
    }

    m_fp.open(filePath, ios::in);
}

void CLibSVMPredictResultReader::Close()
{
    m_fp.close();
}

std::set<int> CLibSVMPredictResultReader::GetFalseIndex(int trueIndex)
{
    string line;
    std::getline(m_fp, line);

    set<int> setFalsePositive;
    int index = 0;
    int label = 0;
    double p1 = 0;
    double p2 = 0;

    while (m_fp >> label >> p1 >> p2)
    {
        if (label != trueIndex)
        {
            setFalsePositive.insert(index);
        }

        ++index;
    }

    return std::move(setFalsePositive);
}

