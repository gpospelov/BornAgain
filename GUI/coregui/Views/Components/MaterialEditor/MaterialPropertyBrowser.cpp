#include "MaterialPropertyBrowser.h"
#include "MaterialModel.h"
#include "MaterialVariantManager.h"
#include "MaterialVariantFactory.h"
#include "qttreepropertybrowser.h"
#include <QtVariantPropertyManager>
#include <QtProperty>
#include <QtVariantProperty>
#include <QtTreePropertyBrowser>
#include <QVBoxLayout>
#include <QDebug>
#include <qtpropertybrowser.h>


MaterialPropertyBrowser::MaterialPropertyBrowser(MaterialModel *model, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(0)
    , m_browser(0)
    , m_variantManager(0)

{
    m_browser = new QtTreePropertyBrowser(this);
    //m_browser->setRootIsDecorated(false);

    m_readOnlyManager = new MaterialVariantManager(this);

    m_variantManager = new MaterialVariantManager(this);

    //m_variantFactory = new QtVariantEditorFactory(this);
    m_variantFactory = new MaterialVariantFactory(this);

    m_browser->setFactoryForManager(m_variantManager, m_variantFactory);


    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));


    connect(m_browser, SIGNAL(currentItemChanged(QtBrowserItem*)), this, SLOT(onCurrentBrowserItemChanged(QtBrowserItem*)));


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);
    setLayout(layout);

    setModel(model);
}


void MaterialPropertyBrowser::setModel(MaterialModel *model)
{
    Q_ASSERT(model);
    if(model != m_materialModel) {
        m_materialModel = model;
        connect(m_materialModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onRowsInserted(QModelIndex, int,int)));
        connect(m_materialModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onRowsRemoved(QModelIndex, int,int)));

        updateBrowser();
    }
}


void MaterialPropertyBrowser::onRowsInserted(const QModelIndex & /*parent*/, int /*first*/, int /*last*/)
{
    clearBrowser();
    updateBrowser();
}


void MaterialPropertyBrowser::onRowsRemoved(const QModelIndex & /*parent*/, int /*first*/, int /*last*/)
{
    clearBrowser();
    updateBrowser();
}



void MaterialPropertyBrowser::slotValueChanged(QtProperty *property,
                                            const QVariant &value)
{
    qDebug() << "MaterialEditorWidget::slotValueChanged" << property << value;

    if (!m_property_to_subitem.contains(property))
        return;

    MaterialItem *material = m_property_to_subitem[property].m_owner;
    QString subName = m_property_to_subitem[property].m_name;

    if(subName.isEmpty()) {
        material->setType(MaterialItem::MaterialType(value.toInt()));
        removeSubProperties(property);
        addSubProperties(property, material);

    } else {
        qDebug() << "XXX subproperty" << property->propertyName() << value;
        material->setMaterialProperty(property->propertyName(), value);

//        if(property->propertyName() == "gamma") {
//            bool status;
//            evaluateDoubleValue(value, status);
//        }

    }

    updateMaterialProperties(material);

}



//double MaterialPropertyBrowser::evaluateDoubleValue(const QVariant &variant, bool &status)
//{
//    QString formula = variant.toString();
//    if( !formula.size() ) {
//        status = false;
//        return 0.0;
//    }
//    QScriptEngine myEngine;
//    QScriptValue x = myEngine.evaluate(formula);
//    if( !x.isNumber()) {
//        status = false;
//        return 0.0;
//    }
//    return x.toNumber();
//}



void MaterialPropertyBrowser::updateBrowser()
{
    qDebug() << "MaterialPropertyBrowser::updateBrowser()";
    foreach(MaterialItem *material, m_materialModel->materials()) {
        addMaterialProperties(material);
    }
    updateExpandState(RestoreExpandState);
    //m_browser->setCurrentItem(0);
}


void MaterialPropertyBrowser::clearBrowser()
{
    updateExpandState(SaveExpandState);
    QMap<QtProperty *, SubItem>::iterator it = m_property_to_subitem.begin();
    while(it!=m_property_to_subitem.end()) {
        delete it.key();
        //delete it.value();
        it++;
    }
    m_property_to_subitem.clear();
    m_subitem_to_property.clear();
    m_top_property_to_material.clear();
    m_top_material_to_property.clear();
    m_material_to_property.clear();


}


void MaterialPropertyBrowser::updateMaterialProperties(MaterialItem *material)
{
    qDebug() << "MaterialEditorWidget::updateMaterialProperties ";
    //QtVariantProperty *property = m_top_material_to_property[material];
    if(m_top_material_to_property.contains(material)) {
//        m_top_material_to_property[material]->setPropertyName(material->getName());
        m_top_material_to_property[material]->setPropertyName(material->property("Name").toString());
//        m_material_to_property[material]["Name"]->setValue(material->getName());
    }
    //property->setValue(int(material->getType()));

    //updateSubProperties(material);

    QMap<MaterialItem *, QtVariantProperty *>::iterator it = m_top_material_to_property.begin();
    while(it!=m_top_material_to_property.end()) {
        updateSubProperties(it.key());
        ++it;
    }


}



void MaterialPropertyBrowser::addMaterialProperties(MaterialItem *material)
{
    qDebug() << "MaterialEditorWidget::addMaterialProperties() " << material->property("Name").toString();
    QtVariantProperty *item_property = m_variantManager->addProperty(
                QtVariantPropertyManager::enumTypeId(), material->getName());

    //qDebug() << "XXX " << item_property->valueText() << item_property->displayText();

    item_property->setAttribute(QLatin1String("enumNames"), material->getMaterialTypes());
    item_property->setValue(int(material->getType()));


//    subProperty = m_variantManager->addProperty(QVariant::Color, "Color");
//    subProperty->setValue(material->getColor());
//    item_property->addSubProperty(subProperty);


//    Q_ASSERT(item_property);

    addSubProperties(item_property, material);
    m_browser->addProperty(item_property);

    m_top_property_to_material[item_property] = material;
    m_top_material_to_property[material] = item_property;
    m_property_to_subitem[item_property] = SubItem(material, "");


//    QtBrowserItem *browserItem = m_browser->addProperty(item_property);
//    m_browser->setExpanded(browserItem, false);

//    QtProperty *property = m_variantManager->addProperty(QVariant::String, tr("Name"));
//    property->setValue(material->getName());
//    addProperty(property, JobQueueXML::JobNameAttribute);

}



void MaterialPropertyBrowser::removeSubProperties(QtProperty *property)
{
    qDebug() << "MaterialEditorWidget::updateMaterialProperties" << property->propertyName();
    QList<QtProperty *> properties = property->subProperties();
    foreach(QtProperty *child, properties) {
        m_browser->removeProperty(child);
        delete child;

        QMap<QtProperty *, SubItem >::iterator it = m_property_to_subitem.find(child);
        //delete it.value();
        m_property_to_subitem.erase(it);

        QMap<SubItem, QtProperty * >::iterator it2 = m_subitem_to_property.find(it.value());
        m_subitem_to_property.erase(it2);


    }





}


void MaterialPropertyBrowser::addSubProperties(QtProperty *material_property, MaterialItem *material)
{
    Q_ASSERT(material_property);
    Q_ASSERT(material);

//    QtVariantProperty *subProperty = m_variantManager->addProperty(QVariant::String, "Name");
//    subProperty->setValue(material->getName());
//    material_property->addSubProperty(subProperty);

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
            if(type == QVariant::Double) {
                subProperty->setAttribute(QLatin1String("singleStep"), 0.1);
                subProperty->setAttribute(QLatin1String("decimals"), 5);
            }

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
        SubItem subitem(material,prop_name);
        m_property_to_subitem[subProperty] = subitem;
        m_subitem_to_property[subitem] = subProperty;

        m_material_to_property[material][prop_name] = subProperty;
    }



}


void MaterialPropertyBrowser::updateSubProperties(MaterialItem *material)
{
    qDebug() << "MaterialEditorWidget::updateSubProperties" << material->getName();
    if(m_material_to_property.contains(material)) {

        QMap<QString, QtVariantProperty *> mmm = m_material_to_property[material];
//        for(QMap<QString, QtVariantProperty *> ::iterator it=mmm.begin(); it!=mmm.end(); ++it) {
//            qDebug() << "ooo " << it.key() << it.value();
//        }

        QList<QByteArray> property_names = material->dynamicPropertyNames();
        for (int i = 0; i < property_names.length(); ++i) {
            QString prop_name = QString(property_names[i]);
            QVariant prop_value = material->property(prop_name.toUtf8().data());
            qDebug() << "oooo2" << prop_name << prop_value;

            if(mmm.contains(prop_name)) {
                QtVariantProperty *vproperty = mmm[prop_name];
                if (material->getSubItems().contains(prop_name)) {
                    vproperty->setValue(prop_value);
                }
            }


        }

    }
}


void MaterialPropertyBrowser::updateExpandState(ExpandAction action)
{
    QMap<QtProperty *, SubItem>::iterator it_prop = m_property_to_subitem.begin();
    while(it_prop!=m_property_to_subitem.end()) {
        QList<QtBrowserItem *> list = m_browser->items(it_prop.key());

        QListIterator<QtBrowserItem *> it_browser(list);
        while (it_browser.hasNext()) {
            QtBrowserItem *item = it_browser.next();
            QtProperty *prop = item->property();
            if(action == SaveExpandState) {
                m_subItemToExpanded[m_property_to_subitem[prop]] = m_browser->isExpanded(item);
            } else if (action == RestoreExpandState) {
                m_browser->setExpanded(item, m_subItemToExpanded[m_property_to_subitem[prop]]);
            }
        }

        ++it_prop;
    }
}


void MaterialPropertyBrowser::onCurrentBrowserItemChanged(QtBrowserItem * /*item*/)
{
    // nasty hack due to the absence of "selection" singnal in QtPropertyBrowser
    static bool first_call = true;
    if(first_call) {
        first_call = false;
        m_browser->setCurrentItem(0);

    }
}


MaterialItem *MaterialPropertyBrowser::getSelectedMaterial()
{
    qDebug() << "MaterialPropertyBrowser::getSelectedMaterial";

    if(m_browser->currentItem()) {
        qDebug() << "MaterialPropertyBrowser::getSelectedMaterial 1.1";
        QtProperty *selected_property = m_browser->currentItem()->property();
        if(selected_property) {
            qDebug() << "MaterialPropertyBrowser::getSelectedMaterial 1.2";
            if(m_top_property_to_material.contains(selected_property))
                return m_top_property_to_material[selected_property];
        }
    }
    qDebug() << "MaterialPropertyBrowser::getSelectedMaterial 1.3";

    return 0;
}

