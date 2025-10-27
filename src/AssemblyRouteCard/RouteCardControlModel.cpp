#include "RouteCardControlModel.h"
#include <mutex>
#include "outputCSV.h"

RouteCardControlModel* RouteCardControlModel::self = nullptr;
RouteCardControlModel* RouteCardControlModel::getInstance()
{
	std::mutex mutex;
	mutex.lock();
	if (self == nullptr) {
		self = new RouteCardControlModel();
	}

	mutex.unlock();
	return self;
}

void RouteCardControlModel::writeTo(QString path, std::map<string, string> res)
{
	std::map<string, string> toPos = SystemConfigModel::getInstance()->getCellsPos();
	std::map<string, string> val = RouteCardControlModel::getInstance()->getCADposValue(toPos, res);
	outputCSV opt;
	opt.writeToXlsx(path, val);
}


std::map<string, string> RouteCardControlModel::getCADposValue(std::map<string, string> posRelation, std::map<string, string> ValRelation)
{
	std::map<string, string> relation;
	for (auto val = posRelation.begin(); val != posRelation.end();val++) {
		if (ValRelation.find(val->first) != ValRelation.end())
			relation.insert(std::make_pair(posRelation[val->first], ValRelation[val->first]));
		else
			relation.insert(std::make_pair(posRelation[val->first], ""));
	}
	return relation;
}

RouteCardControlModel::RouteCardControlModel()
{
	SystemConfigModel::getInstance()->systemConfigLoad();

}

RouteCardControlModel::~RouteCardControlModel()
{
}


