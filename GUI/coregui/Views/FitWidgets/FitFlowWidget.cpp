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
    : QFrame(parent)
    , m_histPlot(new HistogramPlot)
    , m_fitSuiteItem(0)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 15, 15, 0);
    layout->addWidget(m_histPlot);

    setStyleSheet("background-color:white;");

    setLayout(layout);
}

FitFlowWidget::~FitFlowWidget()
{
    if(m_fitSuiteItem)
        m_fitSuiteItem->mapper()->unsubscribe(this);
}

void FitFlowWidget::setItem(FitSuiteItem *fitSuiteItem)
{
    if(fitSuiteItem == m_fitSuiteItem)
        return;

    if(m_fitSuiteItem)
        m_fitSuiteItem->mapper()->unsubscribe(this);

    m_fitSuiteItem = fitSuiteItem;
    if(!m_fitSuiteItem)
        return;

    m_fitSuiteItem->mapper()->setOnPropertyChange(
                [this](const QString &name)
    {
        if(name == FitSuiteItem::P_CHI2) {
            int iter = m_fitSuiteItem->getItemValue(FitSuiteItem::P_ITERATION_COUNT).toInt();
            double chi = m_fitSuiteItem->getItemValue(FitSuiteItem::P_CHI2).toDouble();
            if(iter == 0) {
                m_histPlot->clearData();
//                m_x.clear();
//                m_y.clear();
            }
//            m_x.push_back(static_cast<double>(iter));
//            m_y.push_back(chi);
            m_histPlot->addData(static_cast<double>(iter), chi);
        }
//        if(name == JobItem::P_STATUS) {
//            if(m_currentJobItem->isCompleted())
//                onResetViewAction();
//        }
    }, this);

    m_fitSuiteItem->mapper()->setOnItemDestroy(
                [this](SessionItem *) {
        m_fitSuiteItem = 0;
    }, this);

}

