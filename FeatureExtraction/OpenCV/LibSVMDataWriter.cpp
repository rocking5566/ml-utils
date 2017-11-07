#include "LibSVMDataWriter.h"
using namespace std;

CLibSVMDataWriter::CLibSVMDataWriter()
{

}

CLibSVMDataWriter::~CLibSVMDataWriter()
{
    Close();
}

void CLibSVMDataWriter::Open(std::string fileName)
{
    if (m_fp.is_open())
    {
        Close();
    }

    m_fp.open(fileName, ios::app);
}

void CLibSVMDataWriter::Close()
{
    m_fp.close();
}

