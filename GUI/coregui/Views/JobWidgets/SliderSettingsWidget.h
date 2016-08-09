// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/SliderSettingsWidget.h
//! @brief     Defines class SliderSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SLIDERSETTINGSWIDGET_H
#define SLIDERSETTINGSWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QRadioButton;
class QCheckBox;

class BA_CORE_API_ SliderSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SliderSettingsWidget(QWidget *parent = 0);

signals:
    void sliderRangeFactorChanged(double value);
    void lockzChanged(bool value);

private slots:
    void rangeChanged();
    void onLockZChanged(int state);

private:
    double m_currentSliderRange;
    QRadioButton *m_radio1;
    QRadioButton *m_radio2;
    QRadioButton *m_radio3;
    QCheckBox *m_lockzCheckBox;
};

#endif // SLIDERSETTINGSWIDGET_H
