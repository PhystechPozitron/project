#include "widgetcontrol.h"
#include "ui_widgetcontrol.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

const int sizeControlX = 200;
const int sizeControlY = 200;

//* описание методов класса WidgetControl *//

WidgetControl::WidgetControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetControl)
{
    ui->setupUi(this);
    this->setFixedSize(sizeControlX,sizeControlY);
    createFormInterior();
}

void WidgetControl::createFormInterior()
{
    QGridLayout * grid = new QGridLayout(this);

    {
        QLabel* plb = new QLabel("Test", this);
        grid->addWidget(plb, 0, 0);
    }

    {
        QLineEdit * ple = new QLineEdit(this);
        grid->addWidget(ple, 1, 1);
    }

    {
        QPushButton * ppb = new QPushButton("Ok", this);
        grid->addWidget(ppb, 2, 2);
    }

}

WidgetControl::~WidgetControl()
{
    delete ui;
}
