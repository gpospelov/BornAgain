#include "MaterialItem.h"
#include "MaterialModel.h"
#include "MaterialUtils.h"
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
        qDebug() << "MaterialItem::setMaterialProperty" << QString(property_names[i]);
        if(name == QString(property_names[i])) {
            setProperty(name.toAscii().data(), value);
            return true;
        }
    }
    throw GUIHelpers::Error("MaterialItem::setMaterialProperty() -> No property "+name);
}


void MaterialItem::setType(MaterialType type)
{
    m_type = type;
    updateProperties();
}


void MaterialItem::setType(QString typeName)
{
    int index = m_type_names.indexOf(typeName);
    if(index == -1)
        throw GUIHelpers::Error("MaterialItem::setType() -> Error. Wrong typeName"+typeName);

    setType(MaterialType(index));
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
        if(name == MaterialProperties::Name) {
            m_name = property(MaterialProperties::Name).toString();
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
    if(!property(MaterialProperties::Color).isValid()) {
        ColorProperty mat_color = MaterialUtils::suggestMaterialColorProperty(getName());
        QVariant mat_color_var;
        mat_color_var.setValue(mat_color);
        setProperty(MaterialProperties::Color, mat_color_var);
    }
}


// to handle changes in RefractiveIndexItem and MagneticFieldItem
void MaterialItem::onPropertyItemChanged(QString propertyName)
{
    qDebug() << "MaterialItem::onPropertyItemChanged() " << propertyName;
    MaterialItem *property = qobject_cast<MaterialItem *>(sender());
    if(property && property != this) {
        QString subItemName = property->getName();
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
        else if (type_name == QString("ColorProperty")) {
            int r, g, b, a;
            QColor material_color = variant.value<ColorProperty>().getColor();
            material_color.getRgb(&r, &g, &b, &a);
            writer->writeAttribute(MaterialXML::MaterialColorRedAttribute, QString::number(r));
            writer->writeAttribute(MaterialXML::MaterialColorGreenAttribute, QString::number(g));
            writer->writeAttribute(MaterialXML::MaterialColorBlueAttribute, QString::number(b));
            writer->writeAttribute(MaterialXML::MaterialColorAlphaAttribute, QString::number(a));
        }
        else {
            throw GUIHelpers::Error("MaterialItem::writeProperty: "
                                       "Parameter type not supported"+type_name);
        }
        writer->writeEndElement(); // end ParameterTag
    }
}


void MaterialItem::writeSubProperty(QXmlStreamWriter *writer,
                                     MaterialItem *item) const
{
    writer->writeStartElement(MaterialXML::PropertyTag);
    writer->writeAttribute(MaterialXML::PropertyNameAttribute,
                           item->getName());
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

    if(reader->name() != MaterialXML::MaterialTag) {
        throw GUIHelpers::Error("JobQueueItem::readFrom() -> Format error in p1");
    }

    QString typeName = reader->attributes().value(MaterialXML::MaterialTypeAttribute).toString();
    setType(typeName);

    QString name = reader->attributes().value(MaterialXML::MaterialNameAttribute).toString();
    setName(name);

    MaterialItem *material = this;

    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {

            if (reader->name() == MaterialXML::ParameterTag) {
                readProperty(reader, material);

            } else if(reader->name() == MaterialXML::PropertyTag) {
                const QString property_name = reader->attributes()
                                .value(MaterialXML::PropertyNameAttribute)
                                .toString();
                if(!m_sub_items.contains(property_name)) {
                    throw GUIHelpers::Error("MaterialItem::readFrom -> format error at p1");
                }
                material = m_sub_items[property_name];
            }

        } else if (reader->isEndElement()) {
            if (reader->name() == MaterialXML::MaterialTag) {
                break; // end of xml of current Material
            } else if(reader->name() == MaterialXML::MaterialTag) {
                material = this; // end of SubItem
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

    qDebug() << "       " << parameter_name << parameter_type;

    if (parameter_type == "double") {
        double parameter_value = reader->attributes()
                .value(MaterialXML::ParameterValueAttribute)
                .toDouble();
        item->setMaterialProperty(parameter_name, parameter_value);

    }
    else if (parameter_type == "QString") {
        QString parameter_value = reader->attributes()
                .value(MaterialXML::ParameterValueAttribute)
                .toString();
        item->setMaterialProperty(parameter_name, parameter_value);
    }
    else if (parameter_type == "ColorProperty") {
        int r = reader->attributes().value(MaterialXML::MaterialColorRedAttribute).toInt();
        int g = reader->attributes().value(MaterialXML::MaterialColorGreenAttribute).toInt();
        int b = reader->attributes().value(MaterialXML::MaterialColorBlueAttribute).toInt();
        int a = reader->attributes().value(MaterialXML::MaterialColorAlphaAttribute).toInt();
        ColorProperty color(QColor(r, g, b, a));
        QVariant color_variant;
        color_variant.setValue(color);
        item->setProperty(MaterialProperties::Color, color_variant);
    }
    else {
        throw GUIHelpers::Error("MaterialItem::readProperty: "
                                   "Parameter type not supported"+parameter_type);
    }
    return parameter_name;
}


void MaterialItem::setRefractiveIndex(double delta, double beta)
{
    if(!property(MaterialProperties::RefractiveIndex.toAscii().data()).isValid())
        throw GUIHelpers::Error("MaterialItem::setRefractiveIndex() -> Error! No such property");

    m_sub_items[MaterialProperties::RefractiveIndex]->setMaterialProperty("delta", QString::number(delta));
    m_sub_items[MaterialProperties::RefractiveIndex]->setMaterialProperty("beta", QString::number(beta));
}

