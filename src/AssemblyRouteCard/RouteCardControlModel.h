#pragma once
#include <string>
#include "Result.h"
#include <map>
#include "SystemConfigModel.h"
#include <qstring.h>
using namespace std;
class RouteCardControlModel
{
public:
	static RouteCardControlModel* getInstance();
	void writeTo(QString path, std::map<string, string> res);
	std::map<string, string> getCADposValue(std::map<string, string> posRelation,std::map<string,string> ValRelation);
private:
	RouteCardControlModel();
	~RouteCardControlModel();
private:
	static RouteCardControlModel* self;

};

