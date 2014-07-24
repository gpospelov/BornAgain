#include "SamplePropertyEditor.h"
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

SamplePropertyEditor::SamplePropertyEditor(QItemSelectionModel *selection_model,
                                           QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_selection_model(selection_model)
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("PropertyEditor"));

//    QtAbstractPropertyBrowser *browser = new QtGroupBoxPropertyBrowser();
//    QtAbstractPropertyBrowser *browser = new QtButtonPropertyBrowser();

    QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(this);
    browser->setRootIsDecorated(false);
    m_browser = browser;
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);

    m_read_only_manager = new PropertyVariantManager(this);

    m_manager = new PropertyVariantManager(this);

    QtVariantEditorFactory *factory = new PropertyVariantFactory();
    m_browser->setFactoryForManager(m_manager, factory);

    connect(m_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

    if(m_selection_model)
        connect(m_selection_model,
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,
                SLOT(selectionChanged(QItemSelection,QItemSelection)) );
}


// show property of currently selected object (triggered by the graphics scene)
// if more than one object is selected, show only last selected
void SamplePropertyEditor::selectionChanged(const QItemSelection & selected,
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


void SamplePropertyEditor::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "SamplePropertyEditor::slotValueChanged()" << value;
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
        qDebug() << "setting ..." << prop_list[item_index_pair.m_index].constData();
        item_index_pair.m_item->setProperty(
            prop_list[item_index_pair.m_index].constData(), value);
    }
}


void SamplePropertyEditor::clearEditor()
{
    qDebug() << "SamplePropertyEditor::clearEditor()";
    //updateExpandState(SaveExpandState);

    QListIterator<QtProperty *> it(m_browser->properties());
    while (it.hasNext()) {
        m_browser->removeProperty(it.next());
    }
    m_property_to_item_index_pair.clear();
    m_item_to_index_to_property.clear();
}


void SamplePropertyEditor::updateSubItems(const QString &name)
{
    qDebug() << "SamplePropertyEditor::updateSubItems()";
    (void)name;
    if (!m_item) return;

//    QListIterator<QtProperty *> it(m_browser->properties());
//    while (it.hasNext()) {
//        m_browser->removeProperty(it.next());
//    }
    clearEditor();

    disconnect(m_item, SIGNAL(propertyItemChanged(QString)),
               this, SLOT(updateSubItems(QString)));
    addItemProperties(m_item);
    connect(m_item, SIGNAL(propertyItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));
}

void SamplePropertyEditor::onPropertyChanged(const QString &property_name)
{
    qDebug() << "SamplePropertyEditor::onPropertyChanged() " << property_name ;
    if(!m_item) return;

    QtVariantProperty *variant_property = m_item_to_propertyname_to_qtvariantproperty[m_item][property_name];
    if(variant_property) {
        QVariant property_value = m_item->getRegisteredProperty(property_name);

        disconnect(m_item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        disconnect(m_item, SIGNAL(propertyItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));

        variant_property->setValue(property_value);

        connect(m_item, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        connect(m_item, SIGNAL(propertyItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
    }
}


// assigns item to the property editor
void SamplePropertyEditor::setItem(ParameterizedItem *item)
{
    if (m_item == item) return;

    if (m_item) {
//        QListIterator<QtProperty *> it(m_browser->properties());
//        while (it.hasNext()) {
//            m_browser->removeProperty(it.next());
//        }
        clearEditor();

        disconnect(m_item, SIGNAL(propertyItemChanged(QString)),
                this, SLOT(updateSubItems(QString)));
    }

    m_item = item;

    if (!m_item) return;

    addItemProperties(m_item);
    connect(m_item, SIGNAL(propertyItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
    connect(m_item, SIGNAL(propertyChanged(QString)),
            this, SLOT(onPropertyChanged(QString)));

}


void SamplePropertyEditor::addItemProperties(const ParameterizedItem *item)
{
    QString item_type = item->modelType();
    QtProperty *item_property = m_manager->addProperty(
                QtVariantPropertyManager::groupTypeId(), item_type);

    addSubProperties(item_property, item);
    m_browser->addProperty(item_property);
}


void SamplePropertyEditor::addSubProperties(QtProperty *item_property,
                                            const ParameterizedItem *item)
{
    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        PropertyAttribute prop_attribute = item->getPropertyAttribute(prop_name);

        if(prop_attribute.getAppearance() & PropertyAttribute::HiddenProperty) continue;

        QVariant prop_value = item->property(prop_name.toUtf8().data());
        int type = GUIHelpers::getVariantType(prop_value);

        qDebug() << "XXX " << item->modelType() << prop_name << type;
        QtVariantProperty *subProperty = 0;
        if (m_manager->isPropertyTypeSupported(type)) {

            if(prop_attribute.getLabel().isEmpty()) {
                subProperty = m_manager->addProperty(type, prop_name);
            } else {
                subProperty = m_manager->addProperty(type, prop_attribute.getLabel());
            }

            subProperty->setValue(prop_value);

            QString toolTip = ToolTipDataBase::getSampleViewToolTip(item->modelType(), prop_name);
            if(!toolTip.isEmpty()) subProperty->setToolTip(toolTip);

            if(prop_attribute.getAppearance() & PropertyAttribute::DisabledProperty) {
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

        item_property->addSubProperty(subProperty);
        ParameterizedItem *non_const_item =
                const_cast<ParameterizedItem *>(item);
        ItemIndexPair item_index_pair(non_const_item, i);
        m_property_to_item_index_pair[subProperty] = item_index_pair;
        m_item_to_index_to_property[item][i] = subProperty;
        m_item_to_propertyname_to_qtvariantproperty[item][prop_name] = subProperty;
    }
}

