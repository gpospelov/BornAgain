// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ScriptPanel.cpp
//! @brief     Implements class ScriptPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ScriptPanel.h"
#include "PySampleWidget.h"
#include <QResizeEvent>
#include <QStackedWidget>

ScriptPanel::ScriptPanel(QWidget *parent)
    : InfoPanel(parent)
    , m_pySampleWidget(new PySampleWidget(this))
{
    setWindowTitle("Python Script");
    setObjectName("ScriptPanel");

    m_stackedWidget->addWidget(m_pySampleWidget);

    setContentVisible(false);
}

void ScriptPanel::setSampleModel(SampleModel *sampleModel)
{
    m_pySampleWidget->setSampleModel(sampleModel);
}

void ScriptPanel::setInstrumentModel(InstrumentModel *instrumentModel)
{
    m_pySampleWidget->setInstrumentModel(instrumentModel);
}
