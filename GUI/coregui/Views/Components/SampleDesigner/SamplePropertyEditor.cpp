#include "SamplePropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "ParameterizedItem.h"

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
        if (type == PropertyVariantManager::formFactorEnumTypeId()) {
            subProperty = m_manager->addProperty(
                        QtVariantPropertyManager::enumTypeId(), prop_name);
            QStringList enumNames = item->getEnumNames(prop_name);
            subProperty->setAttribute(QLatin1String("enumNames"),
                                      enumNames);
//            subProperty->setValue(enumToInt(metaEnum,
//                             metaProperty.read(item).toInt()));
            if (item->getSubItems().contains(prop_name)) {
                ParameterizedItem *subitem = item->getSubItems()[prop_name];
                if (subitem) {
                    addSubProperties(subProperty, subitem);
                }
            }
        }
        else if (m_manager->isPropertyTypeSupported(type)) {
            subProperty = m_manager->addProperty(type, prop_name);
            subProperty->setValue(prop_value);
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
        m_property_to_index[subProperty] = i;
        m_item_to_index_to_property[item][i] = subProperty;
    }
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

int SamplePropertyEditor::enumToInt(const QMetaEnum &metaEnum, int enumValue) const
{
    QMap<int, int> valueMap; // dont show multiple enum values which have the same values
    int pos = 0;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value)) {
            if (value == enumValue)
                return pos;
            valueMap[value] = pos++;
        }
    }
    return -1;
}

int SamplePropertyEditor::intToEnum(const QMetaEnum &metaEnum, int intValue) const
{
    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
    QList<int> values;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value)) {
            valueMap[value] = true;
            values.append(value);
        }
    }
    if (intValue >= values.count())
        return -1;
    return values.at(intValue);
}

int SamplePropertyEditor::flagToInt(const QMetaEnum &metaEnum, int flagValue) const
{
    if (!flagValue)
        return 0;
    int intValue = 0;
    QMap<int, int> valueMap; // dont show multiple enum values which have the same values
    int pos = 0;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value) && isPowerOf2(value)) {
            if (isSubValue(flagValue, value))
                intValue |= (1 << pos);
            valueMap[value] = pos++;
        }
    }
    return intValue;
}

int SamplePropertyEditor::intToFlag(const QMetaEnum &metaEnum, int intValue) const
{
    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
    QList<int> values;
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        int value = metaEnum.value(i);
        if (!valueMap.contains(value) && isPowerOf2(value)) {
            valueMap[value] = true;
            values.append(value);
        }
    }
    int flagValue = 0;
    int temp = intValue;
    int i = 0;
    while (temp) {
        if (i >= values.count())
            return -1;
        if (temp & 1)
            flagValue |= values.at(i);
        i++;
        temp = temp >> 1;
    }
    return flagValue;
}

bool SamplePropertyEditor::isPowerOf2(int value) const
{
    while (value) {
        if (value & 1) {
            return value == 1;
        }
        value = value >> 1;
    }
    return false;
}

