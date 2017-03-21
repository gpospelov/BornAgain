// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InstrumentWidgets/ComponentInfoBox.cpp
//! @brief     Implements class ComponentInfoBox
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentInfoBox.h"
#include "ComponentBoxEditor.h"
#include <QGroupBox>
#include <QVBoxLayout>
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

void ComponentInfoBox::addPropertyItems(SessionItem *item)
{
    m_editor->addPropertyItems(item);
    m_item = item;
}

void ComponentInfoBox::clearEditor()
{
    m_editor->clearEditor();
    m_item = 0;
}

void ComponentInfoBox::dialogRequest()
{
    emit onDialogRequest(m_item, m_title);
}
