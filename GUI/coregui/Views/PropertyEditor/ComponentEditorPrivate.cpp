// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditorPrivate.cpp
//! @brief     Implements class ComponentEditorPrivate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ComponentEditorPrivate.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include "ParameterizedItem.h"
#include "GUIHelpers.h"
#include <QDebug>


ComponentEditorPrivate::ComponentEditorPrivate(QWidget *parent)
    : m_browser(0)
    , m_manager(0)
    , m_read_only_manager(0)
    , m_propertyFactory(new PropertyVariantFactory(parent))
    , m_presentationType(ComponentEditorFlags::SHOW_CONDENSED | ComponentEditorFlags::BROWSER_TABLE)
{
    m_read_only_manager = new PropertyVariantManager(parent);
    m_manager = new PropertyVariantManager(parent);
    init_browser();
}

void ComponentEditorPrivate::clear()
{
    m_browser->clear();

    QMap<QtProperty *, ParameterizedItem *>::iterator it = m_qtproperty_to_item.begin();
    while(it!=m_qtproperty_to_item.end()) {
        delete it.key();
        it++;
    }

    m_qtproperty_to_item.clear();
    m_item_to_qtvariantproperty.clear();

}

void ComponentEditorPrivate::setPresentationType(ComponentEditorFlags::PresentationType presentationType)
{
    clear();
    m_presentationType = presentationType;
    init_browser();
}

void ComponentEditorPrivate::init_browser()
{
    delete m_browser;
    m_browser = 0;

    if(m_presentationType & ComponentEditorFlags::BROWSER_TABLE) {
        QtTreePropertyBrowser *browser = new QtTreePropertyBrowser;
        browser->setResizeMode(QtTreePropertyBrowser::Interactive);
        browser->setRootIsDecorated(false);
        m_browser = browser;
    }

    else if(m_presentationType & ComponentEditorFlags::BROWSER_GROUPBOX) {
        m_browser = new QtGroupBoxPropertyBrowser;
    }

    else if(m_presentationType & ComponentEditorFlags::BROWSER_BUTTON) {
        m_browser = new QtButtonPropertyBrowser;
    }
    else {
        throw GUIHelpers::Error("ComponentEditorPrivate::init_browser() -> Error. Unknown browser type.");
    }
    m_browser->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_browser->setFactoryForManager(m_manager, m_propertyFactory);
}

bool ComponentEditorPrivate::isShowDetailed() const
{
    return m_presentationType & ComponentEditorFlags::SHOW_DETAILED;
}

bool ComponentEditorPrivate::isShowCondensed() const
{
    return m_presentationType & ComponentEditorFlags::SHOW_CONDENSED;
}

QtVariantProperty *ComponentEditorPrivate::processPropertyForItem(ParameterizedItem *item, QtVariantProperty *parentProperty)
{
    QtVariantProperty *childProperty = getPropertyForItem(item);
    if(childProperty) {
        if(parentProperty) {
            parentProperty->addSubProperty(childProperty);
        } else {
            m_browser->addProperty(childProperty);
        }
    }
    return childProperty;
}

//! Returns QtVariantProperty representing given item in ComponentEditor.
//! If QtVariantProperty doesn't exist yet, it will be created.
QtVariantProperty *ComponentEditorPrivate::getPropertyForItem(ParameterizedItem *item)
{
    if(m_item_to_qtvariantproperty.contains(item)) {
        return m_item_to_qtvariantproperty[item];
    }

    QtVariantProperty *result = createQtVariantProperty(item);
    if(result) {
        m_qtproperty_to_item[result] = item;
        m_item_to_qtvariantproperty[item] = result;
    }

    return result;
}


//! creates QtVariantProperty for given ParameterizedItem's property
QtVariantProperty *ComponentEditorPrivate::createQtVariantProperty(ParameterizedItem *item)
{
    QtVariantProperty *result(0);

    QString property_name = item->itemName();
    QVariant prop_value = item->value();
    qDebug() << "QtVariantProperty *ComponentEditor::createQtVariantProperty(ParameterizedItem) item" << item << property_name << prop_value;

    if (!prop_value.isValid()) {
        return m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), property_name);
//        return nullptr;
    }
    int type = GUIHelpers::getVariantType(prop_value);

    QtVariantPropertyManager *manager = m_manager;

    if(!manager->isPropertyTypeSupported(type)) {
        throw GUIHelpers::Error("ComponentEditor::createQtVariantProperty() -> Error. Not supported property type "+property_name);
    }

    result = manager->addProperty(type, property_name);
    result->setValue(prop_value);

    return result;
}


