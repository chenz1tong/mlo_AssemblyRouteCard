#include <windows.h>
#include "CADControl_global.h"
#include "D:\mlo\cad\libredwg0.13.3.7825\include\dwg_api.h"
#include <D:\mlo\cad\libredwg0.13.3.7825\include\dwg.h>
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
	Dwg_Entity_VIEWPORT** getViewPort();
	Dwg_Entity_MTEXT** getAllText();
	Dwg_Entity_DIMENSION_LINEAR** getAllLNDimension();
	Dwg_Entity_DIMENSION_RADIUS** getAllRadiusDimension();
	static DWGControl* getInstance();
	///BITCODE_3BD getPartNamePos();

private:

	DWGControl();
	~DWGControl();
private:
	static DWGControl* self;
	Dwg_Data dwg;

};

