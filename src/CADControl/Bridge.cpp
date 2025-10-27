#include "Bridge.h"
#include <string>
#include "FormatHandle.h"
#include <gcroot.h>
#include <msclr/marshal_cppstd.h>
using namespace std;
using namespace msclr;
using namespace System;
using namespace msclr::interop;
Bridge* Bridge::instance = nullptr;
bool Bridge::loadDWG(const char* fileName)
{
    //FormatHandle::OutputToDebugWindow("111111111\n");
    //std::string path = (string(fileName));
    //FormatHandle::OutputToDebugWindow(path);
    Read^ m_CDwg = gcnew Read();

    //String^ fname = gcnew String(fileName);
    //FormatHandle::OutputToDebugWindow("2");
    FormatHandle::OutputToDebugWindow("333333");
    m_CDwg->ReadDxf();
    FormatHandle::OutputToDebugWindow("6666666");
    FormatHandle::OutputToDebugWindow("3");

    return true;
}

Bridge* Bridge::getInstance()
{
    FormatHandle::OutputToDebugWindow("instance\n");
    if (instance == nullptr)
        instance = new Bridge();
    FormatHandle::OutputToDebugWindow("bridge\n");
    return instance;
}

Bridge::~Bridge()
{
    
    //delete m_CDwg;
}

Bridge::Bridge()
{
    FormatHandle::OutputToDebugWindow("instance read\n");

}
