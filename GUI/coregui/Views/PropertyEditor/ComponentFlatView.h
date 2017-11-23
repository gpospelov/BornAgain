// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentFlatView.h
//! @brief     Defines class ComponentFlatView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTFLATVIEW_H
#define COMPONENTFLATVIEW_H

#include "ComponentView.h"
#include <memory>

class SessionItem;
class SessionModel;
class QGridLayout;
class QBoxLayout;
class PropertyWidgetItem;
class WheelEventEater;

//! Component property widget for SessionItems. On the contrary to ComponentTreeView
//! properties are presented as widgets in grid layout.
//! Shows only PropertyItems and current items of GroupProperties.

class BA_CORE_API_ ComponentFlatView : public ComponentView
{
    Q_OBJECT
public:
    ComponentFlatView(QWidget* parent = nullptr);

    void setItem(SessionItem* item);
    void addItemProperties(SessionItem* item);

    void setModel(SessionModel* model);

    void clearEditor();

    void setShowChildren(bool show);

public slots:
    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                       const QVector<int> &roles);

private:
    void updateItemProperties(SessionItem* item);
    void updateItemRoles(SessionItem* item);
    void initGridLayout();
    PropertyWidgetItem* createWidget(const SessionItem* item);

    QBoxLayout* m_mainLayout;
    QGridLayout* m_gridLayout;
    QVector<PropertyWidgetItem*> m_widgetItems;
    SessionItem* m_currentItem;
    SessionModel* m_model;
    bool m_show_children;
    std::unique_ptr<WheelEventEater> m_wheel_event_filter;
};

#endif
