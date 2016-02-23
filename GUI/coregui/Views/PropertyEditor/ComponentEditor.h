// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditor.h
//! @brief     Defines class ComponentEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITOR_H
#define COMPONENTEDITOR_H

#include "WinDllMacros.h"
#include "ComponentEditorPrivate.h"
#include <QWidget>
#include <memory>

class ComponentEditorPrivate;
class QtProperty;
class ParameterizedItem;
class QtVariantProperty;
class QModelIndex;
class SessionModel;

class BA_CORE_API_ ComponentEditor : public QWidget
{
    Q_OBJECT
public:

    ComponentEditor(QWidget *parent = 0);

//    void addItem(ParameterizedItem *item);

    void setItem(ParameterizedItem *item);

    void updateEditor(ParameterizedItem *item, QtVariantProperty *parentProperty = 0);
    void updateEditor2(ParameterizedItem *item, QtVariantProperty *parentProperty = 0);

    void clearEditor();

public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void onRowsInserted(const QModelIndex &parent, int first, int last);


private slots:
    void onQtPropertyChanged(QtProperty *, const QVariant &value);

private:
    QList<ParameterizedItem *> componentItems(ParameterizedItem *item) const;

    void disconnectModel(SessionModel *model);
    void connectModel(SessionModel *model);
    void disconnectManager();
    void connectManager();



    std::unique_ptr<ComponentEditorPrivate> m_d;
    ParameterizedItem *m_item;

};

#endif
