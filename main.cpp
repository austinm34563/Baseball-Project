#include "startupscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartupScreen w;
    w.show();

    return a.exec();
}
