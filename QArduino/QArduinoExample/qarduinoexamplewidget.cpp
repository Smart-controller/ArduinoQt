#include "qarduinoexamplewidget.h"
#include "ui_qarduinoexamplewidget.h"


QArduinoExampleWidget::QArduinoExampleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QArduinoExampleWidget)
{
    ui->setupUi(this);
    arduino = new QArduino("JY MCU");
}

QArduinoExampleWidget::~QArduinoExampleWidget()
{
    delete ui;
}
