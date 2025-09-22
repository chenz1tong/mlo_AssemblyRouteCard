#include "AssemblyRouteCard.h"
#include "CADController.h"
#include <QFile>
#include <string>
#include <QtWidgets/qfiledialog.h>
#include "FormatHandle.h"
#include "RouteCardControlModel.h"
#include <QtWidgets/qmessagebox.h>
AssemblyRouteCard::AssemblyRouteCard(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    RouteCardControlModel::getInstance();
}

AssemblyRouteCard::~AssemblyRouteCard()
{}

void AssemblyRouteCard::on_run_clicked()
{
}

void AssemblyRouteCard::on_loadScript_clicked()
{
}
void AssemblyRouteCard::on_loadInput_clicked()
{
    QString selectDir = QFileDialog::getOpenFileName();
    if (selectDir.isEmpty())
        return;
    selectDir.replace("/", "\\");
    selectDir.replace("//", "\\");
    ui.InputPath->setText(selectDir);
}
void AssemblyRouteCard::on_LoadOutput_clicked()
{
    QString selectDir = QFileDialog::getOpenFileName();
    if (selectDir.isEmpty())
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
    CADController::getInstance()->initRead(file.c_str());
    CADController::getInstance()->initData();
    bool viewRes=CADController::getInstance()->getView();
    if (!viewRes) {
        m_log = "Get ViewPort Failed! Please check the viewport is exist or not!";
        ui.log->append(QString::fromStdString(FormatHandle::StringToUTF8(m_log)));
        return;
    }
    m_log = "Get CAD data is: \n";
    std::map<string,string> res=CADController::getInstance()->getAllTexts();
    for (auto it = res.begin(); it != res.end(); ++it) {
        string key=it->first;
        string val=it->second;
        m_log + key+":";
        m_log + val+"\n";
    }
    ui.log->append(QString::fromStdString(FormatHandle::StringToUTF8( m_log)));
    RouteCardControlModel::getInstance()->writeTo(ui.OutputPath->text(),res);
}

