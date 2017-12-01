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
#include "SessionItem.h"
#include "PropertyEditorFactory.h"
#include "CustomEditors.h"
#include "SessionFlags.h"
#include <QApplication>
#include <QLocale>

namespace {

bool isDoubleProperty(const QModelIndex& index)
{
    return index.data().type() == QVariant::Double;
}

//! Returns text representation of double value depending on user defined editor type.
QString doubleToString(const SessionItem& item)
{
    QString result;

    Q_ASSERT(item.value().type() == QVariant::Double);
    if (item.editorType() == Constants::ScientificEditorType) {
        result = QString::number(item.value().toDouble(), 'g');
    } else {
        auto locale = QLocale::system();
        result = locale.toString(item.value().toDouble(), 'f', item.decimals());
    }

    return result;
}

QWidget* createEditorFromIndex(const QModelIndex& index, QWidget* parent) {
    if (index.column() == SessionFlags::ITEM_VALUE && index.internalPointer()) {
        auto item = static_cast<SessionItem*>(index.internalPointer());
        return PropertyEditorFactory::CreateEditor(*item, parent);
    }
    return nullptr;
}

}

SessionModelDelegate::SessionModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void SessionModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
                                 const QModelIndex& index) const
{
    if (PropertyEditorFactory::IsCustomVariant(index.data())) {
        QString text = PropertyEditorFactory::ToString(index.data());
        paintCustomLabel(painter, option, index, text);

    } else if (isDoubleProperty(index)) {
        auto item = static_cast<SessionItem*>(index.internalPointer());
        paintCustomLabel(painter, option, index, doubleToString(*item));

    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QWidget* SessionModelDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                            const QModelIndex& index) const
{
    auto result = createEditorFromIndex(index, parent);

    if (result) {
        if(auto customEditor = dynamic_cast<CustomEditor*>(result)) {
            customEditor->setData(index.data());
            connect(customEditor, &CustomEditor::dataChanged,
                    this, &SessionModelDelegate::onCustomEditorDataChanged);
        } else {
            // Int and Double will be handled by standard spin boxes
            // QStyledItemDelegate already knows how to handle it, no special connections are required
        }

    } else {
        result = QStyledItemDelegate::createEditor(parent, option, index);
    }

    return result;
}

//! Propagates changed data from the editor to the model.

void SessionModelDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
                                        const QModelIndex& index) const
{
    auto customEditor = qobject_cast<CustomEditor*>(editor);
    if (index.column() == SessionFlags::ITEM_VALUE && customEditor)
        model->setData(index, customEditor->editorData());
    else
        QStyledItemDelegate::setModelData(editor, model, index);
}

//! Propagates the data change from the model to the editor (if it is still opened).

void SessionModelDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    auto customEditor = dynamic_cast<CustomEditor*>(editor);
    if (index.column() == SessionFlags::ITEM_VALUE && customEditor)
        customEditor->setData(index.data());
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

//! Increases height of the row by 20% wrt the default.

QSize SessionModelDelegate::sizeHint(const QStyleOptionViewItem& option,
                                     const QModelIndex& index) const
{
    QSize result = QStyledItemDelegate::sizeHint(option, index);
    result.setHeight(static_cast<int>(result.height() * 1.2));
    return result;
}

//! Makes an editor occupying whole available space in a cell. If cell contains an icon
//! as a decoration (i.e. icon of material property), it will be hidden as soon as editor
//! up and running.

void SessionModelDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                                                const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
    editor->setGeometry(option.rect);
}

//! Notifies everyone that the editor has completed editing the data.

void SessionModelDelegate::onCustomEditorDataChanged(const QVariant& )
{
    CustomEditor* editor = qobject_cast<CustomEditor*>(sender());
    Q_ASSERT(editor);
    emit commitData(editor);
}

//! Paints custom text in a a place corresponding given index.

void SessionModelDelegate::paintCustomLabel(QPainter* painter, const QStyleOptionViewItem& option,
                                            const QModelIndex& index, const QString& text) const
{
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index); // calling original method to take into accounts colors etc
    opt.text = displayText(text, option.locale); // by overriding text with ours
    const QWidget* widget = opt.widget;
    QStyle* style = widget ? widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, widget);
}
