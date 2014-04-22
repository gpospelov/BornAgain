#include "MaterialItem.h"
#include "MaterialModel.h"
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QXmlStreamWriter>
#include "GUIHelpers.h"

QStringList MaterialItem::m_type_names = QStringList()
        << QString("Homogeneous Material")
        << QString("Homogeneous Magnetic Material")
        << QString("Material Property");

MaterialItem::MaterialItem(const QString &name, MaterialType type)
    : m_name(name)
    , m_type(type)
    , m_color(Qt::red)
{
    updateProperties();
}


MaterialItem::~MaterialItem()
{
    qDeleteAll(m_sub_items);
}


QStringList MaterialItem::getMaterialTypes() const
{
    QStringList result = m_type_names;
    result.removeLast();
    return result;
}


bool MaterialItem::setMaterialProperty(QString name, const QVariant &value)
{
    //Q_ASSERT(dynamicPropertyNames().contains(name));
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
        qDebug() << "zzzz " << QString(property_names[i]);
        if(name == QString(property_names[i])) {
            setProperty(name.toAscii().data(), value);
            return true;
        }
    }
    throw GUIHelpers::Error("MaterialItem::setMaterialProperty() -> No property "+name);
}


void MaterialItem::setType(MaterialType type)
{
    qDebug() << "MaterialItem::setType";
    m_type = type;
    updateProperties();
}


// emmits signal on property change
bool MaterialItem::event(QEvent * e )
{
    if(e->type() == QEvent::DynamicPropertyChange) {
        QDynamicPropertyChangeEvent *propertyEvent =
                dynamic_cast<QDynamicPropertyChangeEvent *>(e);
        Q_ASSERT(e);
        QByteArray byte_array = propertyEvent->propertyName();
        QString name(byte_array.constData());
        if (m_sub_items.contains(name)) {
            //updatePropertyItem(name);
        }
        qDebug() << "MaterialItem::event(QEvent * e ) property changed" << name;
        emit propertyChanged(name);
    }
    return QObject::event(e);
}



void MaterialItem::updateProperties()
{
    if(m_type == HomogeneousMaterial) {
        setProperty("Name", m_name);
        addColorProperty();
        addSubProperty(MaterialProperties::RefractiveIndex);
        removeSubProperty(MaterialProperties::MagneticField);
    }

    if(m_type == HomogeneousMagneticMaterial) {
        setProperty("Name", m_name);
        addColorProperty();
        addSubProperty(MaterialProperties::RefractiveIndex);
        addSubProperty(MaterialProperties::MagneticField);
    }
}


void MaterialItem::addSubProperty(QString name)
{
    if(m_sub_items.contains(name)) return;

    MaterialItem *item(0);
    if(name == MaterialProperties::RefractiveIndex) {
        item = new RefractiveIndexItem();
    } else if(name == MaterialProperties::MagneticField) {
        item = new MagneticFieldProperty();
    }
    if(item) {
        setProperty(item->getName().toUtf8().data(), item->getTitleString());
        m_sub_items[item->getName()] = item;
        connect(item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyItemChanged(QString)));
    }
}


void MaterialItem::removeSubProperty(QString name)
{
    QMap<QString, MaterialItem *>::iterator it=m_sub_items.find(name);
    if(it!=m_sub_items.end()) {
        delete it.value();
        m_sub_items.erase(it);
        setProperty(name.toUtf8().data(), QVariant(QVariant::Invalid));
    }
}


void MaterialItem::addColorProperty()
{
    MaterialColorProperty mat_color;
    QVariant mat_color_var;
    mat_color_var.setValue(mat_color);
    setProperty(MaterialProperties::Color.toUtf8().data(), mat_color_var);
}


void MaterialItem::onPropertyItemChanged(QString propertyName)
{
    qDebug() << "MaterialItem::onPropertyItemChanged() " << propertyName;
    MaterialItem *property = qobject_cast<MaterialItem *>(sender());
    if(property) {
        QString subItemName = property->getName();
        qDebug() << " xx setting title string" << subItemName << property->getTitleString();
        setMaterialProperty(subItemName, property->getTitleString());
    }
}




void MaterialItem::writeTo(QXmlStreamWriter *writer)
{
    writer->writeStartElement(MaterialXML::MaterialTag);
    writer->writeAttribute(MaterialXML::MaterialTypeAttribute, getTypeName());
    writer->writeAttribute(MaterialXML::MaterialNameAttribute, property("Name").toString());

//    QMap<QString, MaterialItem *>::iterator it = m_sub_items.begin();
//    while(it!=m_sub_items.end()) {
//        it.value()->writeTo(writer);
//        ++it;
//    }

    QListIterator<QByteArray> it(dynamicPropertyNames());
    while (it.hasNext()) {
        const char *name = it.next().constData();
        if( QString(name) == MaterialProperties::Name) continue;
        writeProperty(writer, this, name);
    }



    writer->writeEndElement(); // MaterialTag

}


void MaterialItem::writeProperty(QXmlStreamWriter *writer, MaterialItem *item, const char *property_name) const
{
    qDebug() << "MaterialItem::writeProperty() " << property_name;
    QMap<QString, MaterialItem *> sub_items = item->getSubItems();
    QVariant variant = item->property(property_name);
    qDebug() << "XXX " << variant.typeName();
    if (variant.isValid()) {        
        writer->writeStartElement(MaterialXML::ParameterTag);
        writer->writeAttribute(MaterialXML::ParameterNameAttribute,
                               QString(property_name));
        QString type_name = variant.typeName();
        writer->writeAttribute(MaterialXML::ParameterTypeAttribute,
                               type_name );
        if (type_name == QString("double")) {
            writer->writeAttribute(MaterialXML::ParameterValueAttribute,
                                QString::number(variant.toDouble(), 'e', 12));
        }
        else if (type_name == QString("QString")) {
            writer->writeAttribute(MaterialXML::ParameterValueAttribute,
                                variant.toString());
        }
        else if (type_name == QString("MaterialColorProperty")) {
            int r, g, b, a;
            QColor material_color = variant.value<MaterialColorProperty>().getColor();
            material_color.getRgb(&r, &g, &b, &a);
            writer->writeAttribute(MaterialXML::MaterialColorRedAttribute, QString::number(r));
            writer->writeAttribute(MaterialXML::MaterialColorGreenAttribute, QString::number(g));
            writer->writeAttribute(MaterialXML::MaterialColorBlueAttribute, QString::number(b));
            writer->writeAttribute(MaterialXML::MaterialColorAlphaAttribute, QString::number(a));
        }
//        else if (type_name == QString("FormFactorProperty")) {
//            QString ff_name =
//                    variant.value<FormFactorProperty>().getFormFactorName();
//            writer->writeAttribute(MaterialXML::ParameterValueAttribute,
//                                ff_name);
//        }
        else {
            qDebug() << "MaterialItem::writeProperty() -> Error! Property not supported" << property_name;
//            throw GUIHelpers::Error(tr("MaterialItem::writeProperty: "
//                                       "Parameter type not supported"));
        }
        if (sub_items.contains(QString(property_name))) {
            writeSubProperty(writer, sub_items[QString(property_name)]);
        }
        writer->writeEndElement(); // end ParameterTag
    }



}


void MaterialItem::writeSubProperty(QXmlStreamWriter *writer,
                                     MaterialItem *item) const
{
    writer->writeStartElement(MaterialXML::MaterialTag);
    writer->writeAttribute(MaterialXML::MaterialTypeAttribute,
                           item->getTypeName());
    writer->writeAttribute(MaterialXML::MaterialNameAttribute,
                           item->getName());
    QListIterator<QByteArray> it(item->dynamicPropertyNames());
    while (it.hasNext()) {
        const char *name = it.next().constData();
        writeProperty(writer, item, name);
    }
//    foreach (ParameterizedItem *child_item, item->childItems()) {
//        writeItemAndChildItems(writer, child_item);
//    }
    writer->writeEndElement(); // ItemTag
}





//void RefractiveIndexItem::writeTo(QXmlStreamWriter *writer)
//{
////    writer->writeStartElement(MaterialXML::PropertyTag);
////    writer->writeAttribute(MaterialXML::PropertyNameAttribute, getName());


////    writer->writeEndElement(); // MaterialTag

//}

//void MagneticFieldProperty::writeTo(QXmlStreamWriter *writer)
//{
////    writer->writeStartElement(MaterialXML::PropertyTag);
////    writer->writeAttribute(MaterialXML::PropertyNameAttribute, getName());


////    writer->writeEndElement(); // MaterialTag

//}




