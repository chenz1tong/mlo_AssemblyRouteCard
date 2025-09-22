#pragma once

#include <QObject>
#include "Result.h"
#include <qmap.h>
#include <QtXlsx>
#include <cstdlib>

using namespace std;
class outputCSV  : public QObject
{
	Q_OBJECT

public:
	Result writeToXlsx(const QString& filePath, std::map<string,string>  cellsItems );
	//Result saveImage(QString filePath, QString sn, cv::Mat img, double pos/*, int index*/);

private:
	std::vector<string> getSplitStrings(const char* c, string loc);
	int getColNum(string algh);
	//Result getFileName(const QString& filePath,QString& sn, QString& fileName);
	bool judegeFolderName(QString& fileName);
};
