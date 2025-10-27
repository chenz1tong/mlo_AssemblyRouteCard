#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H
#include "SystemConfig_global.h"
#include "DWGToXlsxConfig.h"
#include "DWGPosConfig.h"
#include "Result.h"
class SYSTEMCONFIG_EXPORT SystemConfigModel
{
public:	
	  Result systemConfigLoad();
	  std::map<string, string> getCellsPos();
	  DWGPosItems getDWGPos();
	  static SystemConfigModel* getInstance();
private:
	SystemConfigModel() {};
	~SystemConfigModel() {};
	static SystemConfigModel* self;
	string XLSXLocFile = "..\\config\\CADToXlsx.json";
	string CADLocFile = "..\\config\\relativeInfoPosInViewport.json";
};
#endif
