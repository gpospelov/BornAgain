// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditorPrivate.h
//! @brief     Declares class ComponentEditorPrivate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITORPRIVATE_H
#define COMPONENTEDITORPRIVATE_H

#include "WinDllMacros.h"
#include "ComponentEditorFlags.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "SessionItem.h"
#include "PropertyAttribute.h"
#include <QMap>
#include <memory>

class WheelEventEater;

//! Holds logic for ComponentEditor

class BA_CORE_API_ ComponentEditorPrivate
{
public:
    ComponentEditorPrivate(ComponentEditorFlags::PresentationType flags
                           = ComponentEditorFlags::BROWSER_TABLE,
                           QWidget *parent = 0);


    ~ComponentEditorPrivate();

    void clear();
    void init_browser();

    QtVariantProperty *
    processPropertyForItem(SessionItem *item,
                           QtVariantProperty *parentProperty);
    QtVariantProperty *getPropertyForItem(SessionItem *item);
    SessionItem *getItemForProperty(QtProperty *property);
    QtVariantProperty *createQtVariantProperty(SessionItem *item);

    QtVariantProperty *processPropertyGroupForName(const QString &name);
    QtVariantProperty *getPropertyForGroupName(const QString &name);

    void removeQtVariantProperty(QtVariantProperty *property);
    void updatePropertyAppearance(QtVariantProperty *property,
                                  const PropertyAttribute &attribute);
    void cleanChildren(SessionItem *item);

    void install_custom_filters();

    QtAbstractPropertyBrowser *m_browser;
    QtVariantPropertyManager *m_manager;
    QtVariantPropertyManager *m_read_only_manager;
    PropertyVariantFactory *m_propertyFactory;

    QMap<QtProperty *, SessionItem *> m_qtproperty_to_item;
    QMap<SessionItem *, QtVariantProperty *> m_item_to_qtvariantproperty;
    QMap<QString, QtVariantProperty *> m_groupname_to_qtvariant;
    QMap<SessionItem *, QtVariantProperty *> m_item_to_qtparent;
    QMap<SessionItem *, ComponentEditorFlags::InsertMode> m_item_to_insert_mode;

    ComponentEditorFlags::PresentationType m_presentationType;
    QList<SessionItem *> m_changedItems;
    std::unique_ptr<WheelEventEater> m_wheel_event_filter;
};

#endif
