#include "SamplePropertyEditor.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"

#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"

#include <QtBoolPropertyManager>
#include <QtIntPropertyManager>
#include <QtStringPropertyManager>
#include <QtSizePropertyManager>
#include <QtRectPropertyManager>
#include <QtSizePolicyPropertyManager>
#include <QtEnumPropertyManager>
#include <QtGroupPropertyManager>

#include <QtCheckBoxFactory>
#include <QtSpinBoxFactory>
#include <QtSliderFactory>
#include <QtScrollBarFactory>
#include <QtLineEditFactory>
#include <QtEnumEditorFactory>
#include <QtProperty>

#include <QVBoxLayout>
#include <QVariant>
#include <iostream>

#include <QItemSelectionModel>

#include <QMetaObject>
#include <QMetaProperty>
#include <QVBoxLayout>
#include <QScrollArea>
#include "qtvariantproperty.h"
#include "qtgroupboxpropertybrowser.h"
#include "qttreepropertybrowser.h"
#include "qtpropertybrowser.h"

#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerHelper.h"

//#include <QGraphicsItem>
#include "ParameterizedItem.h"

SamplePropertyEditor::SamplePropertyEditor(QItemSelectionModel *selection_model,
                                           QWidget *parent)
    : QWidget(parent)
    , m_selection_model(selection_model)
    , m_object(0)
{
    setWindowTitle(QLatin1String("Property Editor"));
    setObjectName(QLatin1String("PropertyEditor"));

    QtTreePropertyBrowser *browser = new QtTreePropertyBrowser(this);
    browser->setRootIsDecorated(false);
    m_browser = browser;
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);

    m_readOnlyManager = new PropertyVariantManager(this);

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


//int SamplePropertyEditor::enumToInt(const QMetaEnum &metaEnum, int enumValue) const
//{
//    QMap<int, int> valueMap; // dont show multiple enum values which have the same values
//    int pos = 0;
//    for (int i = 0; i < metaEnum.keyCount(); i++) {
//        int value = metaEnum.value(i);
//        if (!valueMap.contains(value)) {
//            if (value == enumValue)
//                return pos;
//            valueMap[value] = pos++;
//        }
//    }
//    return -1;
//}

//int SamplePropertyEditor::intToEnum(const QMetaEnum &metaEnum, int intValue) const
//{
//    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
//    QList<int> values;
//    for (int i = 0; i < metaEnum.keyCount(); i++) {
//        int value = metaEnum.value(i);
//        if (!valueMap.contains(value)) {
//            valueMap[value] = true;
//            values.append(value);
//        }
//    }
//    if (intValue >= values.count())
//        return -1;
//    return values.at(intValue);
//}

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

//bool SamplePropertyEditor::isPowerOf2(int value) const
//{
//    while (value) {
//        if (value & 1) {
//            return value == 1;
//        }
//        value = value >> 1;
//    }
//    return false;
//}

//int SamplePropertyEditor::flagToInt(const QMetaEnum &metaEnum, int flagValue) const
//{
//    if (!flagValue)
//        return 0;
//    int intValue = 0;
//    QMap<int, int> valueMap; // dont show multiple enum values which have the same values
//    int pos = 0;
//    for (int i = 0; i < metaEnum.keyCount(); i++) {
//        int value = metaEnum.value(i);
//        if (!valueMap.contains(value) && isPowerOf2(value)) {
//            if (isSubValue(flagValue, value))
//                intValue |= (1 << pos);
//            valueMap[value] = pos++;
//        }
//    }
//    return intValue;
//}


//int SamplePropertyEditor::intToFlag(const QMetaEnum &metaEnum, int intValue) const
//{
//    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
//    QList<int> values;
//    for (int i = 0; i < metaEnum.keyCount(); i++) {
//        int value = metaEnum.value(i);
//        if (!valueMap.contains(value) && isPowerOf2(value)) {
//            valueMap[value] = true;
//            values.append(value);
//        }
//    }
//    int flagValue = 0;
//    int temp = intValue;
//    int i = 0;
//    while (temp) {
//        if (i >= values.count())
//            return -1;
//        if (temp & 1)
//            flagValue |= values.at(i);
//        i++;
//        temp = temp >> 1;
//    }
//    return flagValue;
//}


// show property of currently selected object (triggered by the graphics scene)
// if more than one object is selected, show only last selected
void SamplePropertyEditor::selectionChanged(const QItemSelection & selected,
                                            const QItemSelection & deselected)
{
    (void)deselected;
    QModelIndexList indices = selected.indexes();
    QObject *object(0);
    ParameterizedItem *item = static_cast<ParameterizedItem *>(
                indices.back().internalPointer());
    if( item ) object = item;
    setObject(object);
}


// assigns objects to the property editor
void SamplePropertyEditor::setObject(QObject *object)
{
    std::cout << "SamplePropertyEditor::setObject() -> 2.1" << std::endl;
    if (m_object == object) return;

    std::cout << "SamplePropertyEditor::setObject() -> 2.2" << std::endl;
    if (m_object) {
//        saveExpandedState();
        QListIterator<QtProperty *> it(m_topLevelProperties);
        while (it.hasNext()) {
            m_browser->removeProperty(it.next());
        }
        m_topLevelProperties.clear();
    }

    std::cout << "SamplePropertyEditor::setObject() -> 2.3" << std::endl;
    m_object = object;

    if (!m_object) return;

    std::cout << "SamplePropertyEditor::setObject() -> 2.4" << std::endl;
    addClassProperties(m_object->metaObject());
    std::cout << "SamplePropertyEditor::setObject() -> 2.5" << std::endl;

    //    restoreExpandedState();
}

void SamplePropertyEditor::addClassProperties(const QMetaObject *metaObject)
{
    std::cout << "SamplePropertyEditor::addClassProperties() -> 3.1" << std::endl;
    if (!metaObject) return;

//    complex_t aaa(1,2);
//    QVariant var;
//    var.setValue(aaa); // copy s into the variant

//    std::cout << "BBB " << var.type() << std::endl;

//    complex_t aaa2 = var.value<complex_t>();
//    std::cout << "AAA XXX " << aaa2 << std::endl;



    //addClassProperties(metaObject->superClass());

    QtProperty *classProperty = m_classToProperty.value(metaObject);
    if (!classProperty) {
        std::cout << "SamplePropertyEditor::addClassProperties() -> 3.2" << std::endl;
        QString className = QLatin1String(metaObject->className());
        classProperty = m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), className);
        m_classToProperty[metaObject] = classProperty;
        m_propertyToClass[classProperty] = metaObject;

        for (int idx = metaObject->propertyOffset(); idx < metaObject->propertyCount(); idx++) {
            QMetaProperty metaProperty = metaObject->property(idx);
            int type = metaProperty.userType();
            std::cout << "XXX metaProperty.name():" << metaProperty.name()
                      << " metaProperty.type():" << metaProperty.type()
                      << " metaProperty.typeName():" << metaProperty.typeName()
                      << " metaProperty.userType():" << metaProperty.userType()
                      << std::endl;
            QtVariantProperty *subProperty = 0;
            if (!metaProperty.isReadable()) {
                subProperty = m_readOnlyManager->addProperty(QVariant::String, QLatin1String(metaProperty.name()));
                subProperty->setValue(QLatin1String("< Non Readable >"));
//            } else if (metaProperty.isEnumType()) {
//                if (metaProperty.isFlagType()) {
//                    subProperty = m_manager->addProperty(QtVariantPropertyManager::flagTypeId(), QLatin1String(metaProperty.name()));
//                    QMetaEnum metaEnum = metaProperty.enumerator();
//                    QMap<int, bool> valueMap;
//                    QStringList flagNames;
//                    for (int i = 0; i < metaEnum.keyCount(); i++) {
//                        int value = metaEnum.value(i);
//                        if (!valueMap.contains(value) && isPowerOf2(value)) {
//                            valueMap[value] = true;
//                            flagNames.append(QLatin1String(metaEnum.key(i)));
//                        }
//                    subProperty->setAttribute(QLatin1String("flagNames"), flagNames);
//                    subProperty->setValue(flagToInt(metaEnum, metaProperty.read(m_object).toInt()));
//                    }
//                } else {
//                    subProperty = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), QLatin1String(metaProperty.name()));
//                    QMetaEnum metaEnum = metaProperty.enumerator();
//                    QMap<int, bool> valueMap; // dont show multiple enum values which have the same values
//                    QStringList enumNames;
//                    for (int i = 0; i < metaEnum.keyCount(); i++) {
//                        int value = metaEnum.value(i);
//                        if (!valueMap.contains(value)) {
//                            valueMap[value] = true;
//                            enumNames.append(QLatin1String(metaEnum.key(i)));
//                        }
//                    }
//                    subProperty->setAttribute(QLatin1String("enumNames"), enumNames);
//                    subProperty->setValue(enumToInt(metaEnum, metaProperty.read(m_object).toInt()));
//                }
//            } else if(metaProperty.typeName() == QString("complex_t")) {

//                subProperty = m_manager->addProperty(1024, QLatin1String(" PointF Property"));
//                subProperty->setValue(QPointF(1.2345, -1.23451));
//                subProperty->setAttribute(QLatin1String("decimals"), 3);
                //topItem->addSubProperty(item);

            } else if (m_manager->isPropertyTypeSupported(type)) {
                std::cout << "XXXXX adding property " << type << std::endl;
                if (!metaProperty.isWritable())
                    subProperty = m_readOnlyManager->addProperty(type, QLatin1String(metaProperty.name()) + QLatin1String(" (Non Writable)"));
                if (!metaProperty.isDesignable())
                    subProperty = m_readOnlyManager->addProperty(type, QLatin1String(metaProperty.name()) + QLatin1String(" (Non Designable)"));
                else
                    subProperty = m_manager->addProperty(type, QLatin1String(metaProperty.name()));
                subProperty->setValue(metaProperty.read(m_object));
            } else {
                subProperty = m_readOnlyManager->addProperty(QVariant::String, QLatin1String(metaProperty.name()));
                subProperty->setValue(QLatin1String("< Unknown Type >"));
                subProperty->setEnabled(false);
            }
            classProperty->addSubProperty(subProperty);
            m_propertyToIndex[subProperty] = idx;
            m_classToIndexToProperty[metaObject][idx] = subProperty;
        }
    } else {
        updateClassProperties(metaObject, false);
    }

    m_topLevelProperties.append(classProperty);
    m_browser->addProperty(classProperty);
}

void SamplePropertyEditor::addItemProperties(const ParameterizedItem *item)
{
    QtProperty *classProperty = m_itemToProperty.value(metaObject);
    if (!classProperty) {
        std::cout << "SamplePropertyEditor::addClassProperties() -> 3.2" << std::endl;
        QString className = QLatin1String(metaObject->className());
        classProperty = m_manager->addProperty(QtVariantPropertyManager::groupTypeId(), className);
        m_classToProperty[metaObject] = classProperty;
        m_propertyToClass[classProperty] = metaObject;

        for (int idx = metaObject->propertyOffset(); idx < metaObject->propertyCount(); idx++) {
            QMetaProperty metaProperty = metaObject->property(idx);
            int type = metaProperty.userType();
            std::cout << "XXX metaProperty.name():" << metaProperty.name()
                      << " metaProperty.type():" << metaProperty.type()
                      << " metaProperty.typeName():" << metaProperty.typeName()
                      << " metaProperty.userType():" << metaProperty.userType()
                      << std::endl;
            QtVariantProperty *subProperty = 0;
            if (!metaProperty.isReadable()) {
                subProperty = m_readOnlyManager->addProperty(QVariant::String, QLatin1String(metaProperty.name()));
                subProperty->setValue(QLatin1String("< Non Readable >"));
            } else if (m_manager->isPropertyTypeSupported(type)) {
                std::cout << "XXXXX adding property " << type << std::endl;
                if (!metaProperty.isWritable())
                    subProperty = m_readOnlyManager->addProperty(type, QLatin1String(metaProperty.name()) + QLatin1String(" (Non Writable)"));
                if (!metaProperty.isDesignable())
                    subProperty = m_readOnlyManager->addProperty(type, QLatin1String(metaProperty.name()) + QLatin1String(" (Non Designable)"));
                else
                    subProperty = m_manager->addProperty(type, QLatin1String(metaProperty.name()));
                subProperty->setValue(metaProperty.read(m_object));
            } else {
                subProperty = m_readOnlyManager->addProperty(QVariant::String, QLatin1String(metaProperty.name()));
                subProperty->setValue(QLatin1String("< Unknown Type >"));
                subProperty->setEnabled(false);
            }
            classProperty->addSubProperty(subProperty);
            m_propertyToIndex[subProperty] = idx;
            m_classToIndexToProperty[metaObject][idx] = subProperty;
        }
    } else {
        updateItemProperties(item, false);
    }

    m_topLevelProperties.append(classProperty);
    m_browser->addProperty(classProperty);
}

void SamplePropertyEditor::updateItemProperties(const ParameterizedItem *item)
{
    if (!item)
        return;

    std::cout << "SamplePropertyEditor::updateItemProperties " << recursive << std::endl;

    QtProperty *item_property = m_itemToProperty.value(item);
    if (!item_property)
        return;

    QListIterator<QByteArray> it(item->dynamicPropertyNames());
    while (it.hasNext()) {
        const char *name = it.next().constData();
        QVariant variant = item->property(name);
        QtVariantProperty *subProperty =
                m_itemToStringToProperty[item][QString(name)];
        subProperty->setValue(variant);
    }
}

//void SamplePropertyEditor::updateClassProperties(const QMetaObject *metaObject, bool recursive)
//{
//    if (!metaObject)
//        return;

//    std::cout << "AAA SamplePropertyEditor::updateClassProperties " << recursive << std::endl;
//    if (recursive)
//        updateClassProperties(metaObject->superClass(), recursive);

//    QtProperty *classProperty = m_classToProperty.value(metaObject);
//    if (!classProperty)
//        return;

//    for (int idx = metaObject->propertyOffset(); idx < metaObject->propertyCount(); idx++) {
//        QMetaProperty metaProperty = metaObject->property(idx);
//        if (metaProperty.isReadable()) {
//            if (m_classToIndexToProperty.contains(metaObject) && m_classToIndexToProperty[metaObject].contains(idx)) {
//                QtVariantProperty *subProperty = m_classToIndexToProperty[metaObject][idx];
////                if (metaProperty.isEnumType()) {
////                    if (metaProperty.isFlagType())
////                        subProperty->setValue(flagToInt(metaProperty.enumerator(), metaProperty.read(m_object).toInt()));
////                    else
////                        subProperty->setValue(enumToInt(metaProperty.enumerator(), metaProperty.read(m_object).toInt()));
////                } else {
//                    subProperty->setValue(metaProperty.read(m_object));
////                }
//            }
//        }
//    }
//}




//void SamplePropertyEditor::saveExpandedState()
//{

//}

//void SamplePropertyEditor::restoreExpandedState()
//{

//}


void SamplePropertyEditor::slotValueChanged(QtProperty *property, const QVariant &value)
{
    std::cout << "SamplePropertyEditor::slotValueChanged() -> 1.1" << std::endl;
    if (!m_propertyToIndex.contains(property))
        return;
    std::cout << "SamplePropertyEditor::slotValueChanged() -> 1.2" << std::endl;

    int idx = m_propertyToIndex.value(property);

    const QMetaObject *metaObject = m_object->metaObject();
    QMetaProperty metaProperty = metaObject->property(idx);
//    if (metaProperty.isEnumType()) {
//        if (metaProperty.isFlagType())
//            metaProperty.write(m_object, intToFlag(metaProperty.enumerator(), value.toInt()));
//        else
//            metaProperty.write(m_object, intToEnum(metaProperty.enumerator(), value.toInt()));
//    } else {
        metaProperty.write(m_object, value);
//    }
    std::cout << "SamplePropertyEditor::slotValueChanged() -> 1.3" << std::endl;

//    updateClassProperties(metaObject, false);
}




//void SamplePropertyEditor::valueChanged(QtProperty *property, const QVariant &value)
//{
//    std::cout << "SamplePropertyEditor::valueChange() " << std::endl;
//    Q_UNUSED(property);
//    Q_UNUSED(value);
//    std::cout << "SamplePropertyEditor::valueChange() " << std::endl;
//}


//void SamplePropertyEditor::attributeChanged(QtProperty *property,
//            const QString &attribute, const QVariant &val)
//{
//    std::cout << "SamplePropertyEditor::attributeChange() " << std::endl;

//}

