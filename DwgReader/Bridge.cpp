#include "Bridge.h"
#include <string>
#include "FormatHandle.h"
#include <msclr/marshal_cppstd.h>
#include "CADControl_global.h"

//using namespace System::Collections::Generic::Dictionary;
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

    String^ fname = gcnew String(fileName);
    //m_CDwg->getInfo();
    m_CDwg = gcnew Read();
    FormatHandle::OutputToDebugWindow("read o");

    bool res= m_CDwg->ReadDxf(fname);


    return res;
}
std::map<string, string> Bridge::getAll() {
    std::map<string, string> resMap;
    System::Collections::Generic::Dictionary<String^, String^>^ map1= m_CDwg->getInfo();
    for each(System::Collections::Generic::KeyValuePair<String^, String^>^ pair in map1) {
        std::string key = marshal_as<std::string>(pair->Key);
        //FormatHandle::OutputToDebugWindow("convert C++ key"+key);
        std::string val = /*FormatHandle::StringToUTF8(*/ marshal_as<std::string>(pair->Value);
        //FormatHandle::OutputToDebugWindow("convert C++ val" + val);

        resMap.insert(std::make_pair(key, val));
    }
    string v,customerV;
    if (resMap.find("CA") != resMap.end()) {
        string str = resMap["CA"];
        int index;
        while (str.find("%%C") != std::string::npos) {
            index = str.find("%%C");
            str.replace(index, 3, "\u03A6");
        }
        resMap["CA"] = str;
    }
    if(resMap.find("CustomVersion")!=resMap.end())
        customerV = resMap.at("CustomVersion");
    if (resMap.find("CustomVersion") != resMap.end()) {
        string dwgV = resMap.at("DwgVersion");
        v = customerV + dwgV;
        resMap.insert(std::make_pair("Version", v));

    }

    return resMap;
}
//void Bridge::SetDWGInfo(DWGPosItems info) {A
//
//    m_CDwg
//}
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
    
    delete m_CDwg;
}

Bridge::Bridge()
{
    //m_CDwg = gcnew Read();
    FormatHandle::OutputToDebugWindow("instance read\n");

}
