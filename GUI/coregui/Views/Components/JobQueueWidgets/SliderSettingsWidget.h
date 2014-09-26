#ifndef SLIDERSETTINGSWIDGET_H
#define SLIDERSETTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QRadioButton;

class BA_CORE_API_ SliderSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SliderSettingsWidget(QWidget *parent = 0);

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

#endif // SLIDERSETTINGSWIDGET_H
