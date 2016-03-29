// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/JobWidgets/RealDataWindow.cpp
//! @brief     Implements class RealDataWindow
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealDataWindow.h"
#include "JobItem.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"


RealDataWindow::RealDataWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_plot(new ColorMapPlot(this))
{
    setCentralWidget(m_plot);
    setWindowTitle("Real Data");
}

void RealDataWindow::setItem(IntensityDataItem *item)
{
    m_plot->setItem(item);
}
