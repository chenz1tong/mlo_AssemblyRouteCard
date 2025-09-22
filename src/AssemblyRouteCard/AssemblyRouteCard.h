
#include <QtWidgets/QWidget>
#include "ui_AssemblyRouteCard.h"

class AssemblyRouteCard : public QWidget
{
    Q_OBJECT

public:
    AssemblyRouteCard(QWidget *parent = nullptr);
    ~AssemblyRouteCard();
public slots:

    void on_loadScript_clicked();
    void on_run_clicked();
    void on_loadInput_clicked();
    void on_LoadOutput_clicked();
    void on_export_2_clicked();

private:
    Ui::AssemblyRouteCardClass ui;
    std::string m_log;
};

