#include "MaterialEditorWidget.h"
#include "MaterialModel.h"
#include "MaterialVariantManager.h"
#include "qttreepropertybrowser.h"
#include <QtVariantPropertyManager>
#include <QtProperty>
#include <QtVariantProperty>

#include <QVBoxLayout>
#include <QDebug>


MaterialEditorWidget::MaterialEditorWidget(MaterialModel *model, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(0)
    , m_browser(0)
    , m_variantManager(0)

{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_browser = new QtTreePropertyBrowser(this);
    //m_browser->setRootIsDecorated(false);

    m_readOnlyManager = new MaterialVariantManager(this);

    m_variantManager = new MaterialVariantManager(this);

    m_variantFactory = new QtVariantEditorFactory(this);

    m_browser->setFactoryForManager(m_variantManager, m_variantFactory);


    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);


    setLayout(mainLayout);

    setModel(model);


}


void MaterialEditorWidget::setModel(MaterialModel *model)
{
    Q_ASSERT(model);
    if(model != m_materialModel) {
        m_materialModel = model;
        updateBrowser();
    }
}


void MaterialEditorWidget::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "MaterialEditorWidget::slotValueChanged" << property << value;
//    if (!m_property_to_item_index_pair.contains(property))
//        return;

//    ItemIndexPair item_index_pair =
//            m_property_to_item_index_pair.value(property);

//    if (item_index_pair.m_item) {
//        QList<QByteArray> prop_list =
//                item_index_pair.m_item->dynamicPropertyNames();
//        if (item_index_pair.m_index > prop_list.length()) {
//            return;
//        }
//        item_index_pair.m_item->setProperty(
//            prop_list[item_index_pair.m_index].constData(), value);
//    }
//    if(m_top_property_to_material.contains(property)) {
//        qDebug() << "XXX contains" << value.toInt();
//        m_top_property_to_material[property]->setType(MaterialItem::MaterialType(value.toInt()));
//        updateMaterialProperties(m_top_property_to_material[property]);
//    } else {
//        if(m_property_to_subitem.contains(property)) {
//            qDebug() << "XXX subproperty" << property->propertyName() << value;
//            MaterialItem *material = m_property_to_subitem[property].m_parent;
//            material->setMaterialProperty(property->propertyName(), value);
//            updateMaterialProperties(material);
//        }

//    }
    if (!m_property_to_subitem.contains(property))
        return;

    MaterialItem *material = m_property_to_subitem[property].m_parent;
    QString subName = m_property_to_subitem[property].m_name;

    if(subName.isEmpty()) {
        material->setType(MaterialItem::MaterialType(value.toInt()));
        removeSubProperties(property);
        addSubProperties(property, material);

    } else {
        qDebug() << "XXX subproperty" << property->propertyName() << value;
        material->setMaterialProperty(property->propertyName(), value);
    }

    updateMaterialProperties(material);

}



void MaterialEditorWidget::updateBrowser()
{
    foreach(MaterialItem *material, m_materialModel->materials()) {
        addMaterialProperties(material);
    }

}


void MaterialEditorWidget::updateMaterialProperties(MaterialItem *material)
{
    qDebug() << "MaterialEditorWidget::updateMaterialProperties ";
    QtVariantProperty *property = m_top_material_to_property[material];
    property->setPropertyName(material->property("Name").toString());
    property->setValue(int(material->getType()));

}



void MaterialEditorWidget::addMaterialProperties(MaterialItem *material)
{
    qDebug() << "MaterialEditorWidget::addMaterialProperties() " << material->getName();
    QtVariantProperty *item_property = m_variantManager->addProperty(
                QtVariantPropertyManager::enumTypeId(), material->getName());

    qDebug() << "XXX " << item_property->valueText() << item_property->displayText();

    qDebug() << "MaterialEditorWidget::addMaterialProperties() " << material->getTypeNames();
    item_property->setAttribute(QLatin1String("enumNames"), material->getTypeNames());
    item_property->setValue(int(material->getType()));


//    QtVariantProperty *subProperty = m_variantManager->addProperty(QVariant::String, "Name");
//    subProperty->setValue(material->getName());
//    item_property->addSubProperty(subProperty);

//    subProperty = m_variantManager->addProperty(QVariant::Color, "Color");
//    subProperty->setValue(material->getColor());
//    item_property->addSubProperty(subProperty);


//    Q_ASSERT(item_property);

    addSubProperties(item_property, material);
    m_browser->addProperty(item_property);

    m_top_property_to_material[item_property] = material;
    m_top_material_to_property[material] = item_property;
    m_property_to_subitem[item_property] = SubProperty(material, "");


//    QtBrowserItem *browserItem = m_browser->addProperty(item_property);
//    m_browser->setExpanded(browserItem, false);

//    QtProperty *property = m_variantManager->addProperty(QVariant::String, tr("Name"));
//    property->setValue(material->getName());
//    addProperty(property, JobQueueXML::JobNameAttribute);

}



void MaterialEditorWidget::removeSubProperties(QtProperty *property)
{
    qDebug() << "MaterialEditorWidget::updateMaterialProperties" << property->propertyName();
    QList<QtProperty *> properties = property->subProperties();
    foreach(QtProperty *child, properties) {
        m_browser->removeProperty(child);
        delete child;

        QMap<QtProperty *, SubProperty>::iterator it = m_property_to_subitem.find(child);
        m_property_to_subitem.erase(it);

    }





}


void MaterialEditorWidget::addSubProperties(QtProperty *material_property, MaterialItem *material)
{
    Q_ASSERT(material_property);
    Q_ASSERT(material);


    QList<QByteArray> property_names = material->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        QVariant prop_value = material->property(prop_name.toUtf8().data());
        int type = prop_value.type();
        if (type == QVariant::UserType) {
            type = prop_value.userType();
        }
        qDebug() << "xxxxxx" << prop_name << prop_value << type;
        QtVariantProperty *subProperty = 0;
        if (m_variantManager->isPropertyTypeSupported(type)) {
            subProperty = m_variantManager->addProperty(type, prop_name);
            subProperty->setValue(prop_value);
            if (material->getSubItems().contains(prop_name)) {
                subProperty->setAttribute(QLatin1String("readOnly"), true);
                MaterialItem *subitem = material->getSubItems()[prop_name];
                if (subitem) {
                    addSubProperties(subProperty, subitem);
                }
            }
        } else {
            subProperty = m_readOnlyManager->addProperty(QVariant::String,
                                                         prop_name);
            subProperty->setValue(QLatin1String("< Unknown Type >"));
            subProperty->setEnabled(false);
        }
        material_property->addSubProperty(subProperty);
//        ParameterizedItem *non_const_item =
//                const_cast<ParameterizedItem *>(item);
//        ItemIndexPair item_index_pair(non_const_item, i);
//        m_property_to_item_index_pair[subProperty] = item_index_pair;
//        m_item_to_index_to_property[item][i] = subProperty;
        m_property_to_subitem[subProperty] = SubProperty(material,prop_name);
    }



}

