// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupAssistant.cpp
//! @brief     Implements class SimulationSetupAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationSetupAssistant.h"
#include "AxesItems.h"
#include "DetectorItems.h"
#include "IAxis.h"
#include "IDetector2D.h"
#include "InstrumentItem.h"
#include "IntensityDataItem.h"
#include "RealDataItem.h"
#include "SampleValidator.h"
#include <QDebug>
#include <QMessageBox>

//! Returns true if given setup is valid for submitting the job

SimulationSetupAssistant::SimulationSetupAssistant()
    : m_isValid(false)
{

}

bool SimulationSetupAssistant::isValidSimulationSetup(const MultiLayerItem *multiLayerItem,
                                                      const InstrumentItem *instrumentItem,
                                                      const RealDataItem *realData)
{
    clear();

    checkMultiLayerItem(multiLayerItem);
    checkInstrumentItem(instrumentItem);
    checkFittingSetup(instrumentItem, realData);

    if(!m_isValid)
        QMessageBox::warning(0, QStringLiteral("Can't run the job"), composeMessage());

    return m_isValid;
}

void SimulationSetupAssistant::clear()
{
    m_isValid = true;
    m_messages.clear();
}

void SimulationSetupAssistant::checkMultiLayerItem(const MultiLayerItem *multiLayerItem)
{
    if(!multiLayerItem) {
        m_messages.append(QStringLiteral("No sample selected"));
        m_isValid = false;
    } else {
        SampleValidator sampleValidator;
        if (!sampleValidator.isValidMultiLayer(multiLayerItem)) {
            m_isValid = false;
            m_messages.append(sampleValidator.getValidationMessage());
        }
    }
}

void SimulationSetupAssistant::checkInstrumentItem(const InstrumentItem *instrumentItem)
{
    if(!instrumentItem) {
        m_messages.append(QStringLiteral("No instrument selected"));
        m_isValid = false;
    }
}

//! Check if setup is suitable for fitting. In the case when there is a realData defined,
//! its axes will be compared with current detector item.

void SimulationSetupAssistant::checkFittingSetup(const InstrumentItem *instrumentItem,
                                                 const RealDataItem *realData)
{
    if(!realData)
        return;

    int nxData(0), nyData(0), nxDetector(0), nyDetector(0);
    realDataShape(realData, nxData, nyData);
    detectorShape(instrumentItem, nxDetector, nyDetector);

    if(nxData != nxDetector || nyData != nyDetector) {
        m_isValid = false;
        m_messages.append("The realData doesn't match selected instrument.");
        QString message = QString("Different shape of axes \n Detector [%1, %2], realData[%3, %4].")
                .arg(nxDetector).arg(nyDetector).arg(nxData).arg(nyData);
        m_messages.append(message);
    }
}

//! Composes the error message for message box.

QString SimulationSetupAssistant::composeMessage()
{
    QString result("Can't run the job with current settings\n\n");
    foreach(QString message, m_messages) {
        QString text = QString("- %1 \n").arg(message);
        result.append(text);
    }
    return result;
}

//! Returns shape of RealDataItem axes.

void SimulationSetupAssistant::realDataShape(const RealDataItem *realData, int &nx, int &ny)
{
    nx = ny = 0;
    if(const IntensityDataItem *intensityItem = realData->intensityDataItem()) {
        SessionItem *xaxis = intensityItem->getItem(IntensityDataItem::P_XAXIS);
        nx = xaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
        SessionItem *yaxis = intensityItem->getItem(IntensityDataItem::P_XAXIS);
        ny = yaxis->getItemValue(BasicAxisItem::P_NBINS).toInt();
    }
}

//! Returns shape of Instrument's detector axes.

void SimulationSetupAssistant::detectorShape(const InstrumentItem *instrumentItem, int &nx, int &ny)
{
    nx = ny = 0;
    DetectorItem *detectorItem = instrumentItem ->getDetectorItem();
    Q_ASSERT(detectorItem);

    auto subDetector = detectorItem->getGroupItem(DetectorItem::P_DETECTOR);
    Q_ASSERT(subDetector);

    std::unique_ptr<IDetector2D> detector;

    if(auto sphericalDetector = dynamic_cast<SphericalDetectorItem *>(subDetector)) {
        detector = sphericalDetector->createDetector();
    }

    else if(auto rectangularDetector = dynamic_cast<RectangularDetectorItem *>(subDetector)) {
        detector = rectangularDetector->createDetector();
    }

    Q_ASSERT(detector.get());
    nx = detector->getAxis(0).getSize();
    ny = detector->getAxis(1).getSize();
}
