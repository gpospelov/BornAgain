// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobResultsPresenter.h
//! @brief     Defines class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef JOBRESULTSPRESENTER_H
#define JOBRESULTSPRESENTER_H

#include "WinDllMacros.h"
#include "IDetector2D.h"
#include <QMap>

class GISASSimulation;
class IntensityDataItem;
class InstrumentItem;

//! The JobResultsPresenter is a mediator between GISASSimulation, JobItem and IntensityDataItem.
//! Used to modify OutputData's axes units as requested by IntensityDataItem.

class BA_CORE_API_ JobResultsPresenter
{
public:

    //! returns axes units names from their domain counterpart
    static QString getNameFromAxesUnits(IDetector2D::EAxesUnits units);

    //! returns domain axes units type from their GUI name
    static IDetector2D::EAxesUnits getAxesUnitsFromName(const QString &name);

    //! Sets simulation results into the IntensityDataItem
    static void setResults(IntensityDataItem *dataItem, const GISASSimulation *simulation);

    //! converts detector default axes units into units most suitable for GUI
    static IDetector2D::EAxesUnits preferableGUIAxesUnits(IDetector2D::EAxesUnits default_units);

    //! updates axes of OutputData in IntensityData item
    static void updateDataAxes(IntensityDataItem *intensityItem,
                               const InstrumentItem *instrumentItem);
private:

    //!< correspondance of GUI axes units names to their domain counterpart
    static QMap<QString, IDetector2D::EAxesUnits> m_name_to_units;

    //!< correspondance of domain detector axes types to their gui counterpart
    static QMap<IDetector2D::EAxesUnits, QString> m_units_to_name;
};


#endif

