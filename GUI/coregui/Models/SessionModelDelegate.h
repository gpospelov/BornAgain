// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModelDelegate.h
//! @brief     Declares class SessionModelDelegate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODELDELEGATE_H
#define SESSIONMODELDELEGATE_H

#include "WinDllMacros.h"
#include <QStyledItemDelegate>

class ComboProperty;

//! The SessionModelDelegate class presents the content of SessionModel items in
//! standard QTreeView. Extents base QItemDelegate with possibility to show/edit
//! our custom QVariant's.

class BA_CORE_API_ SessionModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SessionModelDelegate(QWidget *parent);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

private slots:
    void onComboPropertyChanged(const ComboProperty &);

};

#endif
