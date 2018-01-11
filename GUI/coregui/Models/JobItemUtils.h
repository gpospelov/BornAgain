// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemUtils.h
//! @brief     Defines class JobItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef JOBITEMUTILS_H
#define JOBITEMUTILS_H

#include "IDetector.h"
#include <QMap>

class GISASSimulation;
class IntensityDataItem;
class GISASInstrumentItem;
class JobItem;

//! Contains set of convenience methods to set data to the IntensityDataItem from domain simulation.
//! Used to modify OutputData's axes units as requested by IntensityDataItem.

namespace JobItemUtils
{

//! Sets simulation results into the IntensityDataItem
BA_CORE_API_ void setResults(IntensityDataItem* intensityItem, const GISASSimulation* simulation);

//! updates axes of OutputData in IntensityData item
BA_CORE_API_ void updateDataAxes(IntensityDataItem* intensityItem,
                                 const GISASInstrumentItem* instrumentItem);

//! loads intensity data from project directory
BA_CORE_API_ void loadIntensityData(IntensityDataItem* intensityItem, const QString& projectDir);

//! saves intensity data into project directory
BA_CORE_API_ void saveIntensityData(IntensityDataItem* intensityItem, const QString& projectDir);

//! returns axes units names from their domain counterpart
BA_CORE_API_ QString nameFromAxesUnits(AxesUnits units);

//! returns domain axes units type from their GUI name
BA_CORE_API_ AxesUnits axesUnitsFromName(const QString& name);

//! converts detector default axes units into units most suitable for GUI
BA_CORE_API_ AxesUnits preferableGUIAxesUnits(AxesUnits default_units);

BA_CORE_API_ void setIntensityItemAxesUnits(IntensityDataItem* intensityItem,
                                            const GISASInstrumentItem* instrumentItem);

BA_CORE_API_ void setIntensityItemAxesUnits(IntensityDataItem* intensityItem,
                                            const IDetector* detector);

BA_CORE_API_ void updateAxesTitle(IntensityDataItem* intensityItem);

BA_CORE_API_ void createDefaultDetectorMap(IntensityDataItem* intensityItem,
                                           const GISASInstrumentItem* instrumentItem);

BA_CORE_API_ OutputData<double>* createDetectorMap(const GISASInstrumentItem* instrumentItem,
                                                   AxesUnits units);
}

#endif // JOBITEMUTILS_H

