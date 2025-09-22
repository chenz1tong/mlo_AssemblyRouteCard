#include "AssemblyRouteCard.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AssemblyRouteCard window;
    window.show();
    return app.exec();
}
