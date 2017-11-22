// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyWidgetItem.cpp
//! @brief     Implements class PropertyWidgetItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PropertyWidgetItem.h"
#include "SessionItem.h"
#include "SessionModel.h"
#include "SessionItemUtils.h"
#include "SessionModelDelegate.h"
#include "CustomEditors.h"
#include <QLabel>
#include <QWidget>
#include <QDataWidgetMapper>
#include <QGridLayout>
#include <QComboBox>
#include <QDebug>

PropertyWidgetItem::PropertyWidgetItem(QWidget* parent)
    : QObject(parent)
    , m_label(new QLabel)
    , m_editor(nullptr)
    , m_dataMapper(new QDataWidgetMapper(this))
    , m_delegate(new SessionModelDelegate(this))
    , m_item(nullptr)
{
    m_label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

PropertyWidgetItem::~PropertyWidgetItem()
{
    delete m_label;
    // if editor's action leads to deletion of the editor itself, we have to give him chance to
    // send all signals
    m_editor->deleteLater();
}

void PropertyWidgetItem::setItemEditor(const SessionItem* item, QWidget* editor)
{
    Q_ASSERT(m_item == nullptr);
    m_item = item;
    m_editor = editor;

    m_label->setText(item->displayName());

    m_dataMapper->setModel(item->model());
    m_dataMapper->setRootIndex(item->parent()->index());
    m_dataMapper->setCurrentModelIndex(item->index());
    m_dataMapper->addMapping(m_label, 0);
    m_dataMapper->addMapping(m_editor, 1);
    m_dataMapper->setItemDelegate(m_delegate);

    // Hack: QDataWidgetMapper doesn't listen for the widget (QComboBox is somewhat special).
    if (auto combo = dynamic_cast<ComboPropertyEditor*>(editor))
        connect(combo, &ComboPropertyEditor::currentIndexChanged, [=]{m_delegate->commitData(combo);});

    updateItemRoles();
}

void PropertyWidgetItem::addToGrid(QGridLayout* gridLayout, int nrow)
{
    Q_ASSERT(m_label);
    Q_ASSERT(m_editor);

    gridLayout->addWidget(m_label, nrow, 0);
    gridLayout->addWidget(m_editor, nrow, 1);
}

void PropertyWidgetItem::updateItemRoles()
{
    Q_ASSERT(m_item);
    m_label->setEnabled(m_item->isEnabled());
    m_editor->setEnabled(m_item->isEnabled());
    m_label->setToolTip(SessionItemUtils::ToolTipRole(*m_item).toString());
    m_editor->setToolTip(SessionItemUtils::ToolTipRole(*m_item).toString());
}

const SessionItem* PropertyWidgetItem::item()
{
    return m_item;
}
