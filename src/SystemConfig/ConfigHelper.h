#pragma once

#include <string>
#include <json.hpp>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "SystemConfig_global.h"
using json = nlohmann::ordered_json;//using json = nlohmann::json;

#ifdef SYSTEMCONFIG_EXPORTS
#define CONFIG_API __declspec(dllexport)
#else
#define CONFIG_API __declspec(dllimport)
#endif



class SYSTEMCONFIG_EXPORT ConfigHelper
{
public:
	bool checkJsonFieldValid(const char* name);
	// helper method used inside config file
	bool checkJsonFieldValid(json jsonObj, const char* name);
	bool Load(const char* path);
	bool isDUTaDPA(std::string dutName);
protected:
	json m_JsonControl;
	std::string m_path;
};

