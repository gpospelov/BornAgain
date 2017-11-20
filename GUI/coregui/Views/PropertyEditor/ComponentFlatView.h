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

#include "WinDllMacros.h"
#include <QWidget>

class SessionItem;
class QGridLayout;
class QBoxLayout;
class PropertyWidgetItem;

//! Component property widget for SessionItems. On the contrary to ComponentTreeView
//! properties are presented as widgets in grid layout.
//! Shows only PropertyItems and current items of GroupProperties.

class BA_CORE_API_ ComponentFlatView : public QWidget
{
    Q_OBJECT
public:
    ComponentFlatView(QWidget* parent = nullptr);

    void addItemProperties(SessionItem* item);

private:
    void clearLayout();
    void initGridLayout();
    PropertyWidgetItem* createWidget(SessionItem* item);

    QBoxLayout* m_mainLayout;
    QGridLayout* m_gridLayout;
    QVector<PropertyWidgetItem*> m_widgetItems;
};

#endif
