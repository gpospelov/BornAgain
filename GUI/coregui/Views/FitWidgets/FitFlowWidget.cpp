// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitFlowWidget.cpp
//! @brief     Implement class FitFlowWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitFlowWidget.h"
#include "FitSuiteItem.h"
#include "HistogramPlot.h"
#include <QVBoxLayout>

FitFlowWidget::FitFlowWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_histPlot(new HistogramPlot)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 15, 15, 0);
    layout->addWidget(m_histPlot);

    setStyleSheet("background-color:white;");
    setLayout(layout);
}

void FitFlowWidget::subscribeToItem()
{
    fitSuiteItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == FitSuiteItem::P_CHI2) {
                int iter = fitSuiteItem()->getItemValue(FitSuiteItem::P_ITERATION_COUNT).toInt();
                double chi = fitSuiteItem()->getItemValue(FitSuiteItem::P_CHI2).toDouble();
                if (iter == 0) {
                    m_histPlot->clearData();
                }
                m_histPlot->addData(static_cast<double>(iter), chi);
            }
        },
        this);
}

void FitFlowWidget::unsubscribeFromItem()
{
    m_histPlot->clearData();
    m_x.clear();
    m_y.clear();
}

FitSuiteItem* FitFlowWidget::fitSuiteItem()
{
    return dynamic_cast<FitSuiteItem*>(currentItem());
}

