#pragma once
#include <string>
using namespace std;
class CADController
{
public:
	static CADController* getInstance();
	string getPartName();
	string getPaperSN();
	string getPartSN();
	string getCustomerVersion();
	string getPaperVersion();
	string getVersion();
	string getProjectName();
	string getMaterial();
	string getPolishVersion();
private:
	//bool initRead(const char* fileName);
	~CADController();
	CADController();
private:
	static CADController* instance;
};

