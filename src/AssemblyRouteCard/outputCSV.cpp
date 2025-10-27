#include "outputCSV.h"
#include <qdatetime.h>
#include <QtCore/qdir.h>
#include <QtWidgets/qmessagebox.h>
#include <QDebug>

//Result outputCSV::saveDoc(const QString& filePath) {
//    QString fileName;
//    Result ret = getFileName(filePath, fileName);
//    if (!ret.success) {
//        string msg = ret.errorMsg;
//        qWarning() << msg.c_str();
//        return ret;
//    }
//    m_outXlsx.saveAs(fileName);
//}

//Result outputCSV::writeToXlsx(const QString& filePath, std::vector<std::string> posStrs, QMap<int, QMap<float, double>> ctfRes, QMap<int, QMap<double, double>> newCtfs, QMap<int, QMap<double, double>> newCtfs1, QString sn, QImage img) {
//    QString fileName;
//    Result ret = getFileName(filePath,sn, fileName);
//    if (!ret.success) {
//        string msg = ret.errorMsg;
//        qWarning() << msg.c_str();
//        return ret;
//    }
//    QXlsx::Document outXlsx;
//    int rowNum = 2;
//    int rowHeadNum = 0;
//    outXlsx.write(1, 1, "Z-Pos\\ROI");
//    while (rowHeadNum < posStrs.size()) {
//        const char* a = posStrs.at(rowHeadNum).c_str();
//        outXlsx.write(rowNum, 1, posStrs.at(rowHeadNum).c_str()); 
//
//        rowNum++;
//        outXlsx.write(rowNum, 1, posStrs.at(rowHeadNum).c_str());
//        rowNum++;
//        outXlsx.write(rowNum, 1, posStrs.at(rowHeadNum).c_str());
//        rowNum++;
//        rowHeadNum++;
//     }
//    int colNum = 2;
//    QMap<int, QMap<float, double>>::iterator iter;
//    for (iter = ctfRes.begin(); iter != ctfRes.end(); ++iter)
//    {
//        outXlsx.write(1, colNum, to_string(iter.key()).c_str());
//        QMap<float, double> ctfMap = iter.value();
//        rowNum = 0;
//        rowHeadNum = 0;
//        while (rowHeadNum < posStrs.size()) {
//            outXlsx.write(rowNum+2, colNum, to_string(round(ctfMap.value(stof(posStrs.at(rowHeadNum))) * 10000) / 10000.0).c_str());
//            //outXlsx.write(rowNum + 3, colNum, to_string(round(newCtfs.value(stod(posStrs.at(rowNum))) * 10000) / 10000.0).c_str());
//            rowNum+=3;
//            rowHeadNum++;
//        }
//        colNum++;
//    }
//    colNum = 2;
//    
//    for (iter = newCtfs.begin(); iter != newCtfs.end(); ++iter)
//    {
//        //outXlsx.write(1, colNum, to_string(iter.key()).c_str());
//        QMap<double, double> ctfMaps = iter.value();
//        rowNum = 0;
//        rowHeadNum = 0;
//        while (rowHeadNum < posStrs.size()) {
//            outXlsx.write(rowNum + 3, colNum, to_string(round(ctfMaps.value(stod(posStrs.at(rowHeadNum))) * 10000) / 10000.0).c_str());
//            //outXlsx.write(rowNum + 3, colNum, to_string(round(newCtfs.value(stod(posStrs.at(rowNum))) * 10000) / 10000.0).c_str());
//            rowNum += 3;
//            rowHeadNum++;
//        }
//        colNum++;
//        
//    }
//    colNum = 2;
//    for (iter = newCtfs1.begin(); iter != newCtfs1.end(); ++iter)
//    {
//        //outXlsx.write(1, colNum, to_string(iter.key()).c_str());
//        QMap<double, double> ctfMaps1 = iter.value();
//        rowNum = 0;
//        rowHeadNum = 0;
//        while (rowHeadNum < posStrs.size()) {
//            outXlsx.write(rowNum + 4, colNum, to_string(round(ctfMaps1.value(stod(posStrs.at(rowHeadNum))) * 10000) / 10000.0).c_str());
//            //outXlsx.write(rowNum + 3, colNum, to_string(round(newCtfs.value(stod(posStrs.at(rowNum))) * 10000) / 10000.0).c_str());
//            rowNum += 3;
//            rowHeadNum++;
//        }
//        colNum++;
//        
//    }
//    //QString tmpStr;
//    //int rows = img.rows;
//    //int cols = img.cols;
//    //for (int i = 0; i < rows; i++)
//    //{
//    //    for (int j = 0; j < cols; j++)
//    //    {
//    //        uchar v = img.at<uchar>(i, j);
//    //        outXlsx.write(colNum + i, j + 2, QString::number(v));
//    //    }
//    //}
//    bool inImgRet = outXlsx.insertImage(0, 10,img );
//    if (!inImgRet)
//        return Result(false, "Insert Image Failed!");
//    outXlsx.saveAs(fileName);
//    outXlsx.deleteLater();
//    return Result();
//}
Result outputCSV::writeToXlsx(const QString& filePath, std::map<string, string>  cellsItems) {
    
    QXlsx::Document xlsx(filePath);

    if (!xlsx.workbook()) {
        qDebug() << "Failed to load the file.";

        return Result(false, "Failed to load the file.");
    }
    //std::vector<string> keys;
    for (auto item = cellsItems.begin(); item != cellsItems.end(); item++) {
        string loc=item->first;
        std::vector<string> list = getSplitStrings("/", loc);
        //keys.push_back(loc);
        string sheetName = list.at(0);
        bool res = xlsx.selectSheet(QString::fromStdString(sheetName)); 
        QXlsx::Worksheet* sheet =  xlsx.currentWorksheet();
        if (item->second == "") {
            for (int index = 1; index < list.size(); index++) {
                string cellName = list.at(index);
                int col = getColNum(cellName);
                int row = stoi(cellName.substr(1));
                sheet->write(row, col, "");

            }/*
            xlsx.saveAs(filePath);
            xlsx.deleteLater();
            return Result();*/
        }
        else {
            std::vector<string> vals = getSplitStrings(",", item->second.c_str());

            for (int index = 1; index < list.size(); index++) {
                string cellName = list.at(index);
                int col = getColNum(cellName);
                int row = stoi(cellName.substr(1));
                sheet->write( row,col, QString::fromLocal8Bit(vals.at(index-1).c_str()));
            }
        }



    }

    xlsx.saveAs(filePath);
    xlsx.deleteLater();
    return Result();
}
std::vector<string> outputCSV::getSplitStrings(const char* c,string loc) {
    int d=loc.find("/",0);
    std::vector<string> list;
    string str;
    int pos = 0;
    int find = -1;
    while ( (find=loc.find(c, pos)) != std::string::npos) {

                str = loc.substr(pos, find-pos);
                pos = find + 1;
                find = -1;
                list.push_back(str);
    }
    list.push_back(loc.substr(pos));
    return list;
}

int outputCSV::getColNum(string algh)
{
    char a = 'A';
    char param=algh[0];
    return param-a+1;
}

//Result outputCSV::saveImage(QString filePath, QString sn, cv::Mat img,double pos/*,int index*/)
//{
//    QDateTime dateTime = QDateTime::currentDateTime();
//    QString dateStr = dateTime.toString("yyyyMMdd");
//    QString newPath = filePath + "\\" + dateStr + "_" + sn + "_TestResult\\TestImages";
//    if (!judegeFolderName(newPath)) {
//        return Result(false, "The output filepath format false!");
//    }
//    QString fileName = newPath +"\\" /*+ QString::number(index) + "_"*/ + QString::number(pos,'f',3) + "mm.tif";
//    bool p=cv::imwrite(fileName.toStdString(), img);
//    return Result();
//}
bool  outputCSV::judegeFolderName(QString &fileName)
{
    QDir dir(fileName);
    if (fileName == "")
    {
        QMessageBox msgBox;
        msgBox.setText("The output path cannot be empty!");
        msgBox.exec();
        return false;
    }
    else if (!dir.exists())
    {
        fileName.replace("//", "\\");
        //bool res=dir.mkdir(fileName);
       // return res;
        std::string command = "mkdir " + fileName.toStdString();

        int result = system(command.c_str());

        if (result == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else return true;
}
