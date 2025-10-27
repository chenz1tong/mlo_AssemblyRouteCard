#include "AssemblyRouteCard.h"
#include <QFile>
#include <string>
#include <QtWidgets/qfiledialog.h>
//#include "FormatHandle.h"
#include "RouteCardControlModel.h"
#include <QtWidgets/qmessagebox.h>
#include "../../DwgReader/DWGControl.h"
#include "../../DwgReader/FormatHandle.h"
//#include "DWGControl.h"
#include <qdebug.h>
AssemblyRouteCard::AssemblyRouteCard(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    RouteCardControlModel::getInstance();
    initUi();
}

AssemblyRouteCard::~AssemblyRouteCard()
{}

void AssemblyRouteCard::initUi()
{
    ui.groupBox_2->hide();
}

void AssemblyRouteCard::on_run_clicked()
{
    if (pythonScriptPath == "") {
        QMessageBox::warning(this, "Warning!", "Please check the script path!");
        return;
    }
    std::string command = "python " + pythonScriptPath;
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Python script failed to execute" << std::endl;
    }
}

void AssemblyRouteCard::on_loadScript_clicked()
{
    QString selectDir = QFileDialog::getOpenFileName();
    pythonScriptPath = selectDir.toStdString();
    if (selectDir.isEmpty()|| !selectDir.contains(".py"))
        return;
    selectDir.replace("/", "\\");
    selectDir.replace("//", "\\");
    ui.scriptPath->setText(selectDir);
}
void AssemblyRouteCard::on_loadInput_clicked()
{
    QString selectDir = QFileDialog::getOpenFileName();
    if (selectDir.isEmpty() || !selectDir.contains(".dwg"))
        return;
    selectDir.replace("/", "\\");
    selectDir.replace("//", "\\");
    ui.InputPath->setText(selectDir);
}
void AssemblyRouteCard::on_LoadOutput_clicked()
{
    QString selectDir = QFileDialog::getOpenFileName();
    if (selectDir.isEmpty() || !selectDir.contains(".xlsx"))
        return;
    selectDir.replace("/", "\\");
    selectDir.replace("//", "\\");
    ui.OutputPath->setText(selectDir);
}

void AssemblyRouteCard::on_export_2_clicked()
{
    string file = ui.InputPath->text().toStdString();
    string outfile = ui.OutputPath->text().toStdString();
    if (file == "" || outfile == "") {
        QMessageBox::warning(this, "Warning!", "Please check the input&output path!");
        return;

    }
    try {
        bool loadRes=DWGControl::getInstance()->loadDWG(file.c_str());
        qDebug() << "load is "+QString::number(loadRes);
        if (!loadRes) {
            QMessageBox::warning(this, "Warning", "Load dwg failed!");
        }
    }
    catch(exception e){
        QMessageBox::warning(this, "Warning", e.what());
        return;
    }

    m_log = "Get CAD data is: \n";
    std::map<string,string> res= DWGControl::getInstance()->getCSharpMap();
    for (auto it = res.begin(); it != res.end(); ++it) {
        string key=it->first;
        string val=it->second;
        m_log=m_log + key+":";
        m_log=m_log + val+"\n";
    }
    ui.log->append(QString::fromStdString(FormatHandle::StringToUTF8( m_log)));
    RouteCardControlModel::getInstance()->writeTo(ui.OutputPath->text(),res);
}

