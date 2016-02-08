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
#include "GUIHelpers.h"
#include "JobItem.h"
#include "IntensityDataIOFactory.h"
#include <QFileInfo>
#include <QDebug>

namespace
{
QMap<QString, IDetector2D::EAxesUnits> init_units_to_description_map()
{
    QMap<QString, IDetector2D::EAxesUnits> result;
    result[Constants::UnitsNbins] = IDetector2D::NBINS;
    result[Constants::UnitsRadians] = IDetector2D::RADIANS;
    result[Constants::UnitsDegrees] = IDetector2D::DEGREES;
    result[Constants::UnitsMm] = IDetector2D::MM;
    result[Constants::UnitsQyQz] = IDetector2D::QYQZ;
    return result;
}

QMap<IDetector2D::EAxesUnits, QString> init_description_to_units_map()
{
    QMap<IDetector2D::EAxesUnits, QString> result;
    result[IDetector2D::NBINS] = Constants::UnitsNbins;
    result[IDetector2D::RADIANS] = Constants::UnitsRadians;
    result[IDetector2D::DEGREES] = Constants::UnitsDegrees;
    result[IDetector2D::MM] = Constants::UnitsMm;
    result[IDetector2D::QYQZ] = Constants::UnitsQyQz;
    return result;
}
}

// -------------------------------------------------------------------------------------------------

QMap<QString, IDetector2D::EAxesUnits> JobResultsPresenter::m_name_to_units
    = init_units_to_description_map();

QMap<IDetector2D::EAxesUnits, QString> JobResultsPresenter::m_units_to_name
    = init_description_to_units_map();

void JobResultsPresenter::setResults(IntensityDataItem *intensityItem,
                                     const GISASSimulation *simulation)
{
    const IDetector2D *detector = simulation->getInstrument().getDetector();

    initIntensityItemProperties(intensityItem, detector);

    IDetector2D::EAxesUnits selected_units
        = getAxesUnitsFromName(intensityItem->getSelectedAxesUnits());
    intensityItem->setOutputData(simulation->getDetectorIntensity(selected_units));
    updateAxesTitle(intensityItem);
}

//! Updates axes of OutputData in IntensityData item to correspond
//! with IntensityDataItem::P_AXES_UNITS selection
//! InstrumentItem is used to get domain Instrument and be able to convert OutputData
void JobResultsPresenter::updateDataAxes(IntensityDataItem *intensityItem,
                                         const InstrumentItem *instrumentItem)
{
    Q_ASSERT(intensityItem);
    Q_ASSERT(instrumentItem);

    if (!intensityItem->getOutputData())
        return;

    IDetector2D::EAxesUnits requested_units
        = getAxesUnitsFromName(intensityItem->getSelectedAxesUnits());

    OutputData<double> *newData = createDetectorMap(instrumentItem, requested_units);
    newData->setRawDataVector(intensityItem->getOutputData()->getRawDataVector());

    intensityItem->setOutputData(newData);
    intensityItem->setAxesRangeToData();
    updateAxesTitle(intensityItem);
}

//! Saves intensityData in project directory
//! Axes of data will be reset to default
void JobResultsPresenter::saveIntensityData(JobItem *jobItem, const QString &projectDir)
{
    IntensityDataItem *dataItem = jobItem->getIntensityDataItem();
    if (dataItem) {
        QString filename = projectDir + QStringLiteral("/") + dataItem->itemName();

        std::unique_ptr<OutputData<double>> dataToSave(
            createDetectorMap(jobItem->getInstrumentItem(), IDetector2D::DEFAULT));
        dataToSave->setRawDataVector(dataItem->getOutputData()->getRawDataVector());
        IntensityDataIOFactory::writeOutputData(*dataToSave, filename.toStdString());
    }
}

//! Loads intensityData from project directory
//! IntensityDataItem will be initialized to match last selected axes
void JobResultsPresenter::loadIntensityData(JobItem *jobItem, const QString &projectDir)
{
    IntensityDataItem *intensityItem = jobItem->getIntensityDataItem();
    if (intensityItem) {
        QString filename = projectDir + "/" + intensityItem->itemName();
        QFileInfo info(filename);
        if (info.exists()) {
            IntensityDataItem *intensityItem = jobItem->getIntensityDataItem();

            if (intensityItem) {
                DomainObjectBuilder builder;
                auto instrument = builder.buildInstrument(*jobItem->getInstrumentItem());
                instrument->initDetector();
                initIntensityItemProperties(intensityItem, instrument->getDetector());

                std::unique_ptr<OutputData<double>> rawData(
                    IntensityDataIOFactory::readOutputData(filename.toStdString()));

                IDetector2D::EAxesUnits requested_units
                    = getAxesUnitsFromName(intensityItem->getSelectedAxesUnits());

                OutputData<double> *result = instrument->getDetector()->createDetectorMap(
                    instrument->getBeam(), requested_units);

                result->setRawDataVector(rawData->getRawDataVector());
                intensityItem->setOutputData(result);
            }
        } else {
            jobItem->setStatus(Constants::STATUS_FAILED);
            QString warning("Error while loading job from file, intensity data file '");
            warning.append(filename);
            warning.append("' was not found");
            jobItem->setComments(warning);
        }
    }
}

QString JobResultsPresenter::getNameFromAxesUnits(IDetector2D::EAxesUnits units)
{
    return m_units_to_name[units];
}

IDetector2D::EAxesUnits JobResultsPresenter::getAxesUnitsFromName(const QString &name)
{
    return m_name_to_units[name];
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
        return IDetector2D::MM;

    return default_units;
}

//! inits properties of IntensityDataItem for the case of selectable axes units
void JobResultsPresenter::initIntensityItemProperties(IntensityDataItem *intensityItem,
                                                      const IDetector2D *detector)
{
    ComboProperty combo = intensityItem->getRegisteredProperty(IntensityDataItem::P_AXES_UNITS)
                              .value<ComboProperty>();

    QString cachedUnits = combo.getCachedValue();

    intensityItem->getPropertyAttribute(IntensityDataItem::P_AXES_UNITS).setVisible();

    foreach (auto units, detector->getValidAxesUnits()) {
        combo << getNameFromAxesUnits(units);
    }

    if (cachedUnits.isEmpty()) {
        IDetector2D::EAxesUnits preferrable_units
            = preferableGUIAxesUnits(detector->getDefaultAxesUnits());
        combo.setValue(getNameFromAxesUnits(preferrable_units));
    } else {
        combo.setValue(cachedUnits);
    }

    intensityItem->setRegisteredProperty(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
}

void JobResultsPresenter::updateAxesTitle(IntensityDataItem *intensityItem)
{
    // axes labels
    if (intensityItem->getSelectedAxesUnits() == Constants::UnitsRadians) {
        intensityItem->setXaxisTitle("phi_f [rad]");
        intensityItem->setYaxisTitle("alpha_f [rad]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsDegrees) {
        intensityItem->setXaxisTitle("phi_f [deg]");
        intensityItem->setYaxisTitle("alpha_f [deg]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsQyQz) {
        intensityItem->setXaxisTitle("Qy");
        intensityItem->setYaxisTitle("Qz");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsMm) {
        intensityItem->setXaxisTitle("X [mm]");
        intensityItem->setYaxisTitle("Y [mm]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsNbins) {
        intensityItem->setXaxisTitle("X [nbins]");
        intensityItem->setYaxisTitle("Y [nbins]");
    }
}

//! creates detector map from instrument description with axes corresponding to given units
OutputData<double> *JobResultsPresenter::createDetectorMap(const InstrumentItem *instrumentItem,
                                                           IDetector2D::EAxesUnits units)
{
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();

    if (units == IDetector2D::DEFAULT)
        units = instrument->getDetector()->getDefaultAxesUnits();

    OutputData<double> *result
        = instrument->getDetector()->createDetectorMap(instrument->getBeam(), units);

    if (!result) {
        throw GUIHelpers::Error("JobResultsPresenter::createDetectorMap -> Error. "
                                "Can't create detector map.");
    }

    return result;
}
