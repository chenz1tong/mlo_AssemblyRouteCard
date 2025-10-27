#pragma once
#include "CADControl_global.h"
#include <windows.h>
#include <string>
#include "DWGControl.h"
#include <map>
using namespace std;
class __declspec(dllexport) CADController
{
public:
	static CADController* getInstance();
	bool initRead(const char* fileName);
	void loadData();
	std::map<string, string> getDimensionLNText();
	std::map<string, string> getDimensionRadiusText();
	std::map<string, string> getTextInNeed();

	void initData();
	string getPartName();
	string getPaperSN();
	string getPartSN();
	string getCustomerVersion();
	string getPaperVersion();
	string getVersion();
	string getProjectName();
	string getMaterial();
	std::map<string, string> getAllTexts();
	string handleDiameter(string str);
	string handleThick(string str);
	bool getView();
private:
	~CADController();
	CADController();
private:
	static CADController* instance;
	DWGPosItems m_standardData;
	string m_partName, m_projectName, m_material, m_dwgSn, m_customVersion, m_dwgVersion, m_objectSn, m_CA, m_R, m_ratio, m_thick, m_CustomerDwgSn,m_diameter;
	int m_CANum = 0;
};

