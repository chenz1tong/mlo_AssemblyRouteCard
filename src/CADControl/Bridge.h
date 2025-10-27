#include "CADControl_global.h"

//#using "D:\\mlo\\code\\AssemblyRouteCard\\bin\\x64\\Debug\\ACadSharp.dll"
#using "D:\\mlo\\code\\AssemblyRouteCard\\ACAD\\bin\\Debug\\ACAD.dll"


using namespace ACAD;
class  Bridge
{
public:
		bool loadDWG(const char* fileName);
		static Bridge* getInstance();
private:

	Bridge();
	~Bridge();
	
private:
	static Bridge* instance;

};

