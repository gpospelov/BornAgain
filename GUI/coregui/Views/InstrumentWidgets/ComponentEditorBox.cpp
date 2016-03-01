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

#include "ComponentEditorBox.h"
#include "ComponentEditor.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <iostream>

ComponentEditorBox::ComponentEditorBox(const QString &title, QWidget *parent)
    : QWidget(parent)
    , m_groupBox(new GroupInfoBox(title))
    , m_editor(new ComponentEditor)
    , m_item(0)
    , m_title(title)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    m_editor->setFlat();
//    m_editor->setPresentationType(ComponentEditorFlags::BROWSER_GROUPBOX | ComponentEditorFlags::SHOW_CONDENSED);

    QVBoxLayout *groupBoxLayout = new QVBoxLayout;
    groupBoxLayout->setContentsMargins( 0, 0, 0, 0 );
    groupBoxLayout->addWidget(m_editor);
    m_groupBox->setLayout(groupBoxLayout);

    connect(m_groupBox, SIGNAL(clicked()), this, SLOT(dialogRequest()));

    mainLayout->addWidget(m_groupBox);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

ComponentEditor *ComponentEditorBox::getEditor()
{
    return m_editor;
}

void ComponentEditorBox::setItem(ParameterizedItem *item)
{
    m_editor->setItem(item);
    m_item = item;
}

void ComponentEditorBox::clearEditor()
{
    m_editor->clearEditor();
}

void ComponentEditorBox::dialogRequest()
{
    emit onDialogRequest(m_item, m_title);
}
