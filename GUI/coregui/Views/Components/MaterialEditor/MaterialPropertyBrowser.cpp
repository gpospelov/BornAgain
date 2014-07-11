#include "MaterialPropertyBrowser.h"
#include "MaterialModel.h"
#include "PropertyVariantManager.h"
#include "PropertyVariantFactory.h"
#include "qttreepropertybrowser.h"
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


MaterialPropertyBrowser::MaterialPropertyBrowser(MaterialModel *model, QWidget *parent)
    : QWidget(parent)
    , m_materialModel(0)
    , m_browser(0)
    , m_variantManager(0)
    , m_selection_changed(false)

{
    m_browser = new QtTreePropertyBrowser(this);
    m_readOnlyManager = new PropertyVariantManager(this);
    m_variantManager = new PropertyVariantManager(this);
    m_variantFactory = new PropertyVariantFactory(this);

    m_browser->setFactoryForManager(m_variantManager, m_variantFactory);

    connect(m_variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
                this, SLOT(slotValueChanged(QtProperty *, const QVariant &)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_browser);
    setLayout(layout);

    setModel(model);

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

    if(m_top_property_to_material.contains(property)) {
        MaterialItem *material = m_top_property_to_material[property];
        material->setType(MaterialItem::MaterialType(value.toInt()));
        removeSubProperties(property);
        addSubProperties(property, material);
        return;
    }

    MaterialItem *material = m_property_to_subitem[property].m_owner;
    material->setMaterialProperty(property->propertyName(), value);
    updateMaterialProperties(material);

}


void MaterialPropertyBrowser::updateBrowser()
{
    foreach(MaterialItem *material, m_materialModel->materials()) {
        addMaterialProperties(material);
    }
    updateExpandState(RestoreExpandState);
}


void MaterialPropertyBrowser::clearBrowser()
{
    updateExpandState(SaveExpandState);
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


void MaterialPropertyBrowser::updateMaterialProperties(MaterialItem *material)
{
    if(m_top_material_to_property.contains(material)) {
        m_top_material_to_property[material]->setPropertyName(material->property("Name").toString());
    }

    QMap<MaterialItem *, QtVariantProperty *>::iterator it = m_top_material_to_property.begin();
    while(it!=m_top_material_to_property.end()) {
        updateSubProperties(it.key());
        ++it;
    }
}


void MaterialPropertyBrowser::addMaterialProperties(MaterialItem *material)
{
    QtVariantProperty *item_property = m_variantManager->addProperty(
                QtVariantPropertyManager::enumTypeId(), material->getName());

    item_property->setAttribute(QLatin1String("enumNames"), material->getMaterialTypes());
    item_property->setValue(int(material->getType()));

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


void MaterialPropertyBrowser::addSubProperties(QtProperty *material_property, MaterialItem *material)
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
        SubItem subitem(material,prop_name);
        m_property_to_subitem[subProperty] = subitem;
        m_material_to_property[material][prop_name] = subProperty;
    }
}


void MaterialPropertyBrowser::updateSubProperties(MaterialItem *material)
{
    if(m_material_to_property.contains(material)) {

        QList<QByteArray> property_names = material->dynamicPropertyNames();
        for (int i = 0; i < property_names.length(); ++i) {
            QString prop_name = QString(property_names[i]);
            QVariant prop_value = material->property(prop_name.toUtf8().data());

            if(m_material_to_property[material].contains(prop_name)) {
                QtVariantProperty *vproperty = m_material_to_property[material][prop_name];
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


MaterialItem *MaterialPropertyBrowser::getSelectedMaterial()
{
    if(m_browser->currentItem() && m_selection_changed) {
        QtProperty *selected_property = m_browser->currentItem()->property();
        if(selected_property) {
            if(m_top_property_to_material.contains(selected_property))
                return m_top_property_to_material[selected_property];
        }
    }
    return 0;
}


void MaterialPropertyBrowser::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    m_selection_changed = true;
}
