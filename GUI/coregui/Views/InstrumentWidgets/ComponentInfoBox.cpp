// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InstrumentWidgets/ComponentEditorBox.h
//! @brief     Implements class ComponentEditorBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ComponentInfoBox.h"
#include "ComponentBoxEditor.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <iostream>

ComponentInfoBox::ComponentInfoBox(const QString &title, QWidget *parent)
    : QWidget(parent)
    , m_groupBox(new GroupInfoBox(title))
    , m_editor(new ComponentBoxEditor)
    , m_item(0)
    , m_title(title)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->setContentsMargins( 0, 0, 0, 0 );
    groupBoxLayout->addWidget(m_editor);
    m_groupBox->setLayout(groupBoxLayout);

    connect(m_groupBox, SIGNAL(clicked()), this, SLOT(dialogRequest()));

    mainLayout->addWidget(m_groupBox);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void ComponentInfoBox::addPropertyItems(ParameterizedItem *item)
{
    m_editor->addPropertyItems(item);
    m_item = item;
}

void ComponentInfoBox::clearEditor()
{
    m_editor->clearEditor();
}

void ComponentInfoBox::dialogRequest()
{
    emit onDialogRequest(m_item, m_title);
}
