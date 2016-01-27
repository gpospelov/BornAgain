// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PropertyEditor/UniversalPropertyEditor.cpp
//! @brief     Implements class UniversalPropertyEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "UniversalPropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "ParameterizedItem.h"
#include "tooltipdatabase.h"
#include "GUIHelpers.h"
#include "qttreepropertybrowser.h"
#include "qtgroupboxpropertybrowser.h"
#include "qtbuttonpropertybrowser.h"
#include <QtProperty>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QMetaProperty>
#include <QDebug>
#include <cmath>

UniversalPropertyEditor::UniversalPropertyEditor(QItemSelectionModel *selection_model,
                                           QWidget *parent, EBrowserType browser_type)
    : QWidget(parent)
    , m_item(0)
    , m_selection_model(0)
    , m_browser(0)
    , m_create_group_property(true)
    , m_browser_type(browser_type)
{
    setSelectionModel(selection_model);

    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("PropertyEditor"));

    if(m_browser_type == BROWSER_TREE_TYPE) {
        QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(this);
        browser->setRootIsDecorated(false);
        m_browser = browser;
    }
    else if(m_browser_type == BROWSER_GROUPBOX_TYPE) {
        m_browser = new QtGroupBoxPropertyBrowser();
    }
    else if(m_browser_type == BROWSER_BUTTON_TYPE) {
        m_browser = new QtButtonPropertyBrowser();
    }
    else {
        throw GUIHelpers::Error("UniversalPropertyEditor::UniversalPropertyEditor() -> Error. Unknown browser type.");
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);

    m_read_only_manager = new PropertyVariantManager(this);

    m_manager = new PropertyVariantManager(this);

    QtVariantEditorFactory *factory = new PropertyVariantFactory();
    m_browser->setFactoryForManager(m_manager, factory);

    connect(m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

}

void UniversalPropertyEditor::setSelectionModel(QItemSelectionModel *selection_model)
{
    if(selection_model != m_selection_model) {
        if(m_selection_model)
            disconnect(m_selection_model,
                    SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this,
                    SLOT(selectionChanged(QItemSelection,QItemSelection)) );

        m_selection_model = selection_model;
        connect(m_selection_model,
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,
                SLOT(selectionChanged(QItemSelection,QItemSelection)) );

    }
}

// show property of currently selected object (triggered by the graphics scene)
// if more than one object is selected, show only last selected
void UniversalPropertyEditor::selectionChanged(const QItemSelection & selected,
                                            const QItemSelection & deselected)
{
    (void)deselected;
    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        ParameterizedItem *item = static_cast<ParameterizedItem *>(
                indices.back().internalPointer());
        setItem(item);
    } else {
        setItem(0);
    }
}


void UniversalPropertyEditor::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "UniversalPropertyEditor::slotValueChanged()" << value;
    if (!m_property_to_item_index_pair.contains(property))
        return;

    ItemIndexPair item_index_pair =
            m_property_to_item_index_pair.value(property);

    if (item_index_pair.m_item) {
        QList<QByteArray> prop_list =
                item_index_pair.m_item->dynamicPropertyNames();
        if (item_index_pair.m_index > prop_list.length()) {
            return;
        }
        qDebug() << "UniversalPropertyEditor::slotValueChanged() -> setting ..." << prop_list[item_index_pair.m_index].constData();
        item_index_pair.m_item->setProperty(
            prop_list[item_index_pair.m_index].constData(), value);
    }
}


void UniversalPropertyEditor::clearEditor()
{
    qDebug() << "UniversalPropertyEditor::clearEditor()";

    QListIterator<QtProperty *> it(m_browser->properties());
    while (it.hasNext()) {
        m_browser->removeProperty(it.next());
    }
    m_property_to_item_index_pair.clear();
    m_item_to_index_to_property.clear();
}


void UniversalPropertyEditor::updateSubItems(const QString &name)
{
    qDebug() << "UniversalPropertyEditor::updateSubItems()";
    Q_UNUSED(name)

    if (!m_item) return;

    disconnect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
    disconnect(m_item, SIGNAL(subItemChanged(QString)),
               this, SLOT(updateSubItems(QString)));
    disconnect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
            this, SLOT(onSubItemPropertyChanged(QString,QString)));

    clearEditor();

    addItemProperties(m_item);
    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
    connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
            this, SLOT(onSubItemPropertyChanged(QString,QString)));
}

void UniversalPropertyEditor::onPropertyChanged(const QString &property_name)
{
    qDebug() << "UniversalPropertyEditor::onPropertyChanged() " << property_name ;
    if(!m_item) return;

    QtVariantProperty *variant_property = m_item_to_propertyname_to_qtvariantproperty[m_item][property_name];
    if(variant_property) {
        QVariant property_value = m_item->getRegisteredProperty(property_name);

        disconnect(m_item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        disconnect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
        disconnect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                this, SLOT(onSubItemPropertyChanged(QString,QString)));

        variant_property->setValue(property_value);

        const PropertyAttribute &prop_attribute = m_item->getPropertyAttribute(property_name);
        if(prop_attribute.isDisabled()) {
            variant_property->setEnabled(false);
        } else {
            variant_property->setEnabled(true);
        }

        connect(m_item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
        connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                this, SLOT(onSubItemPropertyChanged(QString,QString)));
    }
}

void UniversalPropertyEditor::onSubItemPropertyChanged(const QString &property_group, const QString &property_name)
{
    qDebug() << "UniversalPropertyEditor::onSubItemPropertyChanged" << property_group << property_name;
    ParameterizedItem *subItem = m_item->getSubItems()[property_group];
    if(subItem){
        QtVariantProperty *variant_property = m_item_to_propertyname_to_qtvariantproperty[subItem][property_name];
        if(variant_property) {
            QVariant property_value = subItem->getRegisteredProperty(property_name);

            disconnect(m_item, SIGNAL(propertyChanged(QString)),
                   this, SLOT(onPropertyChanged(QString)));
            disconnect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(updateSubItems(QString)));
            disconnect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                    this, SLOT(onSubItemPropertyChanged(QString,QString)));

            variant_property->setValue(property_value);

            const PropertyAttribute &prop_attribute = subItem->getPropertyAttribute(property_name);
            if(prop_attribute.isDisabled()) {
                variant_property->setEnabled(false);
            } else {
                variant_property->setEnabled(true);
            }

            connect(m_item, SIGNAL(propertyChanged(QString)),
                   this, SLOT(onPropertyChanged(QString)));
            connect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(updateSubItems(QString)));
            connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                    this, SLOT(onSubItemPropertyChanged(QString,QString)));


        }
    }
}

// assigns item to the property editor
void UniversalPropertyEditor::setItem(ParameterizedItem *item)
{
    qDebug() << "UniversalPropertyEditor::setItem(ParameterizedItem *item)" << item;

    if (m_item == item) return;

    if (m_item) {
        disconnect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(updateSubItems(QString)));
        disconnect(m_item, SIGNAL(propertyChanged(QString)),
                this, SLOT(onPropertyChanged(QString)));
        disconnect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
                this, SLOT(onSubItemPropertyChanged(QString,QString)));

        clearEditor();

    }

    m_item = item;

    if (!m_item) return;

    addItemProperties(m_item);
    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
    connect(m_item, SIGNAL(subItemPropertyChanged(QString,QString)),
            this, SLOT(onSubItemPropertyChanged(QString,QString)));

}

void UniversalPropertyEditor::setCreateGroupProperty(bool create_group_property)
{
    m_create_group_property = create_group_property;
}


void UniversalPropertyEditor::addItemProperties(const ParameterizedItem *item)
{
    QString item_type = item->modelType();

    if(m_create_group_property) {
        QtProperty *item_property = m_manager->addProperty(
                QtVariantPropertyManager::groupTypeId(), item_type);

        addSubProperties(item_property, item);
        m_browser->addProperty(item_property);
    } else {
        addSubProperties(0, item);
    }
}


void UniversalPropertyEditor::addSubProperties(QtProperty *item_property,
                                            const ParameterizedItem *item)
{
    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        const PropertyAttribute &prop_attribute = item->getPropertyAttribute(prop_name);

        if(prop_attribute.isHidden()) continue;

        QVariant prop_value = item->property(prop_name.toUtf8().data());
        int type = GUIHelpers::getVariantType(prop_value);

        QtVariantPropertyManager *manager = m_manager;
        if(prop_attribute.isReadOnly()) manager = m_read_only_manager;

        QtVariantProperty *subProperty = 0;
        if (m_manager->isPropertyTypeSupported(type)) {

            if(prop_attribute.getLabel().isEmpty()) {
                subProperty = manager->addProperty(type, prop_name);
            } else {
                subProperty = manager->addProperty(type, prop_attribute.getLabel());
            }

            subProperty->setValue(prop_value);

            if(type == QVariant::Double) {
                subProperty->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
                AttLimits limits = prop_attribute.getLimits();
                if(limits.hasLowerLimit()) subProperty->setAttribute(QLatin1String("minimum"), limits.getLowerLimit());
                if(limits.hasUpperLimit()) subProperty->setAttribute(QLatin1String("maximum"), limits.getUpperLimit());
                subProperty->setAttribute(QLatin1String("decimals"), prop_attribute.getDecimals());
                subProperty->setAttribute(QLatin1String("singleStep"), 1./std::pow(10.,prop_attribute.getDecimals()-1));
            }

            QString toolTip = prop_attribute.getToolTip();
            if(toolTip.isEmpty()) {
                toolTip = ToolTipDataBase::getSampleViewToolTip(item->modelType(), prop_name);
            }
            if(!toolTip.isEmpty()) subProperty->setToolTip(toolTip);

            if(prop_attribute.isDisabled()) {
                subProperty->setEnabled(false);
            }

            if (item->getSubItems().contains(prop_name)) {
                ParameterizedItem *subitem = item->getSubItems()[prop_name];
                if (subitem) {
                    addSubProperties(subProperty, subitem);
                }
            }

        } else {
            subProperty = m_read_only_manager->addProperty(QVariant::String,
                                                         prop_name);
            subProperty->setValue(QLatin1String("< Unknown Type >"));
            subProperty->setEnabled(false);
        }

        // if item_property exists, then add sub-properties, otherwise add sub-properties
        // directly to the tree browser
        if(item_property) {
            item_property->addSubProperty(subProperty);
        } else {
            m_browser->addProperty(subProperty);
        }

        ParameterizedItem *non_const_item =
                const_cast<ParameterizedItem *>(item);
        ItemIndexPair item_index_pair(non_const_item, i);
        m_property_to_item_index_pair[subProperty] = item_index_pair;
        m_item_to_index_to_property[item][i] = subProperty;
        m_item_to_propertyname_to_qtvariantproperty[item][prop_name] = subProperty;
    }
}


