// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SimulationWidgets/SimulationOptionsWidget.cpp
//! @brief     Implements class SimulationOptionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SimulationOptionsWidget.h"
#include "ComponentBoxEditor.h"
#include "ComponentEditor.h"
#include "SimulationOptionsItem.h"
#include <QGroupBox>
#include <QVBoxLayout>

SimulationOptionsWidget::SimulationOptionsWidget(QWidget *parent)
    : QWidget(parent)
    , m_boxEditor(new ComponentBoxEditor)

{
    QGroupBox *groupBox = new QGroupBox("Simulation Parameters");

    QVBoxLayout *groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    groupLayout->addWidget(m_boxEditor);

    // main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);

}

void SimulationOptionsWidget::setItem(SimulationOptionsItem *item)
{
    m_boxEditor->clearEditor();
    m_boxEditor->addPropertyItems(item);
//    m_boxEditor->setItem(item);
}
