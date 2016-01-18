// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/FittingWorker.h
//! @brief     Implements class FittingWorker
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIFitObserver.h"
#include "FitSuite.h"
#include "IntensityDataItem.h"
#include <boost/scoped_ptr.hpp>

void GUIFitObserver::update(FitSuite *subject)
{
    emit updateLog(QString("NCalls: %1 Chi: %2").
                      arg(QString::number(subject->getNumberOfIterations()),
                         QString::number(subject->getChi2())));

    if (subject->getNumberOfIterations() % m_update_interval == 0)
    {
        // prepare data for progres widget
        emit updateStatus(QString("Iteration: %1").arg(subject->getNumberOfIterations()));



        IntensityDataItem* sim = new IntensityDataItem();
        sim->setOutputData(subject->getSimulationData()->createOutputData());

        IntensityDataItem* chi = new IntensityDataItem();
        chi->setOutputData(subject->getChiSquaredMap()->createOutputData());
        emit updatePlots(sim, chi);
    }
}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

void GUIFitObserver::finishedPlotting()
{
    m_is_updating_plots = false;
}
