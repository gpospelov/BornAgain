// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaterialEditor/MaterialPropertyBrowser.cpp
//! @brief     Implements class MaterialPropertyBrowser
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaterialPropertyBrowser.h"
#include "MaterialModel.h"
#include "MaterialItem.h"
#include "ComboProperty.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "qttreepropertybrowser.h"
#include "tooltipdatabase.h"
#include "ScientificDoubleProperty.h"
#include "GUIHelpers.h"
#include "PropertyAttribute.h"
#include <QtVariantPropertyManager>
#include <QtProperty>
#include <QtVariantProperty>
#include <QtTreePropertyBrowser>
#include <QVBoxLayout>
#include <QDebug>
#include <QEvent>
#include <QApplication>
#include <QTreeWidget>
#include <qtpropertybrowser.h>


MaterialPropertyBrowser::MaterialPropertyBrowser(MaterialModel *materialModel, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(0)
    , m_browser(0)
    , m_variantManager(0)
    , m_selection_changed(false)

{
    m_browser = new QtTreePropertyBrowser(this);
    m_readOnlyManager = new PropertyVariantManager(this);
    m_variantManager = new PropertyVariantManager(this);
//    m_variantFactory = new PropertyVariantFactory(this);
//    m_browser->setFactoryForManager(m_variantManager, m_variantFactory);

    QtVariantEditorFactory *factory = new PropertyVariantFactory();
    m_browser->setFactoryForManager(m_variantManager, factory);


    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);
    setLayout(layout);

    setModel(materialModel);

    // accessing selection model of private QTreeView of m_browser
    QItemSelectionModel *selectionModel(0);
    const QObjectList list = m_browser->children();
    foreach(QObject *obj, list) {
        QTreeView *view = dynamic_cast<QTreeView *>(obj);
        if(view) selectionModel = view->selectionModel();
    }
    if(selectionModel) {
        connect(selectionModel,
            SIGNAL( selectionChanged(const QItemSelection&, const QItemSelection&) ),
            this,
            SLOT( onSelectionChanged(const QItemSelection&, const QItemSelection&) )
            );
    }
}


void MaterialPropertyBrowser::setModel(MaterialModel *materialModel)
{
    Q_ASSERT(materialModel);
    if(materialModel != m_materialModel) {
        m_materialModel = materialModel;
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
    //qDebug() << "MaterialEditorWidget::slotValueChanged" << property << value;

    if (!m_property_to_subitem.contains(property))
        return;

    qDebug() << "MaterialEditorWidget::slotValueChanged() -> 1.1";
    if(m_top_property_to_material.contains(property)) {
        qDebug() << "MaterialEditorWidget::slotValueChanged() -> 1.2";
        MaterialItem *material = dynamic_cast<MaterialItem *>(m_top_property_to_material[property]);
        disconnect(material, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
        material->setMaterialType(value.toInt());
        removeSubProperties(property);
        addSubProperties(property, material);
        connect(material, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));

        return;
    }

    qDebug() << "MaterialEditorWidget::slotValueChanged() -> 1.3";
    //MaterialItem *material = dynamic_cast<MaterialItem *>(m_property_to_subitem[property].m_owner);
    SessionItem *item = m_property_to_subitem[property].m_owner;
    Q_ASSERT(item);
    qDebug() << "MaterialEditorWidget::slotValueChanged() -> 1.4";
    item->setRegisteredProperty(property->propertyName(), value);
    qDebug() << "MaterialEditorWidget::slotValueChanged() -> 1.5";
//    updateMaterialProperties(item);

}

void MaterialPropertyBrowser::onPropertyChanged(const QString &property_name)
{
    SessionItem *parentItem = qobject_cast<SessionItem *>(sender());


    if(m_top_material_to_property.contains(parentItem)) {
        m_top_material_to_property[parentItem]->setPropertyName(parentItem->itemName());
    }


    qDebug() << "MaterialPropertyBrowser::onPropertyChanged()" << property_name << parentItem->modelType();

    QtVariantProperty *variant_property = m_material_to_property[parentItem][property_name];
    if(variant_property) {
        QVariant property_value = parentItem->getRegisteredProperty(property_name);

        disconnect(parentItem, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));

        variant_property->setValue(property_value);

        connect(parentItem, SIGNAL(propertyChanged(QString)),
               this, SLOT(onPropertyChanged(QString)));
    }


}


void MaterialPropertyBrowser::updateBrowser()
{
    Q_ASSERT(m_materialModel);

    QModelIndex parentIndex;
    for( int i_row = 0; i_row < m_materialModel->rowCount( parentIndex); ++i_row) {
         QModelIndex itemIndex = m_materialModel->index( i_row, 0, parentIndex );

         if (MaterialItem *material = dynamic_cast<MaterialItem *>(m_materialModel->itemForIndex(itemIndex))){
             addMaterialProperties(material);
             connect(material, SIGNAL(propertyChanged(QString)),
                    this, SLOT(onPropertyChanged(QString)));

         }
    }
    updateExpandState(RESTORE_EXPAND_STATE);
}


void MaterialPropertyBrowser::clearBrowser()
{
    updateExpandState(SAVE_EXPAND_STATE);
    QMap<QtProperty *, SubItem>::iterator it = m_property_to_subitem.begin();
    while(it!=m_property_to_subitem.end()) {
        delete it.key();
        it++;
    }
    m_property_to_subitem.clear();
    m_top_property_to_material.clear();
    m_top_material_to_property.clear();
    m_material_to_property.clear();
}


//void MaterialPropertyBrowser::updateMaterialProperties(SessionItem *material)
//{
//    if(m_top_material_to_property.contains(material)) {
//        m_top_material_to_property[material]->setPropertyName(material->itemName());
//    }

////    QMap<SessionItem *, QtVariantProperty *>::iterator it = m_top_material_to_property.begin();
////    while(it!=m_top_material_to_property.end()) {
////        updateSubProperties(it.key());
////        ++it;
////    }
//}


void MaterialPropertyBrowser::addMaterialProperties(SessionItem *material)
{
    QtVariantProperty *item_property = m_variantManager->addProperty(
                QtVariantPropertyManager::enumTypeId(), material->itemName());

    ComboProperty combo_property = material->getRegisteredProperty(MaterialItem::P_MATERIAL_TYPE).value<ComboProperty>();

    item_property->setAttribute(QLatin1String("enumNames"), combo_property.getValues());
    item_property->setValue(combo_property.getIndex());

    addSubProperties(item_property, material);
    m_browser->addProperty(item_property);

    m_top_property_to_material[item_property] = material;
    m_top_material_to_property[material] = item_property;
    m_property_to_subitem[item_property] = SubItem(material, "");
}


void MaterialPropertyBrowser::removeSubProperties(QtProperty *property)
{
    qDebug() << "MaterialEditorWidget::updateMaterialProperties" << property->propertyName();
    QList<QtProperty *> properties = property->subProperties();
    foreach(QtProperty *child, properties) {
        m_browser->removeProperty(child);
        delete child;

        QMap<QtProperty *, SubItem >::iterator it = m_property_to_subitem.find(child);
        m_property_to_subitem.erase(it);
    }
}


void MaterialPropertyBrowser::addSubProperties(QtProperty *material_property, SessionItem *item)
{

    QList<QByteArray> property_names = item->dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        QString prop_name = QString(property_names[i]);
        const PropertyAttribute &prop_attribute = PropertyAttribute::fromItem(item);

        if(prop_attribute.isHidden()) continue;

        QVariant prop_value = item->property(prop_name.toUtf8().data());
        int type = GUIHelpers::getVariantType(prop_value);

        QtVariantProperty *subProperty = 0;
        if (m_variantManager->isPropertyTypeSupported(type)) {

            if(prop_attribute.getLabel().isEmpty()) {
                subProperty = m_variantManager->addProperty(type, prop_name);
            } else {
                subProperty = m_variantManager->addProperty(type, prop_attribute.getLabel());
            }

            subProperty->setValue(prop_value);

            QString toolTip = ToolTipDataBase::getSampleViewToolTip(item->modelType(), prop_name);
            if(!toolTip.isEmpty()) subProperty->setToolTip(toolTip);

            if(prop_attribute.isDisabled()) {
                subProperty->setEnabled(false);
            }

            if (item->isGroupProperty(prop_name)) {
                SessionItem *subitem = item->getGroupItem(prop_name);
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
        SubItem subitem(item,prop_name);
        m_property_to_subitem[subProperty] = subitem;
        m_material_to_property[item][prop_name] = subProperty;
    }
}




//void MaterialPropertyBrowser::updateSubProperties(SessionItem *material)
//{
////    if(m_material_to_property.contains(material)) {

////        QList<QByteArray> property_names = material->dynamicPropertyNames();
////        for (int i = 0; i < property_names.length(); ++i) {
////            QString prop_name = QString(property_names[i]);
////            QVariant prop_value = material->property(prop_name.toUtf8().data());

////            if(m_material_to_property[material].contains(prop_name)) {
////                QtVariantProperty *vproperty = m_material_to_property[material][prop_name];
////                if (material->getSubItems().contains(prop_name)) {
////                    vproperty->setValue(prop_value);
////                }
////            }
////        }
////    }
//}


void MaterialPropertyBrowser::updateExpandState(EExpandAction action)
{
    QMap<QtProperty *, SubItem>::iterator it_prop = m_property_to_subitem.begin();
    while(it_prop!=m_property_to_subitem.end()) {
        QList<QtBrowserItem *> list = m_browser->items(it_prop.key());

        QListIterator<QtBrowserItem *> it_browser(list);
        while (it_browser.hasNext()) {
            QtBrowserItem *item = it_browser.next();
            QtProperty *prop = item->property();
            if(action == SAVE_EXPAND_STATE) {
                m_subItemToExpanded[m_property_to_subitem[prop]] = m_browser->isExpanded(item);
            } else if (action == RESTORE_EXPAND_STATE) {
                m_browser->setExpanded(item, m_subItemToExpanded[m_property_to_subitem[prop]]);
            }
        }
        ++it_prop;
    }
}


MaterialItem *MaterialPropertyBrowser::getSelectedMaterial()
{
    if(m_browser->currentItem() && m_selection_changed) {
        QtProperty *selected_property = m_browser->currentItem()->property();
        if(selected_property) {
            if(m_top_property_to_material.contains(selected_property))
                return dynamic_cast<MaterialItem *>(m_top_property_to_material[selected_property]);
       }
    }
    return 0;
}


void MaterialPropertyBrowser::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    m_selection_changed = true;
}
