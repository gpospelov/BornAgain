#include "MaterialItem.h"
#include "MaterialModel.h"
#include "MaterialProperty.h"
#include <QDynamicPropertyChangeEvent>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "GUIHelpers.h"

QStringList MaterialItem::m_type_names = QStringList()
        << QString("Homogeneous Material")
        << QString("Homogeneous Magnetic Material")
        << QString("Material Property");

MaterialItem::MaterialItem(const QString &name, MaterialType type)
    : m_name(name)
    , m_type(type)
{
    updateProperties();
}


MaterialItem::~MaterialItem()
{
    qDeleteAll(m_sub_items);
}


MaterialProperty MaterialItem::getMaterialProperty()
{
    QVariant v = property(MaterialProperties::Color.toAscii().data());
    MaterialColorProperty colorProperty = v.value<MaterialColorProperty>();
    return MaterialProperty(getName(), colorProperty.getColor());
}


void MaterialItem::setName(const QString &name)
{
    m_name = name;
    setMaterialProperty(MaterialProperties::Name, name);
}



QStringList MaterialItem::getMaterialTypes() const
{
    QStringList result = m_type_names;
    result.removeLast();
    return result;
}


bool MaterialItem::setMaterialProperty(QString name, const QVariant &value)
{
    QList<QByteArray> property_names = dynamicPropertyNames();
    for (int i = 0; i < property_names.length(); ++i) {
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


void MaterialItem::setType(QString typeName)
{
    qDebug() << "MaterialItem::setType" << typeName;
    int index = m_type_names.indexOf(typeName);
    if(index == -1)
        throw GUIHelpers::Error("MaterialItem::setType() -> Error. Wrong typeName"+typeName);

    m_type = MaterialType(index);
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
//        if (m_sub_items.contains(name)) {
//            //updatePropertyItem(name);
//        }
        if(name == MaterialProperties::Name) {
            m_name = property(MaterialProperties::Name.toUtf8().data()).toString();
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
    writer->writeAttribute(MaterialXML::MaterialNameAttribute, getName());

    QListIterator<QByteArray> it(dynamicPropertyNames());
    while (it.hasNext()) {
        const char *name = it.next().constData();
        if( QString(name) == MaterialProperties::Name || m_sub_items.contains(name)) continue;
        writeProperty(writer, this, name);
    }

    foreach(MaterialItem *item, m_sub_items) {
        writeSubProperty(writer, item);
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
        else {
            qDebug() << "MaterialItem::writeProperty() -> Error! Property not supported" << property_name;
//            throw GUIHelpers::Error(tr("MaterialItem::writeProperty: "
//                                       "Parameter type not supported"));
        }
//        if (sub_items.contains(QString(property_name))) {
//            writeSubProperty(writer, sub_items[QString(property_name)]);
//        }
        writer->writeEndElement(); // end ParameterTag
    }



}


void MaterialItem::writeSubProperty(QXmlStreamWriter *writer,
                                     MaterialItem *item) const
{
    writer->writeStartElement(MaterialXML::PropertyTag);
    writer->writeAttribute(MaterialXML::PropertyNameAttribute,
                           item->getName());
//    writer->writeAttribute(MaterialXML::MaterialNameAttribute,
//                           item->getName());
    QListIterator<QByteArray> it(item->dynamicPropertyNames());
    while (it.hasNext()) {
        const char *name = it.next().constData();
        writeProperty(writer, item, name);
    }
    writer->writeEndElement(); // ItemTag
}



void MaterialItem::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);

    qDebug() << "MaterialItem::readFrom() -> " << reader->name();
    if(reader->name() != MaterialXML::MaterialTag) {
        throw GUIHelpers::Error("JobQueueItem::readFrom() -> Format error in p1");
    }

    QString typeName = reader->attributes().value(MaterialXML::MaterialTypeAttribute).toString();
    setType(typeName);

    QString name = reader->attributes().value(MaterialXML::MaterialNameAttribute).toString();
    setName(name);
    //setMaterialProperty(MaterialProperties::Name, name);
    qDebug() << "     name:" << name;


    MaterialItem *material = this;

    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {

//            if (reader->name() == JobQueueXML::OutputDataTag) {
//                qDebug() << "JobItem::readFrom() -> output data";
//                OutputDataItem *item = new OutputDataItem();
//                item->readFrom(reader);
//                m_data_items.append(item);
//            }
            qDebug() << "       reader->name():" << reader->name();
            if (reader->name() == MaterialXML::ParameterTag) {
                readProperty(reader, material);

            } else if(reader->name() == MaterialXML::PropertyTag) {
                const QString property_name = reader->attributes()
                                .value(MaterialXML::PropertyNameAttribute)
                                .toString();
                qDebug() << "property_name " << property_name;
                if(!m_sub_items.contains(property_name)) {
                    throw GUIHelpers::Error("MaterialItem::readFrom -> format error at p1");
                }
                material = m_sub_items[property_name];
                //readProperty(reader, material);

            }


        } else if (reader->isEndElement()) {
            if (reader->name() == MaterialXML::MaterialTag) {
                break; // end of xml of current Material
            } else if(reader->name() == MaterialXML::MaterialTag) {
                material = this;
            }
        }
    }

}


QString MaterialItem::readProperty(QXmlStreamReader *reader, MaterialItem *item)
{
    const QString parameter_name = reader->attributes()
            .value(MaterialXML::ParameterNameAttribute)
            .toString();
    const QString parameter_type = reader->attributes()
            .value(MaterialXML::ParameterTypeAttribute)
            .toString();
    qDebug() << "MaterialItem::readProperty " << parameter_name << parameter_type;
    if (parameter_type == "double") {
        double parameter_value = reader->attributes()
                .value(MaterialXML::ParameterValueAttribute)
                .toDouble();
//        item->setProperty(parameter_name.toUtf8().constData(),
//                          parameter_value);
        item->setMaterialProperty(parameter_name, parameter_value);

    }
    else if (parameter_type == "QString") {
        QString parameter_value = reader->attributes()
                .value(MaterialXML::ParameterValueAttribute)
                .toString();
//        item->setProperty(parameter_name.toUtf8().constData(),
//                          parameter_value);
        item->setMaterialProperty(parameter_name, parameter_value);
    }
    else if (parameter_type == "MaterialColorProperty") {
        QString parameter_value = reader->attributes()
                .value(MaterialXML::ParameterValueAttribute)
                .toString();
//        QVariant mat_variant;
//        mat_variant.setValue(MaterialBrowser::getMaterialProperty());
//        item->setProperty(parameter_name.toUtf8().constData(), mat_variant);
    }
    else {
        throw GUIHelpers::Error(tr("MaterialItem::readProperty: "
                                   "Parameter type not supported"));
    }
    return parameter_name;
}


