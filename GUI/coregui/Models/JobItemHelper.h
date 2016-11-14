// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemHelper.h
//! @brief     Defines class JobItemHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef JOBITEMHELPER_H
#define JOBITEMHELPER_H

#include "IDetector2D.h"
#include <QMap>

class GISASSimulation;
class IntensityDataItem;
class InstrumentItem;
class JobItem;

//! The JobItemHelper is a mediator between GISASSimulation, JobItem and IntensityDataItem.
//! Used to modify OutputData's axes units as requested by IntensityDataItem.

class BA_CORE_API_ JobItemHelper
{
public:
    //! Sets simulation results into the IntensityDataItem
    static void setResults(IntensityDataItem *intensityItem, const GISASSimulation *simulation);


    //! updates axes of OutputData in IntensityData item
    static void updateDataAxes(IntensityDataItem *intensityItem,
                               const InstrumentItem *instrumentItem);

    static void adjustAxesUnitsToInstrument(IntensityDataItem *intensityDataItem,
                                                const InstrumentItem *instrumentItem);

    //! saves intensity data into project directory
    static void saveIntensityData(IntensityDataItem *intensityItem, const QString &projectDir);

    //! load intensity data from project directory
    static void loadIntensityData(JobItem *jobItem, const QString &projectDir);

    //! returns axes units names from their domain counterpart
    static QString getNameFromAxesUnits(IDetector2D::EAxesUnits units);

    //! returns domain axes units type from their GUI name
    static IDetector2D::EAxesUnits getAxesUnitsFromName(const QString &name);

    //! converts detector default axes units into units most suitable for GUI
    static IDetector2D::EAxesUnits preferableGUIAxesUnits(IDetector2D::EAxesUnits default_units);

    static void setIntensityItemAxesUnits(IntensityDataItem *intensityItem, const InstrumentItem *instrumentItem);
    static void setIntensityItemAxesUnits(IntensityDataItem *intensityItem, const IDetector2D *detector);


    static void updateAxesTitle(IntensityDataItem *intensityItem);

    static OutputData<double> *createDefaultDetectorMap(const InstrumentItem *instrumentItem);


    static OutputData<double> *createDetectorMap(const InstrumentItem *instrumentItem,
                                                 IDetector2D::EAxesUnits units);

    //!< correspondance of GUI axes units names to their domain counterpart
    static QMap<QString, IDetector2D::EAxesUnits> m_name_to_units;

    //!< correspondance of domain detector axes types to their gui counterpart
    static QMap<IDetector2D::EAxesUnits, QString> m_units_to_name;

};


#endif // JOBITEMHELPER_H

