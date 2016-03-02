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
#include <QString>
#include <QDebug>

ComponentEditorPrivate::ComponentEditorPrivate(ComponentEditorFlags::PresentationType flags, QWidget *parent)
    : m_browser(0), m_manager(0), m_read_only_manager(0),
      m_propertyFactory(new PropertyVariantFactory(parent)),
      m_presentationType(flags)
{
    m_read_only_manager = new PropertyVariantManager(parent);
    m_manager = new PropertyVariantManager(parent);
    init_browser();
}

void ComponentEditorPrivate::clear()
{
    m_browser->clear();

    QMap<QtProperty *, ParameterizedItem *>::iterator it = m_qtproperty_to_item.begin();
    while (it != m_qtproperty_to_item.end()) {
        delete it.key();
        it++;
    }

    m_qtproperty_to_item.clear();
    m_item_to_qtvariantproperty.clear();
    m_qtvariant_to_dependend.clear();
    m_groupname_to_qtvariant.clear();

}

void ComponentEditorPrivate::setPresentationType(
    ComponentEditorFlags::PresentationType presentationType)
{
    clear();
    m_presentationType = presentationType;
    init_browser();
}

void ComponentEditorPrivate::init_browser()
{
    delete m_browser;
    m_browser = 0;

    if (m_presentationType & ComponentEditorFlags::BROWSER_TABLE) {
        QtTreePropertyBrowser *browser = new QtTreePropertyBrowser;
        browser->setResizeMode(QtTreePropertyBrowser::Interactive);
        browser->setRootIsDecorated(false);
        m_browser = browser;
    }

    else if (m_presentationType & ComponentEditorFlags::BROWSER_GROUPBOX) {
        m_browser = new QtGroupBoxPropertyBrowser;
    }

    else if (m_presentationType & ComponentEditorFlags::BROWSER_BUTTON) {
        m_browser = new QtButtonPropertyBrowser;
    } else {
        throw GUIHelpers::Error(
            "ComponentEditorPrivate::init_browser() -> Error. Unknown browser type.");
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

bool ComponentEditorPrivate::isFlat() const
{
    return m_presentationType & ComponentEditorFlags::SHOW_FLAT;
}

//! Creates, if necessary, qtVariantProperty for given item and place it in the editor
QtVariantProperty *ComponentEditorPrivate::
    processPropertyForItem(ParameterizedItem *item, QtVariantProperty *parentProperty)
{
    QtVariantProperty *itemProperty = getPropertyForItem(item);
    if (!itemProperty) {
        itemProperty = createQtVariantProperty(item);
        if (itemProperty) {
            m_qtproperty_to_item[itemProperty] = item;
            m_item_to_qtvariantproperty[item] = itemProperty;
        }

        if (itemProperty) {
//            if(!parentProperty) {
//                parentProperty = getPropertyForItem(item->parent());
//            }

            if (parentProperty) {
//                insertQtVariantProperty(itemProperty, parentProperty);
                parentProperty->addSubProperty(itemProperty);
                m_qtvariant_to_dependend[parentProperty].append(itemProperty);
            } else {
                m_browser->addProperty(itemProperty);
            }
        }


    }


    return itemProperty;
}

void ComponentEditorPrivate::insertQtVariantProperty(QtVariantProperty *qtVariantItem, QtVariantProperty *parent_qtproperty)
{
    if(!isFlat()) {
        parent_qtproperty->addSubProperty(qtVariantItem);
        qDebug() << "      AwesomePropertyEditor::insertQtVariantProperty() -> adding " << qtVariantItem << " as subproperty of" << parent_qtproperty;
    }
    else {
        if(m_browser->items(parent_qtproperty).size() == 1) {
            // inserting qtVariantItem after parent property, so we need to know parent of parent
            QList<QtBrowserItem *> associated = m_browser->items(parent_qtproperty);
            if(associated.size()) {
                QtBrowserItem *parent_browser_item = associated.at(0)->parent();
                if(parent_browser_item) {
                    QtProperty *new_parent = parent_browser_item->property();
                    if(m_qtvariant_to_dependend[parent_qtproperty].size()) {
                        if(!new_parent->subProperties().contains(m_qtvariant_to_dependend[parent_qtproperty].back())) throw 1;
                        new_parent->insertSubProperty(qtVariantItem, m_qtvariant_to_dependend[parent_qtproperty].back());
                    } else {
                    new_parent->insertSubProperty(qtVariantItem, parent_qtproperty);
                    }
                } else {
                    //QtBrowserItem *browserItem = m_d->m_browser->insertProperty(qtVariantItem, parent_qtproperty);
                    QtBrowserItem *browserItem = m_browser->addProperty(qtVariantItem);
                    if(!browserItem) {
                        throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Failed while inserting property");
                    }
                }
            } else {
                throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Unexpected place");
            }
        } else {
            // our parent property is already at the top, so need to add into the browser
            QtBrowserItem *browserItem = m_browser->insertProperty(qtVariantItem, parent_qtproperty);
            if(!browserItem) {
                throw GUIHelpers::Error("AwesomePropertyEditor::insertQtVariantProperty() -> Failed while inserting property");
            }
        }
    }
}



//! Returns QtVariantProperty representing given item in ComponentEditor.
QtVariantProperty *ComponentEditorPrivate::getPropertyForItem(ParameterizedItem *item)
{
    if (m_item_to_qtvariantproperty.contains(item)) {
        return m_item_to_qtvariantproperty[item];
    }
    return nullptr;
}

//! Returns ParameterizedItem corresponding to QtVariantProperty representation
ParameterizedItem *ComponentEditorPrivate::getItemForProperty(QtProperty *property)
{
    if (m_qtproperty_to_item.contains(property)) {
        return m_qtproperty_to_item[property];
    }
    return nullptr;
}

//! creates QtVariantProperty for given ParameterizedItem's property
QtVariantProperty *ComponentEditorPrivate::createQtVariantProperty(ParameterizedItem *item)
{
    QtVariantProperty *result(0);

    QString property_name = item->itemName();
    QVariant prop_value = item->value();
    PropertyAttribute prop_attribute = item->getAttribute();

    if (!prop_value.isValid()) {
        result = m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), property_name);

    } else {
        int type = GUIHelpers::getVariantType(prop_value);

        QtVariantPropertyManager *manager = m_manager;
        if (prop_attribute.isReadOnly())
            manager = m_read_only_manager;

        if (!manager->isPropertyTypeSupported(type)) {
            throw GUIHelpers::Error(
                "ComponentEditor::createQtVariantProperty() -> Error. Not supported property type "
                + property_name);
        }

        result = manager->addProperty(type, property_name);
        result->setValue(prop_value);
    }

    updatePropertyAppearance(result, item->getAttribute());
    return result;
}

QtVariantProperty *ComponentEditorPrivate::processPropertyGroupForName(const QString &name)
{
    QtVariantProperty *result = getPropertyForGroupName(name);
    if(result == nullptr && name.size()) {
        result = m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), name);
        m_groupname_to_qtvariant[name] = result;
        m_browser->addProperty(result);
    }
    return result;
}

QtVariantProperty *ComponentEditorPrivate::getPropertyForGroupName(const QString &name)
{
    if (m_groupname_to_qtvariant.contains(name)) {
        return m_groupname_to_qtvariant[name];
    }
    return nullptr;
}

//! removes given qtVariantProperty from browser and all maps
void ComponentEditorPrivate::removeQtVariantProperty(QtVariantProperty *property)
{
    m_browser->removeProperty(property);
    delete property;
    auto it = m_qtproperty_to_item.find(property);
    if (it != m_qtproperty_to_item.end()) {
        ParameterizedItem *item = it.value();
        m_item_to_qtvariantproperty.remove(item);
        m_qtproperty_to_item.erase(it);
    }
}

//! update visual apperance of qtVariantProperty using ParameterizedItem's attribute
void ComponentEditorPrivate::updatePropertyAppearance(QtVariantProperty *property,
                                                      const PropertyAttribute &attribute)
{
    Q_ASSERT(property);

    QString toolTip = attribute.getToolTip();
    if (!toolTip.isEmpty())
        property->setToolTip(toolTip);

    if (attribute.isDisabled()) {
        property->setEnabled(false);
    } else {
        property->setEnabled(true);
    }

    QVariant prop_value = property->value();
    if (!prop_value.isValid())
        return;
    int type = GUIHelpers::getVariantType(prop_value);

    if (type == QVariant::Double) {
        AttLimits limits = attribute.getLimits();
        if (limits.hasLowerLimit())
            property->setAttribute(QStringLiteral("minimum"), limits.getLowerLimit());
        if (limits.hasUpperLimit())
            property->setAttribute(QStringLiteral("maximum"), limits.getUpperLimit());
        property->setAttribute(QStringLiteral("decimals"), attribute.getDecimals());
        property->setAttribute(QStringLiteral("singleStep"),
                               1. / std::pow(10., attribute.getDecimals() - 1));
    } else if (type == QVariant::Int) {
        AttLimits limits = attribute.getLimits();
        if (limits.hasLowerLimit())
            property->setAttribute(QStringLiteral("minimum"), int(limits.getLowerLimit()));
        if (limits.hasUpperLimit())
            property->setAttribute(QStringLiteral("maximum"), int(limits.getUpperLimit()));
    }
}
