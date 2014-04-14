// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      ParameterizedItem.h
//! @brief     Defines class ParameterizedItem.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterizedItem.h"
#include "Exceptions.h"
#include "MaterialBrowser.h"
#include "FormFactorProperty.h"

#include <QEvent>
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QMetaEnum>
#include <PropertyVariantManager.h>



ParameterizedItem::~ParameterizedItem()
{
    qDeleteAll(m_children);
}

ParameterizedItem *ParameterizedItem::takeChildItem(int row)
{
    ParameterizedItem *item = m_children.takeAt(row);
    item->m_parent = 0;
    return item;
}

bool ParameterizedItem::acceptsAsChild(const QString &child_name) const
{
    return m_valid_children.contains(child_name);
}

// emmits signal on property change
bool ParameterizedItem::event(QEvent * e )
{
    if(e->type() == QEvent::DynamicPropertyChange) {
        QDynamicPropertyChangeEvent *propertyEvent =
                dynamic_cast<QDynamicPropertyChangeEvent *>(e);
        Q_ASSERT(e);
        QByteArray byte_array = propertyEvent->propertyName();
        QString name(byte_array.constData());
        if (m_sub_items.contains(name)) {
            updatePropertyItem(name);
        }
        emit propertyChanged(name);
    }
    return QObject::event(e);
}

void ParameterizedItem::addPropertyItem(QString name, ParameterizedItem *item)
{
    if (!item) return;
    if (m_sub_items.contains(name)) {
        delete m_sub_items[name];
        m_sub_items.remove(name);
    }
    m_sub_items[name] = item;
    item->m_parent = this;
}

ParameterizedItem *ParameterizedItem::createPropertyItem(QString name)
{
    ParameterizedItem *result = 0;
    qDebug() << "CreateSubItem: " << name;
    QByteArray name_byte_array = name.toUtf8();
    QVariant val = property(name_byte_array.constData());
    if (val.userType() == PropertyVariantManager::formFactorTypeId()) {
        FormFactorProperty ff_prop = val.value<FormFactorProperty>();
        result = FormFactorProperty::createFormFactorItem(
                    ff_prop.getFormFactorName());
    }
    return result;
}

ParameterizedItem::ParameterizedItem(const QString &model_type,
                                     ParameterizedItem *parent)
    : m_model_type(model_type)
    , m_parent(parent)
{
    if (m_parent) {
        m_parent->addChildItem(this);
    }
    setItemName(m_model_type);
}

void ParameterizedItem::updatePropertyItem(QString name)
{
    if (!m_sub_items.contains(name)) return;
    ParameterizedItem *item = createPropertyItem(name);
    addPropertyItem(name, item);
    emit propertyItemChanged(name);
}

void ParameterizedItem::setMaterialProperty()
{
    MaterialProperty material = MaterialBrowser::getDefaultMaterialProperty();
    QVariant mat_var;
    mat_var.setValue(material);
    setProperty("Material", mat_var);
}

void ParameterizedItem::addFormFactorProperty(const char *name, QString value)
{
    FormFactorProperty ff_prop(value);
    if (ff_prop.isDefined()) {
        QVariant ff_var;
        ff_var.setValue(ff_prop);
        setProperty(name, ff_var);
    }
    ParameterizedItem *item = createPropertyItem(name);
    addPropertyItem(name, item);
}
