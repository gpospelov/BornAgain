// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/ObsoleteRealDataWindow.cpp
//! @brief     Implements class ObsoleteRealDataWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteRealDataWindow.h"
#include "JobItem.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"


ObsoleteRealDataWindow::ObsoleteRealDataWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_plot(new ColorMapPlot(this))
{
    setCentralWidget(m_plot);
    setWindowTitle("Real Data");
}

void ObsoleteRealDataWindow::setItem(IntensityDataItem *item)
{
    m_plot->setItem(item);
}
