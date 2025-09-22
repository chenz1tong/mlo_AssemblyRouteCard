#ifndef DWGPOSCONFIG_H
#define DWGPOSCONFIG_H
#include "SystemConfig_global.h"
#include <string>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include "ConfigHelper.h"
using json = nlohmann::ordered_json;//using json = nlohmann::json;
using namespace std;
struct SYSTEMCONFIG_EXPORT MarginRelData {
	double left;
	double right;
	double bottom ;
	double top ;
};
typedef SYSTEMCONFIG_EXPORT struct {
	MarginRelData partName;
	MarginRelData projectName;
	MarginRelData dwgSn;
	MarginRelData customVersion;
	MarginRelData dwgVersion;
	MarginRelData objectSn;
	MarginRelData material;
	MarginRelData CA;
	MarginRelData R;
	MarginRelData diameter;
	MarginRelData thick;
	MarginRelData CustomerDwgSn;
}DWGPosItems;
class SYSTEMCONFIG_EXPORT DWGPosConfig: public ConfigHelper
{
private:

	//bool loadFile(const char*);

public:
	DWGPosItems getDWGPos();
	//bool loadFile(const char* path);
	void getItems();

	static DWGPosConfig& instance() {
		static DWGPosConfig config;
		return config;
	}
	~DWGPosConfig();
	DWGPosConfig();
private:
	//const char* fileName = "../config/relativeInfoPosInViewport.json";
	DWGPosItems items;
	//json m_JsonControl;

};
#endif
