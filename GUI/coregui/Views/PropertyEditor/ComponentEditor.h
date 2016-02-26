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
#include "ComponentEditorFlags.h"
#include <QWidget>
#include <memory>

class ComponentEditorPrivate;
class ParameterizedItem;
class SessionModel;
class QtVariantProperty;
class QtProperty;

class BA_CORE_API_ ComponentEditor : public QWidget
{
    Q_OBJECT
public:
    ComponentEditor(QWidget *parent = 0);
    ~ComponentEditor();

    void setItem(ParameterizedItem *item);
//    void addItemProperty(ParameterizedItem *item, const QString &name);

    void updateEditor(ParameterizedItem *item, QtVariantProperty *parentProperty = 0);

    void clearEditor();

    void setPresentationType(ComponentEditorFlags::PresentationType presentationType);

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
};


#endif
