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
#include "HistogramPlot.h"
#include <QVBoxLayout>

FitFlowWidget::FitFlowWidget(QWidget *parent)
    : QFrame(parent)
    , m_histPlot(new HistogramPlot)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(m_histPlot);

    setStyleSheet("background-color:white;");

    setLayout(layout);
}
