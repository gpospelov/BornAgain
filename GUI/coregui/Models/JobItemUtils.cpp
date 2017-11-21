// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemUtils.cpp
//! @brief     Implements class JobItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobItemUtils.h"
#include "ComboProperty.h"
#include "DomainObjectBuilder.h"
#include "GISASSimulation.h"
#include "GUIHelpers.h"
#include "InstrumentItem.h"
#include "IntensityDataIOFactory.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include <QFileInfo>

namespace
{
QMap<QString, DetectorAxesUnits> init_units_to_description_map()
{
    QMap<QString, DetectorAxesUnits> result;
    result[Constants::UnitsNbins] = DetectorAxesUnits::NBINS;
    result[Constants::UnitsRadians] = DetectorAxesUnits::RADIANS;
    result[Constants::UnitsDegrees] = DetectorAxesUnits::DEGREES;
    result[Constants::UnitsMm] = DetectorAxesUnits::MM;
    result[Constants::UnitsQyQz] = DetectorAxesUnits::QYQZ;
    return result;
}

QMap<DetectorAxesUnits, QString> init_description_to_units_map()
{
    QMap<DetectorAxesUnits, QString> result;
    result[DetectorAxesUnits::NBINS] = Constants::UnitsNbins;
    result[DetectorAxesUnits::RADIANS] = Constants::UnitsRadians;
    result[DetectorAxesUnits::DEGREES] = Constants::UnitsDegrees;
    result[DetectorAxesUnits::MM] = Constants::UnitsMm;
    result[DetectorAxesUnits::QYQZ] = Constants::UnitsQyQz;
    return result;
}
}

void JobItemUtils::setResults(IntensityDataItem* intensityItem, const GISASSimulation* simulation)
{
    if (intensityItem->getOutputData() == nullptr) {
        const IDetector2D* detector = simulation->getInstrument().getDetector();
        setIntensityItemAxesUnits(intensityItem, detector);
        auto selected_units = axesUnitsFromName(intensityItem->selectedAxesUnits());
        updateAxesTitle(intensityItem);
        std::unique_ptr<OutputData<double>> data(simulation->getDetectorIntensity(selected_units));
        intensityItem->setOutputData(data.release());
    } else {
        std::unique_ptr<OutputData<double>> data(simulation->getDetectorIntensity());
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
    Q_ASSERT(instrumentItem);

    if (!intensityItem->getOutputData())
        return;

    DetectorAxesUnits requested_units
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

QString JobItemUtils::nameFromAxesUnits(DetectorAxesUnits units)
{
    static QMap<DetectorAxesUnits, QString> units_to_name = init_description_to_units_map();
    return units_to_name[units];
}

//! Correspondance of GUI axes units names to their domain counterpart.

DetectorAxesUnits JobItemUtils::axesUnitsFromName(const QString& name)
{
    static QMap<QString, DetectorAxesUnits> name_to_units = init_units_to_description_map();
    return name_to_units[name];
}

//! Converts detector default axes units into units most suitable for GUI.
//! SphericalDetector's default units (RADIANS) will be converted to DEGREES
//! RectangularDetector's default units (MM) will remain the same

DetectorAxesUnits JobItemUtils::preferableGUIAxesUnits(DetectorAxesUnits default_units)
{
    if (default_units == DetectorAxesUnits::RADIANS)
        return DetectorAxesUnits::DEGREES;

    if (default_units == DetectorAxesUnits::MM)
        return DetectorAxesUnits::MM;

    return default_units;
}

//! Sets axes units suitable for given instrument.

void JobItemUtils::setIntensityItemAxesUnits(IntensityDataItem* intensityItem,
                                              const InstrumentItem* instrumentItem)
{
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();
    setIntensityItemAxesUnits(intensityItem, instrument->getDetector());
}

//! Sets axes units suitable for given detector. Currently selected units will  be preserved.

void JobItemUtils::setIntensityItemAxesUnits(IntensityDataItem* intensityItem,
                                              const IDetector2D* detector)
{
    ComboProperty combo;

    foreach (auto units, detector->getValidAxesUnits())
        combo << nameFromAxesUnits(units);

    DetectorAxesUnits preferrable_units
        = preferableGUIAxesUnits(detector->getDefaultAxesUnits());

    combo.setValue(nameFromAxesUnits(preferrable_units));
    intensityItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
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
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();
    DetectorAxesUnits units = instrument->getDetector()->getDefaultAxesUnits();
    auto detector = instrument->getDetector();
    setIntensityItemAxesUnits(intensityItem, detector);
    updateAxesTitle(intensityItem);
    intensityItem->setOutputData(detector->createDetectorMap(instrument->getBeam(),
                                                             preferableGUIAxesUnits(units)));
}

//! creates detector map from instrument description with axes corresponding to given units
OutputData<double>* JobItemUtils::createDetectorMap(const InstrumentItem* instrumentItem,
                                                     DetectorAxesUnits units)
{
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();

    if (units == DetectorAxesUnits::DEFAULT)
        units = instrument->getDetector()->getDefaultAxesUnits();

    OutputData<double>* result
        = instrument->getDetector()->createDetectorMap(instrument->getBeam(), units);

    if (!result) {
        throw GUIHelpers::Error("JobResultsPresenter::createDetectorMap -> Error. "
                                "Can't create detector map.");
    }

    return result;
}

