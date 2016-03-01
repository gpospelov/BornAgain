// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentProxyEditor.h
//! @brief     Defines class ComponentProxyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTPROXYEDITOR_H
#define COMPONENTPROXYEDITOR_H

#include "WinDllMacros.h"
#include "ComponentEditorFlags.h"
#include <QWidget>
#include <memory>

class ComponentProxyEditorPrivate;
class ParameterizedItem;
class SessionModel;
class QtVariantProperty;
class QtProperty;
class QIdentityProxyModel;
class QModelIndex;
class QAbstractItemModel;

class BA_CORE_API_ ComponentProxyEditor : public QWidget
{
    Q_OBJECT
public:
    ComponentProxyEditor(QWidget *parent = 0);
    ~ComponentProxyEditor();

    void setItem(ParameterizedItem *item);
//    void addItemProperty(ParameterizedItem *item, const QString &name);

//    void updateEditor(ParameterizedItem *item, QtVariantProperty *parentProperty = 0);
    void updateEditor(const QModelIndex &parentIndex, QtVariantProperty *parentProperty = 0);

    void clearEditor();

    void setPresentationType(ComponentEditorFlags::PresentationType presentationType);

public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
    void onRowsInserted(const QModelIndex &parent, int first, int last);
    void onRowsRemoved(const QModelIndex &parent, int first, int last);

private slots:
    void onQtPropertyChanged(QtProperty *, const QVariant &value);

private:
    QList<ParameterizedItem *> componentItems(ParameterizedItem *item) const;

    void disconnectModel(const QAbstractItemModel *model);
    void connectModel(const QAbstractItemModel *model);
    void disconnectManager();
    void connectManager();

    std::unique_ptr<ComponentProxyEditorPrivate> m_d;
    std::unique_ptr<QIdentityProxyModel> m_proxy;
//    QAbstractItemModel *m_model;
};


#endif
