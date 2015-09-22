#ifndef QARDUINOEXAMPLEWIDGET_H
#define QARDUINOEXAMPLEWIDGET_H

#include <QWidget>
#include "QArduino.h"

namespace Ui {
class QArduinoExampleWidget;
}

class QArduinoExampleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QArduinoExampleWidget(QWidget *parent = 0);
    ~QArduinoExampleWidget();

private:
    Ui::QArduinoExampleWidget *ui;
    QArduino *arduino;
};

#endif // QARDUINOEXAMPLEWIDGET_H
