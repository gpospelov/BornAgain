// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RealDataWindow.h
//! @brief     Defines class RealDataWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef REALDATAWINDOW_H
#define REALDATAWINDOW_H

#include <QMainWindow>

class IntensityDataItem;
class ColorMapPlot;

class RealDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    RealDataWindow(QWidget *parent = 0);

    void setItem(IntensityDataItem *item);

private:
    ColorMapPlot *m_plot;
};

#endif
