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
};

AwesomePropertyEditorPrivate::AwesomePropertyEditorPrivate(QWidget *parent, AwesomePropertyEditor::EBrowserType browser_type)
    : m_browser(0)
    , m_manager(0)
    , m_read_only_manager(0)
    , m_browser_type(browser_type)
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
    qDebug() << "AwesomePropertyEditor::addItemProperty(ParameterizedItem *item, const QString &property_name)" << item->modelType();
    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        addItemProperty(item, prop_name, parent_qtproperty);
    }
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
    subProperty = manager->addProperty(type, property_name);
    subProperty->setValue(prop_value);

    if(parent_qtproperty) {
        parent_qtproperty->addSubProperty(subProperty);
    } else {
        m_d->m_browser->addProperty(subProperty);
    }

    if (item->getSubItems().contains(property_name)) {
        ParameterizedItem *subitem = item->getSubItems()[property_name];
        if (subitem) {
            addItemProperties(subitem, subProperty);
        }
    }

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

//! updates corresponding property of ParameterizedItem on editor change
void AwesomePropertyEditor::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "AwesomePropertyEditor::slotValueChanged() BROWSER_ID:" << m_d->m_browser_type << "value:" << value;

    if (!m_d->m_qtproperty_to_itempropertypair.contains(property))
        return;

    AwesomePropertyEditorPrivate::ItemPropertyPair itemPropertyPair = m_d->m_qtproperty_to_itempropertypair[property];
    qDebug() << itemPropertyPair.m_item << itemPropertyPair.m_name;
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
        removeSubProperties(variant_property);
        addItemProperties( item->getSubItems()[property_name], variant_property);
    }
}


void AwesomePropertyEditor::removeSubProperties(QtProperty *property)
{
    qDebug() << "AwesomePropertyEditor::removeSubProperties" << property->propertyName();
    QList<QtProperty *> properties = property->subProperties();
    foreach(QtProperty *child, properties) {
        m_d->m_browser->removeProperty(child);
        delete child;

        QMap<QtProperty *, AwesomePropertyEditorPrivate::ItemPropertyPair >::iterator it = m_d->m_qtproperty_to_itempropertypair.find(child);
        if(it != m_d->m_qtproperty_to_itempropertypair.end()) {
            AwesomePropertyEditorPrivate::ItemPropertyPair itemPair = it.value();
            m_d->m_qtproperty_to_itempropertypair.erase(it);
        }
    }
}

