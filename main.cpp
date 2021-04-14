#include "vgsa_view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VGSA_View w;
    w.show();
    return a.exec();
}
