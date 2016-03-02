// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentBoxEditor.h
//! @brief     Defines class ComponentBoxEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTBOXEDITOR_H
#define COMPONENTBOXEDITOR_H

#include "WinDllMacros.h"
#include "ComponentEditor.h"

//! Special version of editor to show property item as standard qt widgets

class BA_CORE_API_ ComponentBoxEditor : public ComponentEditor
{
    Q_OBJECT
public:
    ComponentBoxEditor(QWidget *parent = 0);

    void addPropertyItems(ParameterizedItem *item, const QString &group_name=QString());
    void updatePropertyItems(ParameterizedItem *item, QtVariantProperty *parentProperty=0);

    void addItem(ParameterizedItem *item, const QString &group_name=QString());
    void updateItem(ParameterizedItem *item, QtVariantProperty *parentProperty);

public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void onRowsInserted(const QModelIndex &parent, int first, int last);

};


#endif
