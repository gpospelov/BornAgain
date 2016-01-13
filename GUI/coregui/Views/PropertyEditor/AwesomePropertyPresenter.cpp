// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/AwesomePropertyPresenter.cpp
//! @brief     Implements class AwesomePropertyPresenter
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AwesomePropertyPresenter.h"
#include "AwesomePropertyEditor.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <iostream>

AwesomePropertyPresenter::AwesomePropertyPresenter(const QString &title, QWidget *parent)
    : QWidget(parent)
    , m_groupBox(new GroupBox(title))
    , m_editor(new AwesomePropertyEditor(this,  AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE))
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

void AwesomePropertyPresenter::setItem(ParameterizedItem *item)
{
    m_editor->addItemProperties(item, QString(), AwesomePropertyEditor::INSERT_AFTER);
    m_item = item;
}

void AwesomePropertyPresenter::clearEditor()
{
    m_editor->clearEditor();
}

void AwesomePropertyPresenter::dialogRequest()
{
    emit onDialogRequest(m_item, m_title);
}
