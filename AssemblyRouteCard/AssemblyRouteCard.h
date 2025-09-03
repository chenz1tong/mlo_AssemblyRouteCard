#pragma once

#include <QtWidgets/QWidget>
#include "ui_AssemblyRouteCard.h"

class AssemblyRouteCard : public QWidget
{
    Q_OBJECT

public:
    AssemblyRouteCard(QWidget *parent = nullptr);
    ~AssemblyRouteCard();

private:
    Ui::AssemblyRouteCardClass ui;
};

