#include "CADController.h"
#include <mutex>
CADController* CADController::instance = nullptr;
CADController* CADController::getInstance()
{
	std::mutex mutex;
	mutex.lock();
	if (instance == nullptr)
		instance = new CADController();
		mutex.unlock();
		return instance;
}

string CADController::getPartName()
{
	return string();
}

string CADController::getPaperSN()
{
	return string();
}

string CADController::getPartSN()
{
	return string();
}

string CADController::getCustomerVersion()
{
	return string();
}

string CADController::getPaperVersion()
{
	return string();
}

string CADController::getVersion()
{
	return string();
}

string CADController::getProjectName()
{
	return string();
}

string CADController::getMaterial()
{
	return string();
}

string CADController::getPolishVersion()
{
	return string();
}

//bool CADController::initRead(const char* fileName)
//{
//	Dwg_Data dwg;
//	memset(&dwg, 0, sizeof(Dwg_Data));
//	int error = dwg_read_file(fileName, &dwg);
//	if (error >= DWG_ERR_CRITICAL) {
//		//std::cerr << "Error reading DWG file: " << filename << std::endl;
//		return false;
//	}
//	return true;
//}

CADController::~CADController()
{
}
CADController::CADController()
{
}