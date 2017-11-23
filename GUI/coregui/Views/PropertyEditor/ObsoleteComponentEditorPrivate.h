// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ObsoleteComponentEditorPrivate.h
//! @brief     Defines class ObsoleteComponentEditorPrivate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETECOMPONENTEDITORPRIVATE_H
#define OBSOLETECOMPONENTEDITORPRIVATE_H

#include "ObsoleteComponentEditorFlags.h"
#include "ObsoletePropertyVariantFactory.h"
#include "ObsoletePropertyVariantManager.h"
#include "SessionItem.h"
#include "WinDllMacros.h"
#include "qtbuttonpropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qttreepropertybrowser.h"
#include <QMap>
#include <memory>

class WheelEventEater;

//! Holds logic for ComponentEditor

class BA_CORE_API_ ObsoleteComponentEditorPrivate
{
public:
    ObsoleteComponentEditorPrivate(ObsoleteComponentEditorFlags::PresentationType flags
                           = ObsoleteComponentEditorFlags::BROWSER_TABLE,
                           QWidget *parent = 0);


    ~ObsoleteComponentEditorPrivate();

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
                                  SessionItem* item);
    void cleanChildren(SessionItem *item);

    void install_custom_filters();

    QtAbstractPropertyBrowser *m_browser;
    QtVariantPropertyManager *m_manager;
    QtVariantPropertyManager *m_read_only_manager;
    ObsoletePropertyVariantFactory *m_propertyFactory;

    QMap<QtProperty *, SessionItem *> m_qtproperty_to_item;
    QMap<SessionItem *, QtVariantProperty *> m_item_to_qtvariantproperty;
    QMap<QString, QtVariantProperty *> m_groupname_to_qtvariant;
    QMap<SessionItem *, QtVariantProperty *> m_item_to_qtparent;
    QMap<SessionItem *, ObsoleteComponentEditorFlags::InsertMode> m_item_to_insert_mode;

    ObsoleteComponentEditorFlags::PresentationType m_presentationType;
    QList<SessionItem *> m_changedItems;
    std::unique_ptr<WheelEventEater> m_wheel_event_filter;
    SessionItem *m_topItem;
};

#endif // OBSOLETECOMPONENTEDITORPRIVATE_H
