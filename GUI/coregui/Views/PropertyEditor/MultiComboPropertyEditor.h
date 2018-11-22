// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/MultiComboPropertyEditor.h
//! @brief     Defines MultiComboPropertyEditor class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTICOMBOPROPERTYEDITOR_H
#define MULTICOMBOPROPERTYEDITOR_H

#include "CustomEditors.h"
#include <memory>
#include <QStyledItemDelegate>

class QStandardItemModel;
class QModelIndex;
class QStyleOptionViewItem;

//! Provides custom editor for ComboProperty with multi-select option.

class BA_CORE_API_ MultiComboPropertyEditor : public CustomEditor
{
    Q_OBJECT
public:
    explicit MultiComboPropertyEditor(QWidget* parent = nullptr);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected slots:
    virtual void onIndexChanged(int index);
    void onModelDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                            const QVector<int>&);

protected:
    void initEditor();
    void setConnected(bool isConnected);

    QComboBox* m_box;
    class WheelEventEater* m_wheel_event_filter;
    QStandardItemModel* m_model;
};

//! Provides custom style delegate for QComboBox to allow checkboxes.

class QCheckListStyledItemDelegate : public QStyledItemDelegate
{
public:
    QCheckListStyledItemDelegate(QObject* parent = nullptr);

    void paint(QPainter* painter_, const QStyleOptionViewItem& option_,
               const QModelIndex& index_) const;
};

#endif
