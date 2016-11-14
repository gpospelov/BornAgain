// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemHelper.cpp
//! @brief     Implements class JobItemHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "JobItemHelper.h"
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

QMap<QString, IDetector2D::EAxesUnits> JobItemHelper::m_name_to_units
    = init_units_to_description_map();

QMap<IDetector2D::EAxesUnits, QString> JobItemHelper::m_units_to_name
    = init_description_to_units_map();

void JobItemHelper::setResults(IntensityDataItem *intensityItem,
                                     const GISASSimulation *simulation)
{
    IDetector2D::EAxesUnits selected_units = IDetector2D::DEFAULT;

    if(intensityItem->getOutputData() == nullptr) {
        const IDetector2D *detector = simulation->getInstrument().getDetector();
        setIntensityItemAxesUnits(intensityItem, detector);
        selected_units = getAxesUnitsFromName(intensityItem->getSelectedAxesUnits());
        updateAxesTitle(intensityItem);
    }

    std::unique_ptr<OutputData<double>> data(simulation->getDetectorIntensity(selected_units));

    if(intensityItem->getOutputData() == nullptr) {
        intensityItem->setOutputData(data.release());
    } else {
        intensityItem->setRawDataVector(data.get());
        if(!intensityItem->isZAxisLocked())
            intensityItem->computeDataRange();
    }

}

//! Updates axes of OutputData in IntensityData item to correspond with ::P_AXES_UNITS selection.
//! InstrumentItem is used to get domain's detector map for given units.

void JobItemHelper::updateDataAxes(IntensityDataItem *intensityItem,
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

void JobItemHelper::adjustAxesUnitsToInstrument(IntensityDataItem *intensityDataItem,
                                                    const InstrumentItem *instrumentItem)
{
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();

    IDetector2D::EAxesUnits preferrable_units
        = preferableGUIAxesUnits(instrument->getDetector()->getDefaultAxesUnits());

    ComboProperty unitsCombo;
    foreach (auto units, instrument->getDetector()->getValidAxesUnits())
        unitsCombo << getNameFromAxesUnits(units);
    unitsCombo.setValue(getNameFromAxesUnits(preferrable_units));

    intensityDataItem->setItemValue(IntensityDataItem::P_AXES_UNITS, unitsCombo.getVariant());
}


//! Saves intensityData in project directory

void JobItemHelper::saveIntensityData(IntensityDataItem *intensityItem, const QString &projectDir)
{
    if(!intensityItem || !intensityItem->getOutputData())
        return;

    QString filename = intensityItem->fileName(projectDir);
    IntensityDataIOFactory::writeOutputData(
                *intensityItem->getOutputData(), filename.toStdString());
}

//! Loads intensityData from project directory

void JobItemHelper::loadIntensityData(JobItem *jobItem, const QString &projectDir)
{
    IntensityDataItem *intensityItem = jobItem->intensityDataItem();
    if(!intensityItem)
        return;

    QString filename = intensityItem->fileName(projectDir);

    QFileInfo info(filename);
    if (info.exists()) {
        std::unique_ptr<OutputData<double>> rawData(
            IntensityDataIOFactory::readOutputData(filename.toStdString()));
        setIntensityItemAxesUnits(intensityItem, jobItem->instrumentItem());
        intensityItem->setOutputData(rawData.release());

    } else {
        jobItem->setStatus(Constants::STATUS_FAILED);
        QString warning("Error while loading job from file, intensity data file '");
        warning.append(filename);
        warning.append("' was not found");
        jobItem->setComments(warning);
    }
}

QString JobItemHelper::getNameFromAxesUnits(IDetector2D::EAxesUnits units)
{
    return m_units_to_name[units];
}

IDetector2D::EAxesUnits JobItemHelper::getAxesUnitsFromName(const QString &name)
{
    return m_name_to_units[name];
}

//! Converts detector default axes units into units most suitable for GUI.
//! SphericalDetector's default units (RADIANS) will be converted to DEGREES
//! RectangularDetector's default units (MM) will remain the same

IDetector2D::EAxesUnits
JobItemHelper::preferableGUIAxesUnits(IDetector2D::EAxesUnits default_units)
{
    if (default_units == IDetector2D::RADIANS)
        return IDetector2D::DEGREES;

    if (default_units == IDetector2D::MM)
        return IDetector2D::MM;

    return default_units;
}

//! Sets axes units suitable for given instrument.

void JobItemHelper::setIntensityItemAxesUnits(IntensityDataItem *intensityItem,
                                              const InstrumentItem *instrumentItem)
{
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();
    setIntensityItemAxesUnits(intensityItem, instrument->getDetector());
}


//! Sets axes units suitable for given detector. Currently selected units will  be preserved.

void JobItemHelper::setIntensityItemAxesUnits(IntensityDataItem *intensityItem,
                                              const IDetector2D *detector)
{
    ComboProperty orig = intensityItem->getItemValue(IntensityDataItem::P_AXES_UNITS)
                              .value<ComboProperty>();

//    if(!combo.getValues().isEmpty())
//        return;

    QString cachedUnits = orig.getCachedValue();

    intensityItem->getItem(IntensityDataItem::P_AXES_UNITS)->setVisible(true);

    ComboProperty combo;
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

    intensityItem->setItemValue(IntensityDataItem::P_AXES_UNITS, combo.getVariant());
}


void JobItemHelper::updateAxesTitle(IntensityDataItem *intensityItem)
{
    // axes labels
    if (intensityItem->getSelectedAxesUnits() == Constants::UnitsRadians) {
        intensityItem->setXaxisTitle("phi_f [rad]");
        intensityItem->setYaxisTitle("alpha_f [rad]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsDegrees) {
        intensityItem->setXaxisTitle("phi_f [deg]");
        intensityItem->setYaxisTitle("alpha_f [deg]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsQyQz) {
        intensityItem->setXaxisTitle("Qy [1/nm]");
        intensityItem->setYaxisTitle("Qz [1/nm]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsMm) {
        intensityItem->setXaxisTitle("X [mm]");
        intensityItem->setYaxisTitle("Y [mm]");
    } else if (intensityItem->getSelectedAxesUnits() == Constants::UnitsNbins) {
        intensityItem->setXaxisTitle("X [nbins]");
        intensityItem->setYaxisTitle("Y [nbins]");
    }
}


OutputData<double> *JobItemHelper::createDefaultDetectorMap(const InstrumentItem *instrumentItem)
{
    DomainObjectBuilder builder;
    auto instrument = builder.buildInstrument(*instrumentItem);
    instrument->initDetector();
    IDetector2D::EAxesUnits units = instrument->getDetector()->getDefaultAxesUnits();
    return instrument->getDetector()->createDetectorMap(instrument->getBeam(),
                                                        preferableGUIAxesUnits(units));
}



//! creates detector map from instrument description with axes corresponding to given units
OutputData<double> *JobItemHelper::createDetectorMap(const InstrumentItem *instrumentItem,
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
