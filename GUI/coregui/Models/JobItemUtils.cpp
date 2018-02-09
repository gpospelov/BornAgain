// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemUtils.cpp
//! @brief     Implements class JobItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "JobItemUtils.h"
#include "ComboProperty.h"
#include "DomainObjectBuilder.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "InstrumentItems.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "SpecularSimulation.h"
#include "SpecularDataItem.h"
#include <QFileInfo>
#include <QDebug>

namespace
{
QMap<QString, AxesUnits> init_units_to_description_map()
{
    QMap<QString, AxesUnits> result;
    result[Constants::UnitsNbins] = AxesUnits::NBINS;
    result[Constants::UnitsRadians] = AxesUnits::RADIANS;
    result[Constants::UnitsDegrees] = AxesUnits::DEGREES;
    result[Constants::UnitsMm] = AxesUnits::MM;
    result[Constants::UnitsQyQz] = AxesUnits::QSPACE;
    return result;
}

QMap<AxesUnits, QString> init_description_to_units_map()
{
    QMap<AxesUnits, QString> result;
    result[AxesUnits::NBINS] = Constants::UnitsNbins;
    result[AxesUnits::RADIANS] = Constants::UnitsRadians;
    result[AxesUnits::DEGREES] = Constants::UnitsDegrees;
    result[AxesUnits::MM] = Constants::UnitsMm;
    result[AxesUnits::QSPACE] = Constants::UnitsQyQz;
    return result;
}
}

void JobItemUtils::setResults(JobItem* jobItem, const Simulation* simulation)
{
    auto dataItem = jobItem->getItem(JobItem::T_OUTPUT);
    Q_ASSERT(dataItem);

    if (dataItem->modelType() == Constants::IntensityDataType) {
        setResults(jobItem->intensityDataItem(), simulation);
    } else if (dataItem->modelType() == Constants::SpecularDataType) {
        auto specItem = dynamic_cast<SpecularDataItem*>(dataItem);
        setResults(specItem, simulation);
    } else {
        throw GUIHelpers::Error("JobItemUtils::setResults() -> Error. Unsupported data item.");
    }
}

void JobItemUtils::setResults(SpecularDataItem* specItem, const Simulation* simulation) {
    specItem->setOutputData(simulation->result().data());
}

void JobItemUtils::setResults(IntensityDataItem* intensityItem, const Simulation* simulation)
{
    if (dynamic_cast<const SpecularSimulation*>(simulation))
        throw GUIHelpers::Error("Error in JobItemUtils::setResults: specular simulation "
                                 "currently is not handled by GUI");
    auto sim_result = simulation->result();
    if (intensityItem->getOutputData() == nullptr) {
        const IDetector* detector = simulation->getInstrument().getDetector();
        setIntensityItemAxesUnits(intensityItem, detector);
        auto selected_units = axesUnitsFromName(intensityItem->selectedAxesUnits());
        updateAxesTitle(intensityItem);
        std::unique_ptr<OutputData<double>> data(sim_result.data(selected_units));
        intensityItem->setOutputData(data.release());
    } else {
        std::unique_ptr<OutputData<double>> data(sim_result.data());
        intensityItem->setRawDataVector(data.get());
        if (!intensityItem->isZAxisLocked())
            intensityItem->computeDataRange();
    }
}

//! Updates axes of OutputData in IntensityData item to correspond with ::P_AXES_UNITS selection.
//! InstrumentItem is used to get domain's detector map for given units.

void JobItemUtils::updateDataAxes(IntensityDataItem* intensityItem,
                                  const InstrumentItem* instrumentItem)
{
    Q_ASSERT(intensityItem);

    if (!instrumentItem) {
        // special case when reading old project files: project failed on load instrument
        // but we want to try to recover the rest.
        qInfo() << "JobItemUtils::updateDataAxes() -> Error. Absent instrument.";
        return;
    }

    if (!intensityItem->getOutputData())
        return;

    AxesUnits requested_units
        = axesUnitsFromName(intensityItem->selectedAxesUnits());

    OutputData<double>* newData = createDetectorMap(instrumentItem, requested_units);
    newData->setRawDataVector(intensityItem->getOutputData()->getRawDataVector());

    intensityItem->setOutputData(newData);
    intensityItem->setAxesRangeToData();
    updateAxesTitle(intensityItem);
}

//! loads intensity data from project directory

void JobItemUtils::loadIntensityData(IntensityDataItem *intensityItem, const QString &projectDir)
{
    QString filename = intensityItem->fileName(projectDir);
    auto data = IntensityDataIOFactory::readOutputData(filename.toStdString());
    intensityItem->setOutputData(data);
}


//! Saves intensityData in project directory

void JobItemUtils::saveIntensityData(IntensityDataItem* intensityItem, const QString& projectDir)
{
    if (!intensityItem || !intensityItem->getOutputData())
        return;

    QString filename = intensityItem->fileName(projectDir);
    IntensityDataIOFactory::writeOutputData(*intensityItem->getOutputData(),
                                            filename.toStdString());
}

//! Correspondance of domain detector axes types to their gui counterpart.

QString JobItemUtils::nameFromAxesUnits(AxesUnits units)
{
    static QMap<AxesUnits, QString> units_to_name = init_description_to_units_map();
    return units_to_name[units];
}

//! Correspondance of GUI axes units names to their domain counterpart.

AxesUnits JobItemUtils::axesUnitsFromName(const QString& name)
{
    static QMap<QString, AxesUnits> name_to_units = init_units_to_description_map();
    return name_to_units[name];
}

//! Converts detector default axes units into units most suitable for GUI.
//! SphericalDetector's default units (RADIANS) will be converted to DEGREES
//! RectangularDetector's default units (MM) will remain the same

AxesUnits JobItemUtils::preferableGUIAxesUnits(AxesUnits default_units)
{
    if (default_units == AxesUnits::RADIANS)
        return AxesUnits::DEGREES;

    if (default_units == AxesUnits::MM)
        return AxesUnits::MM;

    return default_units;
}

//! Sets axes units suitable for given instrument.

void JobItemUtils::setIntensityItemAxesUnits(IntensityDataItem* intensityItem,
                                              const InstrumentItem* instrumentItem)
{
    auto instrument = DomainObjectBuilder::buildInstrument(*instrumentItem);
    instrument->initDetector();
    setIntensityItemAxesUnits(intensityItem, instrument->getDetector());
}

//! Sets axes units suitable for given detector. Currently selected units will  be preserved.

void JobItemUtils::setIntensityItemAxesUnits(IntensityDataItem* intensityItem,
                                              const IDetector* detector)
{
    ComboProperty combo;

    for (auto units : detector->validAxesUnits())
        combo << nameFromAxesUnits(units);

    AxesUnits preferrable_units
        = preferableGUIAxesUnits(detector->defaultAxesUnits());

    combo.setValue(nameFromAxesUnits(preferrable_units));
    intensityItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.variant());
}

void JobItemUtils::updateAxesTitle(IntensityDataItem* intensityItem)
{
    // axes labels
    if (intensityItem->selectedAxesUnits() == Constants::UnitsRadians) {
        intensityItem->setXaxisTitle(QStringLiteral("phi_f [rad]"));
        intensityItem->setYaxisTitle(QStringLiteral("alpha_f [rad]"));
    } else if (intensityItem->selectedAxesUnits() == Constants::UnitsDegrees) {
        intensityItem->setXaxisTitle(QStringLiteral("phi_f [deg]"));
        intensityItem->setYaxisTitle(QStringLiteral("alpha_f [deg]"));
    } else if (intensityItem->selectedAxesUnits() == Constants::UnitsQyQz) {
        intensityItem->setXaxisTitle(QStringLiteral("Qy [1/nm]"));
        intensityItem->setYaxisTitle(QStringLiteral("Qz [1/nm]"));
    } else if (intensityItem->selectedAxesUnits() == Constants::UnitsMm) {
        intensityItem->setXaxisTitle(QStringLiteral("X [mm]"));
        intensityItem->setYaxisTitle(QStringLiteral("Y [mm]"));
    } else if (intensityItem->selectedAxesUnits() == Constants::UnitsNbins) {
        intensityItem->setXaxisTitle(QStringLiteral("X [nbins]"));
        intensityItem->setYaxisTitle(QStringLiteral("Y [nbins]"));
    }
}

void JobItemUtils::createDefaultDetectorMap(IntensityDataItem* intensityItem,
                                            const InstrumentItem* instrumentItem)
{
    auto instrument = DomainObjectBuilder::buildInstrument(*instrumentItem);
    instrument->initDetector();
    AxesUnits units = instrument->getDetector()->defaultAxesUnits();
    auto detector = instrument->getDetector();
    setIntensityItemAxesUnits(intensityItem, detector);
    updateAxesTitle(intensityItem);
    intensityItem->setOutputData(
        detector->createDetectorMap(instrument->getBeam(), preferableGUIAxesUnits(units))
            .release());
}

//! creates detector map from instrument description with axes corresponding to given units
OutputData<double>* JobItemUtils::createDetectorMap(const InstrumentItem* instrumentItem,
                                                     AxesUnits units)
{
    auto instrument = DomainObjectBuilder::buildInstrument(*instrumentItem);
    instrument->initDetector();

    if (units == AxesUnits::DEFAULT)
        units = instrument->getDetector()->defaultAxesUnits();

    auto result = instrument->getDetector()->createDetectorMap(instrument->getBeam(), units);
    if (!result) {
        throw GUIHelpers::Error("JobResultsPresenter::createDetectorMap -> Error. "
                                "Can't create detector map.");
    }

    return result.release();
}

