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

    void addItem(ParameterizedItem *item);

public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);


private slots:
    void onQtPropertyChanged(QtProperty *, const QVariant &value);

private:
    QtVariantProperty *createQtVariantProperty(ParameterizedItem *item);
    void disconnectModel(SessionModel *model);
    void connectModel(SessionModel *model);
    void disconnectManager();
    void connectManager();



    std::unique_ptr<ComponentEditorPrivate> m_d;

};

#endif
