#include "ConfigHelper.h"

bool ConfigHelper::checkJsonFieldValid(const char* name)
{
	return m_JsonControl.find(name) != m_JsonControl.end();
}

bool ConfigHelper::checkJsonFieldValid(json jsonObj, const char* name)
{
    return jsonObj.find(name) != jsonObj.end();
}

bool ConfigHelper::Load(const char* path)
{
    m_path = path;
    std::ifstream ifs(path, std::fstream::in);

    if (ifs.fail())
    {
        return false;
    }

    ifs >> m_JsonControl;
    return true;
}

bool ConfigHelper::isDUTaDPA(std::string dutName)
{
    return dutName.rfind("DPA", 0) == 0;
}