// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/ComponentEditorPrivate.cpp
//! @brief     Implements class ComponentEditorPrivate
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ComponentEditorPrivate.h"
#include "GUIHelpers.h"
#include "CustomEventFilters.h"
#include <QString>
#include <QComboBox>
#include <QDebug>

ComponentEditorPrivate::ComponentEditorPrivate(ComponentEditorFlags::PresentationType flags, QWidget *parent)
    : m_browser(0), m_manager(0), m_read_only_manager(0)
    , m_propertyFactory(new PropertyVariantFactory(parent))
    , m_presentationType(flags)
    , m_wheel_event_filter(new WheelEventEater)
{
    m_read_only_manager = new PropertyVariantManager(parent);
    m_manager = new PropertyVariantManager(parent);
    init_browser();
}

ComponentEditorPrivate::~ComponentEditorPrivate()
{
    clear();
}

void ComponentEditorPrivate::clear()
{
    m_browser->clear();

    auto it = m_qtproperty_to_item.begin();
    while (it != m_qtproperty_to_item.end()) {
        delete it.key();
        it++;
    }

    m_qtproperty_to_item.clear();
    m_item_to_qtvariantproperty.clear();
    m_groupname_to_qtvariant.clear();
    m_item_to_qtparent.clear();
    m_item_to_insert_mode.clear();
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
            "ComponentEditorPrivate::init_browser() -> Error. "
            "Unknown browser type.");
    }

    m_browser->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_browser->setFactoryForManager(m_manager, m_propertyFactory);
}

//! Creates, if necessary, qtVariantProperty for given item and place it in the editor
QtVariantProperty *ComponentEditorPrivate::
    processPropertyForItem(SessionItem *item, QtVariantProperty *parentProperty)
{
    QtVariantProperty *itemProperty = getPropertyForItem(item);
    if (!itemProperty) {
        itemProperty = createQtVariantProperty(item);
        if (itemProperty) {
            m_qtproperty_to_item[itemProperty] = item;
            m_item_to_qtvariantproperty[item] = itemProperty;
        }

        if (itemProperty) {
            if (parentProperty) {
                parentProperty->addSubProperty(itemProperty);
                m_item_to_qtparent[item] = parentProperty;
            } else {
                m_browser->addProperty(itemProperty);
            }
        }
    }

    install_custom_filters();

    return itemProperty;
}

//! Returns QtVariantProperty representing given item in ComponentEditor.
QtVariantProperty *ComponentEditorPrivate::getPropertyForItem(SessionItem *item)
{
    if (m_item_to_qtvariantproperty.contains(item)) {
        return m_item_to_qtvariantproperty[item];
    }
    return nullptr;
}

//! Returns SessionItem corresponding to QtVariantProperty representation
SessionItem *ComponentEditorPrivate::getItemForProperty(QtProperty *property)
{
    if (m_qtproperty_to_item.contains(property)) {
        return m_qtproperty_to_item[property];
    }
    return nullptr;
}

//! creates QtVariantProperty for given SessionItem's property
QtVariantProperty *ComponentEditorPrivate::createQtVariantProperty(SessionItem *item)
{
    QtVariantProperty *result(0);

    QString property_name = item->itemName();
    QVariant prop_value = item->value();
    PropertyAttribute prop_attribute = PropertyAttribute::fromItem(item);

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

    updatePropertyAppearance(result, PropertyAttribute::fromItem(item));
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
        SessionItem *item = it.value();
        m_item_to_qtvariantproperty.remove(item);
        m_item_to_qtparent.remove(item);
        m_item_to_insert_mode.remove(item);
        m_qtproperty_to_item.erase(it);
    }
}

//! update visual apperance of qtVariantProperty using SessionItem's attribute
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

//! removes properties of all child items
void ComponentEditorPrivate::cleanChildren(SessionItem *item)
{
    foreach(SessionItem *child, item->childItems()) {
        if (QtVariantProperty *property = getPropertyForItem(child)) {
            removeQtVariantProperty(property);
        }
        cleanChildren(child);
    }
}

//! installs WheelEventEater on all comboxes
// hack to change behaviour of ComboBoxes and SpinBoxes produced by QtGroupBoxPropertyBrowser
// with the goal to react on mouse wheel event only when there is keyboard focus
void ComponentEditorPrivate::install_custom_filters()
{
    if(m_presentationType & ComponentEditorFlags::BROWSER_GROUPBOX) {
        QList<QAbstractSpinBox*> spinboxes = m_browser->findChildren<QAbstractSpinBox *>();
        QList<QComboBox*> comboboxes = m_browser->findChildren<QComboBox *>();
        foreach(QAbstractSpinBox *w, spinboxes) {
            w->removeEventFilter(m_wheel_event_filter.get());
            w->installEventFilter(m_wheel_event_filter.get());
            w->setFocusPolicy(Qt::StrongFocus);
        }
        foreach(QComboBox *w, comboboxes) {
            w->removeEventFilter(m_wheel_event_filter.get());
            w->installEventFilter(m_wheel_event_filter.get());
        }
    }
}
