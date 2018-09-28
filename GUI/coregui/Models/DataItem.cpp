// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/IntensityDataItem.cpp
//! @brief     Implements class IntensityDataItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataItem.h"
#include "BornAgainNamespace.h"
#include "ComboProperty.h"
#include "GUIHelpers.h"
#include "IntensityDataIOFactory.h"

const QString DataItem::P_FILE_NAME = "FileName";
const QString DataItem::P_AXES_UNITS = "Axes Units";

void DataItem::setOutputData(OutputData<double>* data)
{
    std::unique_lock<std::mutex> lock(m_update_data_mutex);
    m_data.reset(data);
}

void DataItem::setRawDataVector(std::vector<double> data)
{
    if (m_data->getAllocatedSize() != data.size())
        throw GUIHelpers::Error("DataItem::setRawDataVector() -> Error. "
                                "Different data size.");
    std::unique_lock<std::mutex> lock(m_update_data_mutex);
    m_data->setRawDataVector(std::move(data));
    emitDataChanged();
}

QString DataItem::fileName(const QString& projectDir) const
{
    QString filename = getItemValue(DataItem::P_FILE_NAME).toString();
    return projectDir.isEmpty() ? filename : projectDir + QStringLiteral("/") + filename;
}

QDateTime DataItem::lastModified() const
{
    return m_last_modified;
}

void DataItem::setLastModified(const QDateTime& dtime)
{
    m_last_modified = dtime;
}

QString DataItem::selectedAxesUnits() const
{
    ComboProperty combo = getItemValue(DataItem::P_AXES_UNITS).value<ComboProperty>();
    return combo.getValue();
}

void DataItem::saveData(const QString& projectDir)
{
    if (!getOutputData())
        return;

    std::unique_lock<std::mutex> lock(m_update_data_mutex);
    std::unique_ptr<OutputData<double>> clone(getOutputData()->clone());
    lock.unlock();
    IntensityDataIOFactory::writeOutputData(*clone,
                                            fileName(projectDir).toStdString());
}

void DataItem::resetToDefault()
{
    ComboProperty combo = ComboProperty() << Constants::UnitsNbins;
    setItemValue(DataItem::P_AXES_UNITS, combo.variant());
    getItem(DataItem::P_AXES_UNITS)->setVisible(true);
}

DataItem::DataItem(const QString& modelType) : SessionItem(modelType)
{
    // name of the file used to serialize given IntensityDataItem
    addProperty(P_FILE_NAME, QStringLiteral("undefined"))->setVisible(false);

    ComboProperty units = ComboProperty() << Constants::UnitsNbins;
    addProperty(P_AXES_UNITS, units.variant());

    mapper()->setOnPropertyChange([this](const QString& name) {
        if (name == P_FILE_NAME)
            setLastModified(QDateTime::currentDateTime());
    });

    mapper()->setOnValueChange([this]() {
        // OutputData was modified
        setLastModified(QDateTime::currentDateTime());
    });
}
