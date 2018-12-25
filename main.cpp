#include "Control.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Control c;
    c.show();

    return a.exec();
}
