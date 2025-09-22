#include "SystemConfigModel.h"
#include <mutex>

SystemConfigModel* SystemConfigModel::self = nullptr;
Result SystemConfigModel::systemConfigLoad()
{
	bool res = DWGPosConfig::instance().Load(CADLocFile.c_str());
	if (!res) {
		return Result(false, "Load config json file failed!");
	}

	DWGPosConfig::instance().getItems();	
	res = DWGToXlsxConfig::instance().Load(XLSXLocFile.c_str());
	if (!res) {
		return Result(false, "Load config json file failed!");
	}
	DWGToXlsxConfig::instance().getItems();
	//DWGPosConfig::instance();
	return Result();

}

std::map<string, string> SystemConfigModel::getCellsPos()
{
	return DWGToXlsxConfig::instance().getCellsPos();
}

DWGPosItems SystemConfigModel::getDWGPos()
{
	return DWGPosConfig::instance().getDWGPos();
}

SystemConfigModel* SystemConfigModel::getInstance()
{
	std::mutex mutex;
	mutex.lock();
	if (self == nullptr) {
		self = new SystemConfigModel();
	}
	mutex.unlock();
	return self;

}
