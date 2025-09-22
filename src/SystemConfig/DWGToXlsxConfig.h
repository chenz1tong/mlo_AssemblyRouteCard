#ifndef DWGTOXLSXCONFIG_H
#define DWGTOXLSXCONFIG_H
#include "SystemConfig_global.h"
#include <iostream>
#include <json.hpp>
#include "ConfigHelper.h"
#include <string>
using namespace std;
using json = nlohmann::ordered_json;
typedef SYSTEMCONFIG_EXPORT struct {
	string propertyName;
	string toCell;
}XLSXLocations;
class SYSTEMCONFIG_EXPORT DWGToXlsxConfig :public  ConfigHelper
{
private:

	//bool loadFile(const char*);

public:
	std::map<string, string> getCellsPos();
	void getItems();

	static DWGToXlsxConfig& instance() {
		static DWGToXlsxConfig config;
		return config;
	}
	~DWGToXlsxConfig() {}
	DWGToXlsxConfig() {
		//loadFile(fileName);
		//getItems();
	}
private:
	std::map<string,string>  m_items;
};

#endif

