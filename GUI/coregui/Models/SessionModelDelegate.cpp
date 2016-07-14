// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModelDelegate.cpp
//! @brief     Implements class SessionModelDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionModelDelegate.h"
#include "PropertyBrowserUtils.h"
#include <QApplication>

SessionModelDelegate::SessionModelDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void SessionModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    QVariant prop_value = index.model()->data(index, Qt::EditRole);
    if(prop_value.canConvert<ComboProperty>()) {
        ComboProperty property = prop_value.value<ComboProperty>();
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index); // calling original method to take into accounts colors etc
        opt.text = displayText(property.getValue(), option.locale); // by overriding text with ours
        const QWidget *widget = opt.widget;
        QStyle *style = widget ? widget->style() : QApplication::style();
        style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }

}

QWidget *SessionModelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    if (index.data().canConvert<ComboProperty>()) {
        ComboPropertyEdit *editor = new ComboPropertyEdit(parent);
        ComboProperty combo = index.data().value<ComboProperty>();
        editor->setComboProperty(combo);
        connect(editor, SIGNAL(comboPropertyChanged(const ComboProperty &)),
                this, SLOT(onComboPropertyChanged(const ComboProperty &)));
        return editor;

    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }

}

void SessionModelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    if (index.data().canConvert<ComboProperty>()) {
        ComboPropertyEdit *comboEditor = qobject_cast<ComboPropertyEdit *>(editor);
        model->setData(index, comboEditor->getComboProperty().getVariant());
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }

}

void SessionModelDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.data().canConvert<ComboProperty>()) {
        //as using custom widget, doing nothing here
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void SessionModelDelegate::onComboPropertyChanged(const ComboProperty &property)
{
    Q_UNUSED(property);
    ComboPropertyEdit *editor = qobject_cast<ComboPropertyEdit *>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
    //emit closeEditor(editor); // Qt by default leaves editor alive after editing finished
}
