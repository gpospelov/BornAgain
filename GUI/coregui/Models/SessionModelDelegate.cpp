// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModelDelegate.cpp
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
#include "SessionModel.h"
#include "ComboProperty.h"
#include "PropertyBrowserUtils.h"
#include "ComboProperty.h"
#include <QDebug>
#include <QApplication>
#include <QPainter>

SessionModelDelegate::SessionModelDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{

}

void SessionModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    bool is_processed(false);

    const SessionModel* model = dynamic_cast<const SessionModel*>(index.model());



    QVariant prop_value = index.model()->data(index, Qt::EditRole);
    if(prop_value.canConvert<ComboProperty>()) {
        ComboProperty property = prop_value.value<ComboProperty>();
        QStyleOptionViewItem opt = option;
        opt.text = displayText(property.getValue(), option.locale);
        const QWidget *widget = opt.widget;
        QStyle *style = widget ? widget->style() : QApplication::style();
        style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
    }

    else {
        QStyledItemDelegate::paint(painter, option, index);
    }

    return;


    if(model && index.row() == 1) {
        const SessionItem *item = model->itemForIndex(index);
        Q_ASSERT(item);

        QVariant v = item->value();
        if(v.canConvert<ComboProperty>()) {
//            painter->save();

            ComboProperty property = v.value<ComboProperty>();

            is_processed = true;


//            QString text("xxx");
//            QRect textRect = option.rect;
//            painter->drawText(textRect,text);

            QStyleOptionViewItem opt = option;
            opt.text = displayText(property.getValue(), option.locale);
            const QWidget *widget = opt.widget;
            QStyle *style = widget ? widget->style() : QApplication::style();
            style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);

//            initStyleOption(&opt, index);
//            const QWidget *widget = QStyledItemDelegatePrivate::widget(option);
//            QStyle *style = widget ? widget->style() : QApplication::style();
//            style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);


//            QRect displayRect;
//            QStyleOptionViewItem opt = setOptions(index, option);
//            displayRect = textRectangle(painter, option.rect, opt.font, text);
//            drawDisplay(painter, opt, displayRect, text);

//            QRect textRect = option.rect;
//            painter->drawText(textRect,text);

//            painter->restore();


        }


    }





    if(!is_processed) QStyledItemDelegate::paint(painter, option, index);
}

QWidget *SessionModelDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

void SessionModelDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
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
    ComboPropertyEdit *editor = qobject_cast<ComboPropertyEdit *>(sender());
    Q_ASSERT(editor);
    qDebug() << "SessionModelDelegate::onComboPropertyChanged()" << property.getValue();
    emit commitData(editor);
    //emit closeEditor(editor);
}
