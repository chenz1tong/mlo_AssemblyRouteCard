#using "D:\\mlo\\code\\AssemblyRouteCard\\ACAD\\bin\\Debug\\ACAD.dll"
#include <map>
#include "DWGPosConfig.h"
#include <gcroot.h>
using namespace ACAD;
class  Bridge
{
public:
    bool loadDWG(const char* fileName);
    std::map<string, string> getAll();
    //void SetDWGInfo(DWGPosItems info);
    static Bridge* getInstance();
private:

    Bridge();
    ~Bridge();

private:
    static Bridge* instance;
    gcroot < Read^> m_CDwg;
};