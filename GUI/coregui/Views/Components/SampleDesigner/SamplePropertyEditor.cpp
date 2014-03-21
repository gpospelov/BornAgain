#include "SamplePropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "ParameterizedItem.h"

#include "qttreepropertybrowser.h"

#include <QtProperty>
#include <QItemSelectionModel>
#include <QVBoxLayout>

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


bool SamplePropertyEditor::isSubValue(int value, int subValue) const
{
    if (value == subValue)
        return true;
    int i = 0;
    while (subValue) {
        if (!(value & (1 << i))) {
            if (subValue & 1)
                return false;
        }
        i++;
        subValue = subValue >> 1;
    }
    return true;
}

// show property of currently selected object (triggered by the graphics scene)
// if more than one object is selected, show only last selected
void SamplePropertyEditor::selectionChanged(const QItemSelection & selected,
                                            const QItemSelection & deselected)
{
    (void)deselected;
    QModelIndexList indices = selected.indexes();
    ParameterizedItem *item = static_cast<ParameterizedItem *>(
                indices.back().internalPointer());
    setItem(item);
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

        QList<QByteArray> property_names = item->dynamicPropertyNames();
        for (int i = 0; i < property_names.length(); ++i) {
            QString prop_name = QString(property_names[i]);
            QVariant prop_value = item->property(prop_name.toUtf8().data());
            QVariant::Type type = prop_value.type();
            QtVariantProperty *subProperty = 0;
            if (m_manager->isPropertyTypeSupported(type)) {
                subProperty = m_manager->addProperty(type, prop_name);
                subProperty->setValue(prop_value);
            } else {
                subProperty = m_read_only_manager->addProperty(QVariant::String,
                                                             prop_name);
                subProperty->setValue(QLatin1String("< Unknown Type >"));
                subProperty->setEnabled(false);
            }
            item_property->addSubProperty(subProperty);
            m_property_to_index[subProperty] = i;
            m_item_to_index_to_property[item][i] = subProperty;
        }
    } else {
        updateItemProperties(item);
    }

    m_top_level_properties.append(item_property);
    m_browser->addProperty(item_property);
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
    }
}

void SamplePropertyEditor::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    if (!m_property_to_index.contains(property))
        return;

    int index = m_property_to_index.value(property);

    QList<QByteArray> prop_list = m_item->dynamicPropertyNames();
    if (index > prop_list.length()) {
        return;
    }
    m_item->setProperty(prop_list[index].constData(), value);
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
    }

    m_item = item;

    if (!m_item) return;

    addItemProperties(m_item);
}
