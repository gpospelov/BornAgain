// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/EnvironmentEditor.cpp
//! @brief     Implements class EnvironmentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "EnvironmentEditor.h"
#include "ComponentEditor.h"
#include "InstrumentItems.h"
#include "GroupItem.h"
#include <QGridLayout>

namespace
{
const QString background_title("Background");
}

EnvironmentEditor::EnvironmentEditor(QWidget* parent)
    : SessionItemWidget(parent)
    , m_backgroundEditor(new ComponentEditor(ComponentEditor::GroupWidget, background_title))
    , m_gridLayout(new QGridLayout)
{
    m_gridLayout->addWidget(m_backgroundEditor, 0, 0);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(m_gridLayout);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void EnvironmentEditor::subscribeToItem()
{
    m_backgroundEditor->setItem(instrumentItem()->backgroundGroup());
}

void EnvironmentEditor::unsubscribeFromItem()
{
    m_backgroundEditor->clearEditor();
}

GISASInstrumentItem* EnvironmentEditor::instrumentItem()
{
    auto result = dynamic_cast<GISASInstrumentItem*>(currentItem());
    Q_ASSERT(result);
    return result;
}
