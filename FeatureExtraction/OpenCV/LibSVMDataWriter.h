#ifndef LibSVMDataWriter_h__
#define LibSVMDataWriter_h__

#include <fstream>
#include <vector>

class CLibSVMDataWriter
{
public:
    CLibSVMDataWriter();
    ~CLibSVMDataWriter();

    void Open(std::string fileName);
    void Close();

    template<typename T>
    void WriteBack(int label, std::vector<T> feature)
    {
        m_fp << label << " ";

        for (int i = 0; i < feature.size(); ++i)
        {
            m_fp << i + 1 << ":" << feature[i] << " ";
        }

        m_fp << endl;
    }

private:
    std::fstream m_fp;

};
#endif // LibSVMDataWriter_h__
