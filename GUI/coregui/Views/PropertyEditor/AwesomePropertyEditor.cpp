// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/AwesomePropertyEditor.cpp
//! @brief     Implements class AwesomePropertyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "AwesomePropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "ParameterizedItem.h"
#include "tooltipdatabase.h"
#include "GUIHelpers.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include <QtProperty>
#include <QMetaProperty>
#include <QDebug>
#include <QVBoxLayout>
#include <cmath>


class AwesomePropertyEditorPrivate
{
public:
    struct ItemPropertyPair {
        ItemPropertyPair(ParameterizedItem *item=0, QString property_name = QString())
            : m_item(item), m_name(property_name) {}
        ParameterizedItem *m_item;
        QString m_name;
        friend bool operator <(const ItemPropertyPair& left, const ItemPropertyPair& right)
        {
            if(left.m_item == right.m_item)
                return left.m_name < right.m_name;
            return left.m_item < right.m_item;
        }
    };

    AwesomePropertyEditorPrivate(QWidget *parent, AwesomePropertyEditor::EBrowserType browser_type);
    QtAbstractPropertyBrowser *m_browser;
    QtVariantPropertyManager  *m_manager;
    QtVariantPropertyManager  *m_read_only_manager;
    AwesomePropertyEditor::EBrowserType m_browser_type;
    QMap<QtProperty *, ItemPropertyPair> m_qtproperty_to_itempropertypair;
    QMap<ParameterizedItem *, QMap<QString, QtVariantProperty *> > m_item_to_property_to_qtvariant;
    QMap<QString, QtVariantProperty *> m_groupname_to_qtvariant;
    bool m_recursive_flag;
};

AwesomePropertyEditorPrivate::AwesomePropertyEditorPrivate(QWidget *parent, AwesomePropertyEditor::EBrowserType browser_type)
    : m_browser(0)
    , m_manager(0)
    , m_read_only_manager(0)
    , m_browser_type(browser_type)
    , m_recursive_flag(true)
{
    if(m_browser_type == AwesomePropertyEditor::BROWSER_TREE_TYPE) {
        QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(parent);
        //browser->setResizeMode(QtTreePropertyBrowser::Stretch);
        browser->setRootIsDecorated(false);
        m_browser = browser;
    }
    else if(m_browser_type == AwesomePropertyEditor::BROWSER_GROUPBOX_TYPE) {
        m_browser = new QtGroupBoxPropertyBrowser(parent);
    }
    else if(m_browser_type == AwesomePropertyEditor::BROWSER_BUTTON_TYPE) {
        m_browser = new QtButtonPropertyBrowser(parent);
    }
    else {
        throw GUIHelpers::Error("UniversalPropertyEditor::UniversalPropertyEditor() -> Error. Unknown browser type.");
    }
    m_read_only_manager = new PropertyVariantManager(parent);

    m_manager = new PropertyVariantManager(parent);
    QtVariantEditorFactory *factory = new PropertyVariantFactory();
    m_browser->setFactoryForManager(m_manager, factory);

}


AwesomePropertyEditor::AwesomePropertyEditor(QWidget *parent, EBrowserType browser_type)
    : QWidget(parent)
    , m_d(new AwesomePropertyEditorPrivate(this, browser_type))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(256, 128);

    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("AwesomePropertyEditor"));

    m_d->m_browser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_d->m_browser);

    connect(m_d->m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

    setLayout(layout);
}

AwesomePropertyEditor::~AwesomePropertyEditor()
{
    delete m_d;
}

QSize AwesomePropertyEditor::sizeHint() const
{
    return m_d->m_browser->sizeHint();
}

QSize AwesomePropertyEditor::minimumSizeHint() const
{
    return m_d->m_browser->minimumSizeHint();
}

void AwesomePropertyEditor::addItemProperties(ParameterizedItem *item, QtProperty *parent_qtproperty)
{
    Q_ASSERT(item);
    qDebug() << "addItemProperties(ParameterizedItem *item, QtProperty *parent_qtproperty)" << item->modelType() << parent_qtproperty;
    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        addItemProperty(item, prop_name, parent_qtproperty);
    }
}

void AwesomePropertyEditor::addItemPropertiesToGroup(ParameterizedItem *item, const QString &group_name)
{
    QtVariantProperty *variantProperty(0);
    if(m_d->m_groupname_to_qtvariant.contains(group_name)) {
        variantProperty = m_d->m_groupname_to_qtvariant[group_name];
    } else {
        variantProperty = m_d->m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), group_name);
        m_d->m_groupname_to_qtvariant[group_name] = variantProperty;
        m_d->m_browser->addProperty(variantProperty);
    }
    addItemProperties(item, variantProperty);
}

//! add single ParameterizedItem property
void AwesomePropertyEditor::addItemProperty(ParameterizedItem *item, const QString &property_name, QtProperty *parent_qtproperty)
{
    Q_ASSERT(item);
    qDebug() << "AwesomePropertyEditor::addItemProperty(ParameterizedItem *item, const QString &property_name)" << item->modelType() << property_name;

    PropertyAttribute prop_attribute = item->getPropertyAttribute(property_name);
    if(prop_attribute.getAppearance() & PropertyAttribute::HIDDEN) return;

    QVariant prop_value = item->property(property_name.toUtf8().data());
    Q_ASSERT(prop_value.isValid());
    int type = GUIHelpers::getVariantType(prop_value);

    QtVariantPropertyManager *manager = m_d->m_manager;
    if(prop_attribute.getAppearance() & PropertyAttribute::READONLY) manager = m_d->m_read_only_manager;

    QtVariantProperty *subProperty = 0;
    if(manager->isPropertyTypeSupported(type)) {
        if(prop_attribute.getLabel().isEmpty()) {
            subProperty = manager->addProperty(type, property_name);
        } else {
            subProperty = manager->addProperty(type, prop_attribute.getLabel());
        }

        if(type == QVariant::Double) {
            subProperty->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
            AttLimits limits = prop_attribute.getLimits();
            if(limits.hasLowerLimit()) subProperty->setAttribute(QLatin1String("minimum"), limits.getLowerLimit());
            if(limits.hasUpperLimit()) subProperty->setAttribute(QLatin1String("maximum"), limits.getUpperLimit());
            subProperty->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
            subProperty->setAttribute(QLatin1String("singleStep"), 1./std::pow(10.,prop_attribute.getDecimals()-1));
        }

        QString toolTip = ToolTipDataBase::getSampleViewToolTip(item->modelType(), property_name);
        if(!toolTip.isEmpty()) subProperty->setToolTip(toolTip);

        if(prop_attribute.getAppearance() & PropertyAttribute::DISABLED) {
            subProperty->setEnabled(false);
        }

        subProperty->setValue(prop_value);

        // adding property to parent property/manager
        if(parent_qtproperty) {
            parent_qtproperty->addSubProperty(subProperty);
        } else {
            m_d->m_browser->addProperty(subProperty);
        }

    } else {
        subProperty = m_d->m_read_only_manager->addProperty(QVariant::String,
                                                     property_name);
        subProperty->setValue(QLatin1String("< Unknown Type >"));
        subProperty->setEnabled(false);
    }

    // additing properties of SubItem
    if(m_d->m_recursive_flag && item->getSubItems().contains(property_name)) {
        ParameterizedItem *subitem = item->getSubItems()[property_name];
        if (subitem) {
            addItemProperties(subitem, subProperty);
        }
    }

    // configuring PropertyEditor
    AwesomePropertyEditorPrivate::ItemPropertyPair itemPropertyPair(item, property_name);
    m_d->m_qtproperty_to_itempropertypair[subProperty] = itemPropertyPair;
    m_d->m_item_to_property_to_qtvariant[item][property_name] = subProperty;
    connect(item, SIGNAL(propertyChanged(QString)),
           this, SLOT(onPropertyChanged(QString)), Qt::UniqueConnection);
    connect(item, SIGNAL(propertyItemChanged(QString)),
            this, SLOT(onPropertyItemChanged(QString)), Qt::UniqueConnection);
}

//! add single ParameterizedItem property to group
void AwesomePropertyEditor::addItemPropertyToGroup(ParameterizedItem *item, const QString &property_name, const QString &group_name)
{
    qDebug() << "AwesomePropertyEditor::addItemPropertyToGroup() BROWSER_ID" << m_d->m_browser_type << "group_name" << group_name;
    QtVariantProperty *variantProperty(0);
    if(m_d->m_groupname_to_qtvariant.contains(group_name)) {
        variantProperty = m_d->m_groupname_to_qtvariant[group_name];
    } else {
        variantProperty = m_d->m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), group_name);
        m_d->m_groupname_to_qtvariant[group_name] = variantProperty;
        m_d->m_browser->addProperty(variantProperty);
    }
    addItemProperty(item, property_name, variantProperty);
}

void AwesomePropertyEditor::setRecursive(bool recursive_flag)
{
    m_d->m_recursive_flag = recursive_flag;
}

void AwesomePropertyEditor::clearEditor()
{
    qDebug() << "AwesomePropertyEditor::clearEditor()";
    disconnect(m_d->m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));
    disconnect();

//    QListIterator<QtProperty *> it(m_d->m_browser->properties());
//    while (it.hasNext()) {
//        m_d->m_browser->removeProperty(it.next());
//    }

    m_d->m_browser->clear();

    QMap<QtProperty *, AwesomePropertyEditorPrivate::ItemPropertyPair>::iterator it = m_d->m_qtproperty_to_itempropertypair.begin();
    while(it!=m_d->m_qtproperty_to_itempropertypair.end()) {
        //m_d->m_browser->removeProperty(it.key());
        delete it.key();
        it++;
    }

    m_d->m_qtproperty_to_itempropertypair.clear();
    m_d->m_item_to_property_to_qtvariant.clear();
    m_d->m_groupname_to_qtvariant.clear();

    connect(m_d->m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

}

//! updates corresponding property of ParameterizedItem on editor change
void AwesomePropertyEditor::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "AwesomePropertyEditor::slotValueChanged() BROWSER_ID:" << m_d->m_browser_type << "property:" << property->propertyName() << "value:" << value;

    if (!m_d->m_qtproperty_to_itempropertypair.contains(property)) {
        qDebug() << "    AwesomePropertyEditor::slotValueChanged()    -> No such property";
        return;
    }

    AwesomePropertyEditorPrivate::ItemPropertyPair itemPropertyPair = m_d->m_qtproperty_to_itempropertypair[property];
    qDebug() << "    AwesomePropertyEditor::slotValueChanged()-> itemPropertyPair" << itemPropertyPair.m_item << itemPropertyPair.m_name;
    itemPropertyPair.m_item->setProperty(itemPropertyPair.m_name.toUtf8().data(), value);
}

//! updates editors on ParameterizedItem's propertyChanged
void AwesomePropertyEditor::onPropertyChanged(const QString &property_name)
{
    ParameterizedItem *item = qobject_cast<ParameterizedItem *>(sender());
    qDebug() << "AwesomePropertyEditor::onPropertyChanged(const QString &property_name) BROWSER_ID:" << m_d->m_browser_type << "item->modelType(), property_name" << item->modelType() << property_name;

    QtVariantProperty *variant_property = m_d->m_item_to_property_to_qtvariant[item][property_name];
    if(variant_property) {
        QVariant property_value = item->property(property_name.toUtf8().data());

        disconnect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        disconnect(item, SIGNAL(propertyItemChanged(QString)),
                this, SLOT(onPropertyItemChanged(QString)));

        variant_property->setValue(property_value);
        PropertyAttribute prop_attribute = item->getPropertyAttribute(property_name);
        if(prop_attribute.getAppearance() & PropertyAttribute::DISABLED) {
            variant_property->setEnabled(false);
        } else {
            variant_property->setEnabled(true);
        }


        connect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)), Qt::UniqueConnection);
        connect(item, SIGNAL(propertyItemChanged(QString)),
                this, SLOT(onPropertyItemChanged(QString)), Qt::UniqueConnection);

    } else {
        Q_ASSERT(0);
    }
}

void AwesomePropertyEditor::onPropertyItemChanged(const QString &property_name)
{
    ParameterizedItem *item = qobject_cast<ParameterizedItem *>(sender());
    qDebug() << "AwesomePropertyEditor::onPropertyItemChanged(const QString &property_name) BROWSER_ID:" << m_d->m_browser_type << "item->modelType(), property_name" << item->modelType() << property_name;

    QtVariantProperty *variant_property = m_d->m_item_to_property_to_qtvariant[item][property_name];
    if(variant_property) {
        QVariant property_value = item->property(property_name.toUtf8().data());

        disconnect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        disconnect(item, SIGNAL(propertyItemChanged(QString)),
                this, SLOT(onPropertyItemChanged(QString)));

        variant_property->setValue(property_value);
        PropertyAttribute prop_attribute = item->getPropertyAttribute(property_name);
        if(prop_attribute.getAppearance() & PropertyAttribute::DISABLED) {
            variant_property->setEnabled(false);
        } else {
            variant_property->setEnabled(true);
        }

        removeSubProperties(variant_property);

        if(m_d->m_recursive_flag) addItemProperties( item->getSubItems()[property_name], variant_property);

        connect(item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        connect(item, SIGNAL(propertyItemChanged(QString)),
                this, SLOT(onPropertyItemChanged(QString)));
    }
}

//!
void AwesomePropertyEditor::removeSubProperties(QtProperty *property)
{
    qDebug() << "AwesomePropertyEditor::removeSubProperties" << property << property->propertyName();
    QList<QtProperty *> properties = property->subProperties();
    foreach(QtProperty *child, properties) {
        m_d->m_browser->removeProperty(child);
        delete child;

        QMap<QtProperty *, AwesomePropertyEditorPrivate::ItemPropertyPair >::iterator it = m_d->m_qtproperty_to_itempropertypair.find(child);
        if(it != m_d->m_qtproperty_to_itempropertypair.end()) {
            AwesomePropertyEditorPrivate::ItemPropertyPair itemPair = it.value();
            m_d->m_item_to_property_to_qtvariant.remove(itemPair.m_item);
            m_d->m_qtproperty_to_itempropertypair.erase(it);
        }
    }
}

