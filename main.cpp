#include "widgetview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetView view;
    view.show();

    return a.exec();
}
