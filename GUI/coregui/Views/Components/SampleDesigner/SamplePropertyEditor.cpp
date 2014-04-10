#include "SamplePropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "ParameterizedItem.h"

#include "FormFactorProperty.h"
#include "qttreepropertybrowser.h"

#include <QtProperty>
#include <QItemSelectionModel>
#include <QVBoxLayout>
#include <QMetaProperty>

SamplePropertyEditor::SamplePropertyEditor(QItemSelectionModel *selection_model,
                                           QWidget *parent)
    : QWidget(parent)
    , m_item(0)
    , m_selection_model(selection_model)
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("PropertyEditor"));

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
        item_index_pair.m_item->setProperty(
            prop_list[item_index_pair.m_index].constData(), value);
    }
}

void SamplePropertyEditor::updateSubItems(QString name)
{
    (void)name;
    if (!m_item) return;

    QListIterator<QtProperty *> it(m_top_level_properties);
    while (it.hasNext()) {
        m_browser->removeProperty(it.next());
    }
    m_top_level_properties.clear();
    QtProperty *item_property = m_item_to_property[m_item];
    m_item_to_property.remove(m_item);
    m_property_to_item.remove(item_property);

    disconnect(m_item, SIGNAL(subItemChanged(QString)),
               this, SLOT(updateSubItems(QString)));
    addItemProperties(m_item);
    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
}

// assigns item to the property editor
void SamplePropertyEditor::setItem(ParameterizedItem *item)
{
    if (m_item == item) return;

    if (m_item) {
        QListIterator<QtProperty *> it(m_top_level_properties);
        while (it.hasNext()) {
            m_browser->removeProperty(it.next());
        }
        m_top_level_properties.clear();
        disconnect(m_item, SIGNAL(subItemChanged(QString)),
                this, SLOT(updateSubItems(QString)));
    }

    m_item = item;

    if (!m_item) return;

    addItemProperties(m_item);
    connect(m_item, SIGNAL(subItemChanged(QString)),
            this, SLOT(updateSubItems(QString)));
}

void SamplePropertyEditor::updateItemProperties(const ParameterizedItem *item)
{
    if (!item)
        return;

    QtProperty *item_property = m_item_to_property.value(item);
    if (!item_property)
        return;

    QList<QByteArray> prop_list = item->dynamicPropertyNames();
    for (int i=0; i<prop_list.length(); ++i) {
        const char *name = prop_list[i].constData();
        QVariant variant = item->property(name);
        QtVariantProperty *subProperty =
                m_item_to_index_to_property[item][i];
        subProperty->setValue(variant);
        ParameterizedItem *subitem = item->getSubItems()[QString(name)];
        if (subitem) {
            updateItemProperties(subitem);
        }
    }
}

void SamplePropertyEditor::addItemProperties(const ParameterizedItem *item)
{
    QtProperty *item_property = m_item_to_property.value(item);
    if (!item_property) {
        QString item_type = item->modelType();
        item_property = m_manager->addProperty(
                    QtVariantPropertyManager::groupTypeId(), item_type);
        m_item_to_property[item] = item_property;
        m_property_to_item[item_property] = item;

        addSubProperties(item_property, item);
    } else {
        updateItemProperties(item);
    }

    m_top_level_properties.append(item_property);
    m_browser->addProperty(item_property);
}

void SamplePropertyEditor::addSubProperties(QtProperty *item_property,
                                            const ParameterizedItem *item)
{
    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        QVariant prop_value = item->property(prop_name.toUtf8().data());
        int type = prop_value.type();
        if (type == QVariant::UserType) {
            type = prop_value.userType();
        }
        QtVariantProperty *subProperty = 0;
        if (m_manager->isPropertyTypeSupported(type)) {
            subProperty = m_manager->addProperty(type, prop_name);
            subProperty->setValue(prop_value);
            if (item->getSubItems().contains(prop_name)) {
                ParameterizedItem *subitem = item->getSubItems()[prop_name];
                if (subitem) {
                    m_item_to_property[subitem] = subProperty;
                    m_property_to_item[subProperty] = subitem;
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
    }
}

