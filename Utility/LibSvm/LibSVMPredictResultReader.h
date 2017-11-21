#ifndef LibSVMPredictResultReader_h__
#define LibSVMPredictResultReader_h__

#include <set>
#include <fstream>

class CLibSVMPredictResultReader
{
public:
    CLibSVMPredictResultReader();
    ~CLibSVMPredictResultReader();

    void Open(std::string filePath);
    void Close();
    std::set<int> GetFalseIndex(int trueIndex);

private:
    std::fstream m_fp;

};
#endif // LibSVMPredictResultReader_h__
