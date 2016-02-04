// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/JobResultsPresenter.cpp
//! @brief     Implements class JobResultsPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "JobResultsPresenter.h"
#include "item_constants.h"
#include "IntensityDataItem.h"
#include "GISASSimulation.h"
#include "ComboProperty.h"
#include "DomainObjectBuilder.h"
#include "InstrumentItem.h"
#include "Instrument.h"
#include "OutputData.h"
#include <QDebug>

namespace {
QMap<QString, IDetector2D::EAxesUnits> init_units_to_description_map() {
    QMap<QString, IDetector2D::EAxesUnits> result;
    result[Constants::UnitsNbins] = IDetector2D::NBINS;
    result[Constants::UnitsRadians] = IDetector2D::RADIANS;
    result[Constants::UnitsDegrees] = IDetector2D::DEGREES;
    result[Constants::UnitsMm] = IDetector2D::MM;
    result[Constants::UnitsQyQz] = IDetector2D::QYQZ;
    return result;
}

QMap<IDetector2D::EAxesUnits, QString> init_description_to_units_map() {
    QMap<IDetector2D::EAxesUnits, QString> result;
    result[IDetector2D::NBINS] = Constants::UnitsNbins;
    result[IDetector2D::RADIANS] = Constants::UnitsRadians;
    result[IDetector2D::DEGREES] = Constants::UnitsDegrees;
    result[IDetector2D::MM] = Constants::UnitsMm;
    result[IDetector2D::QYQZ] = Constants::UnitsQyQz;
    return result;
}


}

QMap<QString, IDetector2D::EAxesUnits> JobResultsPresenter::m_name_to_units
= init_units_to_description_map();

QMap<IDetector2D::EAxesUnits, QString> JobResultsPresenter::m_units_to_name
= init_description_to_units_map();


QString JobResultsPresenter::getNameFromAxesUnits(IDetector2D::EAxesUnits units)
{
    return m_units_to_name[units];
}

IDetector2D::EAxesUnits JobResultsPresenter::getAxesUnitsFromName(const QString &name)
{
    return m_name_to_units[name];
}

void JobResultsPresenter::setResults(IntensityDataItem *dataItem, const GISASSimulation *simulation)
{
    dataItem->getPropertyAttribute(IntensityDataItem::P_AXES_UNITS).setVisible();

    const IDetector2D *detector = simulation->getInstrument().getDetector();

    ComboProperty combo;
    foreach (auto units, detector->getValidAxesUnits()) {
        combo << getNameFromAxesUnits(units);
    }
    IDetector2D::EAxesUnits preferrable_units
        = preferableGUIAxesUnits(detector->getDefaultAxesUnits());

    combo.setValue(getNameFromAxesUnits(preferrable_units));

    dataItem->setRegisteredProperty(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
    dataItem->setOutputData(simulation->getDetectorIntensity(preferrable_units));
}

// Converts detector default axes units into units most suitable for GUI
// SphericalDetector's default units (RADIANS) will be converted to DEGREES
// RectangularDetector's default units (MM) will remain the same
IDetector2D::EAxesUnits
JobResultsPresenter::preferableGUIAxesUnits(IDetector2D::EAxesUnits default_units)
{
    if (default_units == IDetector2D::RADIANS)
        return IDetector2D::DEGREES;
    if (default_units == IDetector2D::MM)
        return IDetector2D::DEGREES;

    return default_units;
}

//! Updates axes of OutputData in IntensityData item to correspond
//! with IntensityDataItem::P_AXES_UNITS selection
//! InstrumentItem is used to get domain Instrument and be able to convert OutputData
void JobResultsPresenter::updateDataAxes(IntensityDataItem *intensityItem,
                                         const InstrumentItem *instrumentItem)
{
    Q_ASSERT(intensityItem);
    Q_ASSERT(instrumentItem);

    if(!intensityItem->getOutputData()) return;

    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();

    ComboProperty combo= intensityItem->getRegisteredProperty(IntensityDataItem::P_AXES_UNITS)
              .value<ComboProperty>();
    IDetector2D::EAxesUnits requested_units = getAxesUnitsFromName(combo.getValue());

    OutputData<double> *newData = instrument->getDetector()
            ->createDetectorMap(instrument->getBeam(), requested_units);
    Q_ASSERT(newData);
    newData->setRawDataVector(intensityItem->getOutputData()->getRawDataVector());

    intensityItem->setOutputData(newData);
    intensityItem->setAxesRangeToData();
}

