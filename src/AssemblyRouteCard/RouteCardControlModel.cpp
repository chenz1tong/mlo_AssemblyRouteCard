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
	for (auto val = ValRelation.begin(); val != ValRelation.end();val++) {
		relation.insert(std::make_pair(posRelation[val->first], val->second));
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


