#include "frontend_class.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Frontend_class w;
    w.show();

    return a.exec();
}
