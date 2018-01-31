// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataFFTPresenter.h
//! @brief     Defines class IntensityDataFFTPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "IntensityDataFFTPresenter.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "SessionModel.h"
#include "GUIHelpers.h"
#include <QWidget>

IntensityDataFFTPresenter::IntensityDataFFTPresenter(QWidget* parent)
    : QObject(parent)
    , m_fftModel(new SessionModel("TempFFTModel"))
    , m_fftItem(nullptr)
{
    m_fftItem
        = dynamic_cast<IntensityDataItem*>(m_fftModel->insertNewItem(Constants::IntensityDataType));
}

IntensityDataItem* IntensityDataFFTPresenter::fftItem(IntensityDataItem* origItem)
{
    if (!origItem)
        throw GUIHelpers::Error("IntensityDataFFTPresenter::fftItem() -> Error. Empty item.");

    m_fftItem->setOutputData(
        IntensityDataFunctions::createFFT(*origItem->getOutputData()).release());

    return m_fftItem;
}
