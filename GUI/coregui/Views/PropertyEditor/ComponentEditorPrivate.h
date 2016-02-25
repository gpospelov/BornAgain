// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditorPrivate.h
//! @brief     Defines class ComponentEditorPrivate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPONENTEDITORPRIVATE_H
#define COMPONENTEDITORPRIVATE_H

#include "WinDllMacros.h"
#include "ComponentEditorFlags.h"
#include <QMap>
#include <memory>

class ComponentEditorPrivate;
class QWidget;
class QtAbstractPropertyBrowser;
class QtVariantPropertyManager;
class PropertyVariantFactory;
class QtProperty;
class ParameterizedItem;
class QtVariantProperty;

class BA_CORE_API_ ComponentEditorPrivate
{
public:
    ComponentEditorPrivate(QWidget *parent);
    void clear();
    void setPresentationType(ComponentEditorFlags::PresentationType presentationType);
    void init_browser();

    bool isShowDetailed() const;
    bool isShowCondensed() const;

    QtVariantProperty *processPropertyForItem(ParameterizedItem *item, QtVariantProperty *parentProperty);

    QtVariantProperty *getPropertyForItem(ParameterizedItem *item);
    QtVariantProperty *createQtVariantProperty(ParameterizedItem *item);
    void removeQtVariantProperty(QtVariantProperty *property);


    QtAbstractPropertyBrowser *m_browser;
    QtVariantPropertyManager  *m_manager;
    QtVariantPropertyManager  *m_read_only_manager;
    PropertyVariantFactory *m_propertyFactory;

    QMap<QtProperty *, ParameterizedItem *> m_qtproperty_to_item;
    QMap<ParameterizedItem *, QtVariantProperty *> m_item_to_qtvariantproperty;

    ComponentEditorFlags::PresentationType m_presentationType;
};


#endif
