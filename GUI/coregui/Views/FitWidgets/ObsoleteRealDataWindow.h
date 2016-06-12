// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/ObsoleteRealDataWindow.h
//! @brief     Declares class ObsoleteRealDataWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEREALDATAWINDOW_H
#define OBSOLETEREALDATAWINDOW_H

#include <QMainWindow>

class IntensityDataItem;
class ColorMapPlot;

class ObsoleteRealDataWindow : public QMainWindow
{
    Q_OBJECT

public:
    ObsoleteRealDataWindow(QWidget *parent = 0);

    void setItem(IntensityDataItem *item);

private:
    ColorMapPlot *m_plot;
};

#endif
