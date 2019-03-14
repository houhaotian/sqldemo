#include "QSqlDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDemo w;
    w.show();
    return a.exec();
}
