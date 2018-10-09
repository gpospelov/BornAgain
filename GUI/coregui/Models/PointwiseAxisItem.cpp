// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/PointwiseAxisItem.cpp
//! @brief     Implements pointwise axis item
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "PointwiseAxisItem.h"
#include "IntensityDataIOFactory.h"
#include "OutputData.h"
#include "PointwiseAxis.h"

namespace {
std::unique_ptr<OutputData<double>> makeOutputData(const PointwiseAxis& axis);
}

const QString PointwiseAxisItem::P_FILE_NAME = "FileName";

PointwiseAxisItem::PointwiseAxisItem()
    : BasicAxisItem(Constants::PointwiseAxisType)
{
    getItem(P_MIN)->setEnabled(false);
    getItem(P_NBINS)->setEnabled(false);
    getItem(P_MAX)->setEnabled(false);
    addProperty(P_FILE_NAME,QStringLiteral("undefined"))->setVisible(false);
    setLastModified(QDateTime::currentDateTime());
    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });
}

PointwiseAxisItem::~PointwiseAxisItem() = default;

void PointwiseAxisItem::setAxis(const IAxis* axis)
{
    setLastModified(QDateTime::currentDateTime());
    if (!axis) {
        m_axis.reset();
        return;
    }
    m_axis = std::make_unique<PointwiseAxis>(axis->getName(), axis->getBinCenters());
    getItem(P_MIN)->setValue(m_axis->getMin());
    getItem(P_MIN)->setValue(m_axis->getMax());
    getItem(P_NBINS)->setValue(static_cast<int>(m_axis->size()));
}

const IAxis* PointwiseAxisItem::getAxis()
{
    return m_axis.get();
}

std::unique_ptr<IAxis> PointwiseAxisItem::createAxis(double scale) const
{
    if (!m_axis)
        return nullptr;
    std::vector<double> centers = m_axis->getBinCenters();
    std::for_each(centers.begin(), centers.end(),
                  [scale](double& value) { value = value * scale; });
    return std::make_unique<PointwiseAxis>(m_axis->getName(), std::move(centers));
}

bool PointwiseAxisItem::load(const QString& projectDir)
{
    QString filename = SaveLoadInterface::fileName(projectDir);
    auto data = IntensityDataIOFactory::readOutputData(filename.toStdString());
    if (!data)
        return false;

    setAxis(&data->getAxis(0));
    return true;
}

bool PointwiseAxisItem::save(const QString& projectDir)
{
    if (!containsNonXMLData())
        return false;

    IntensityDataIOFactory::writeOutputData(*makeOutputData(*m_axis),
                                            SaveLoadInterface::fileName(projectDir).toStdString());
    return true;
}

bool PointwiseAxisItem::containsNonXMLData() const
{
    return static_cast<bool>(m_axis);
}

QDateTime PointwiseAxisItem::lastModified() const
{
    return m_last_modified;
}

QString PointwiseAxisItem::fileName() const
{
    return getItemValue(PointwiseAxisItem::P_FILE_NAME).toString();
}

void PointwiseAxisItem::setLastModified(const QDateTime& dtime)
{
    m_last_modified = dtime;
}

namespace {
std::unique_ptr<OutputData<double>> makeOutputData(const PointwiseAxis& axis)
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(axis);
    return result;
}
}
