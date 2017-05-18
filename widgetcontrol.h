#ifndef WIDGETCONTROL_H
#define WIDGETCONTROL_H

#include <QWidget>

//* класс WidgetControl окна управления приложения *//

namespace Ui {
class WidgetControl;
}

class WidgetControl : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetControl(QWidget *parent = 0);
    ~WidgetControl();

private:
    void createFormInterior(); // метод для создание интерьера формы
    Ui::WidgetControl *ui;
};

#endif // WIDGETCONTROL_H
