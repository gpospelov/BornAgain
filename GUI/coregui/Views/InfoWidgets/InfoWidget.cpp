// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/InfoWidget.cpp
//! @brief     Implements class InfoWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "InfoWidget.h"
#include "PySampleWidget.h"
#include <QResizeEvent>
#include <QStackedWidget>

InfoWidget::InfoWidget(QWidget *parent)
    : InfoPanel(parent)
    , m_pySampleWidget(new PySampleWidget(this))
{
    setWindowTitle("Python Script Viewer");

    m_stackedWidget->addWidget(m_pySampleWidget);

    setContentVisible(false);
}

void InfoWidget::setSampleModel(SampleModel *sampleModel)
{
    m_pySampleWidget->setSampleModel(sampleModel);
}

void InfoWidget::setInstrumentModel(InstrumentModel *instrumentModel)
{
    m_pySampleWidget->setInstrumentModel(instrumentModel);
}
