#include <windows.h>
#include "CADControl_global.h"
#include "D:\mlo\cad\libredwg0.13.3.7825\include\dwg_api.h"
#include <string>
#include <map>
#include "SystemConfigModel.h"

using namespace std;

class CADCONTROL_EXPORT DWGControl
{
public:
	bool loadDWG(const char* fileName);
	std::string ConvertToUTF8(const std::string& input, UINT codepage);
	std::string CharToUTF8(char* input, UINT codepage);
	std::string GB2312ToUTF8(const char* gb2312Str);
	static DWGControl* getInstance();
	///BITCODE_3BD getPartNamePos();
	std::map<string, string> getCSharpMap();
private:

	DWGControl();
	~DWGControl();
private:
	static DWGControl* self;
	Dwg_Data dwg;
	//std::mutex mutex;

};

