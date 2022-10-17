#include "BackpackWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BackpackWindow w;
    w.show();
    return a.exec();
}
