#ifndef QUICKSIMULATIONSETTINGS_H
#define QUICKSIMULATIONSETTINGS_H

#include "WinDllMacros.h"
#include <QWidget>

class QRadioButton;

class BA_CORE_API_ QuickSimulationSettings : public QWidget
{
    Q_OBJECT

public:
    QuickSimulationSettings(QWidget *parent = 0);

signals:
    void sliderRangeFactorChanged(double value);

private slots:
    void rangeChanged();
private:
    double m_currentSliderRange;
    QRadioButton *m_radio1;
    QRadioButton *m_radio2;
    QRadioButton *m_radio3;

};


#endif // QUICKSIMULATIONSETTINGS_H
