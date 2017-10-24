// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonController.cpp
//! @brief     Implements class FitComparisonController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitComparisonController.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include "PropertyRepeater.h"

FitComparisonController::FitComparisonController(QObject* parent)
    : QObject(parent)
    , m_propertyRepeater(new PropertyRepeater(this))
    , m_relativeDiffItem(nullptr)
    , m_tempIntensityDataModel(new SessionModel("TempIntensityDataModel", this))
{
    createRelativeDifferenceItem();
}

IntensityDataItem* FitComparisonController::diffItem()
{
    return m_relativeDiffItem;
}

void FitComparisonController::setItems(IntensityDataItem* realDataItem,
                                       IntensityDataItem* simDataItem)
{
    m_propertyRepeater->addItem(realDataItem);
    m_propertyRepeater->addItem(simDataItem);
}

void FitComparisonController::clear()
{
    m_propertyRepeater->clear();
}

void FitComparisonController::createRelativeDifferenceItem()
{
    m_tempIntensityDataModel->clear();

    m_relativeDiffItem = dynamic_cast<IntensityDataItem*>(
        m_tempIntensityDataModel->insertNewItem(Constants::IntensityDataType));
}
