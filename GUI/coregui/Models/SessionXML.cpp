// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModel.cpp
//! @brief     Implements class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SessionXML.h"
#include "ParameterizedItem.h"
#include "SessionModel.h"
#include "MaterialProperty.h"
#include "ComboProperty.h"
#include "GroupProperty.h"
#include "ScientificDoubleProperty.h"
#include "ColorProperty.h"
#include "AngleProperty.h"
#include "GUIHelpers.h"
#include "ItemFactory.h"
#include "GroupItem.h"

#include <QXmlStreamWriter>
#include <QDebug>


void SessionWriter::writeTo(QXmlStreamWriter *writer, ParameterizedItem *parent)
{
    writer->writeStartElement(parent->model()->getModelTag());
    writer->writeAttribute(SessionXML::ModelNameAttribute, parent->model()->getModelName());

    writeItemAndChildItems(writer, parent);

    writer->writeEndElement(); // m_model_tag
}

void SessionWriter::writeItemAndChildItems(QXmlStreamWriter *writer, const ParameterizedItem *item)
{
    qDebug() << "SessionModel::writeItemAndChildItems " << item;
    Q_ASSERT(item);
    if (item->parent()) {
        writer->writeStartElement(SessionXML::ItemTag);
        writer->writeAttribute(SessionXML::ModelTypeAttribute, item->modelType());
        writer->writeAttribute(SessionXML::TagAttribute, item->parent()->tagFromItem(item));
        /*if (item->isRegisteredProperty(ParameterizedItem::P_NAME)) {
            writer->writeAttribute(SessionXML::ItemNameAttribute, item->itemName());
        } else {
            writer->writeAttribute(SessionXML::ParameterNameAttribute, item->itemName());
        }*/
        QVector<int> roles = item->getRoles();
        foreach(int role, roles) {
            if (role == Qt::DisplayRole || role == Qt::EditRole)
                writeVariant(writer, item->value(), role);
        }

    }
    foreach (ParameterizedItem *child_item, item->childItems()) {
        writeItemAndChildItems(writer, child_item);
    }
    if (item->parent()) {
        writer->writeEndElement(); // ItemTag
    }
}

void SessionWriter::writeVariant(QXmlStreamWriter *writer, QVariant variant, int role)
{
    if (variant.isValid()) {
        writer->writeStartElement(SessionXML::ParameterTag);
        QString type_name = variant.typeName();
        writer->writeAttribute(SessionXML::ParameterTypeAttribute, type_name);
        writer->writeAttribute(SessionXML::ParameterRoleAttribute, QString::number(role));
        if (type_name == QString("double")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toDouble(), 'e', 12));
        } else if (type_name == QString("int")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toInt()));
        } else if (type_name == QString("bool")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(variant.toBool()));
        } else if (type_name == QString("QString")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute, variant.toString());
        } else if (type_name == QString("MaterialProperty")) {
            MaterialProperty material_property = variant.value<MaterialProperty>();
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   material_property.getName());
            writer->writeAttribute(SessionXML::IdentifierAttribute,
                                   material_property.getIdentifier());

        } else if (type_name == QString("ComboProperty")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   variant.value<ComboProperty>().getValue());
        } else if (type_name == QString("ScientificDoubleProperty")) {
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   variant.value<ScientificDoubleProperty>().getText());

        } else if (type_name == QString("GroupProperty_t")) {
            QString ff_name = variant.value<GroupProperty_t>()->getCurrentType();
            writer->writeAttribute(SessionXML::ParameterValueAttribute, ff_name);
        } else if (type_name == QString("ColorProperty")) {
            int r, g, b, a;
            QColor material_color = variant.value<ColorProperty>().getColor();
            material_color.getRgb(&r, &g, &b, &a);
            writer->writeAttribute(SessionXML::ColorRedAttribute, QString::number(r));
            writer->writeAttribute(SessionXML::ColorGreenAttribute, QString::number(g));
            writer->writeAttribute(SessionXML::ColorBlueAttribute, QString::number(b));
            writer->writeAttribute(SessionXML::ColorAlphaAttribute, QString::number(a));
        } else if (type_name == QString("AngleProperty")) {
            double value = variant.value<AngleProperty>().getValueInRadians();
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(value, 'g'));
            writer->writeAttribute(SessionXML::AngleUnitsAttribute,
                                   variant.value<AngleProperty>().getUnits());
        } else {
            throw GUIHelpers::Error("SessionModel::writeProperty: Parameter type not supported " + type_name);
        }
        writer->writeEndElement(); // end ParameterTag
    }
}

void SessionReader::readItems(QXmlStreamReader *reader, ParameterizedItem *item, int row)
{
    qDebug() << "SessionModel::readItems() " << row;
    if(item) qDebug() << "  item" << item->modelType();
    const QString modelType = item->model()->getModelTag();
//    bool inside_parameter_tag = false;
//    QString parent_parameter_name;
//    ParameterizedItem *parent_backup(0);
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                const QString model_type
                    = reader->attributes().value(SessionXML::ModelTypeAttribute).toString();
                QString tag = reader->attributes().value(SessionXML::TagAttribute).toString();
                /*QString item_name;
                bool setItemName = false;
                if (reader->attributes().hasAttribute(SessionXML::ItemNameAttribute)) {
                    item_name = reader->attributes().value(SessionXML::ItemNameAttribute).toString();
                    setItemName = true;
                } else {
                    item_name = reader->attributes().value(SessionXML::ParameterNameAttribute).toString();
                }*/
                if (model_type == Constants::PropertyType || model_type == Constants::GroupItemType) {
                    item = item->getItem(tag);
                    if (!item) {
                        qDebug() << "!!";
                    }
                } else if (item->modelType() == Constants::GroupItemType) {
                    item = item->parent()->getGroupItem(item->parent()->tagFromItem(item), model_type);
                    if (!item) {
                        qDebug() << "!!";
                    }
                } else {
                    ParameterizedItem *new_item = ItemFactory::createItem(model_type);
                    if (tag == "rootTag")
                        tag = item->defaultTag();
                    if (!item->insertItem(-1, new_item, tag)) {
                        qDebug() << "!!";
                    }
                    item = new_item;
                }
                if (!item) {
                    row = -1;
                }

                row = -1; // all but the first item should be appended

//                if (inside_parameter_tag) {
//                    Q_ASSERT(item);
//                    ParameterizedItem *parent = item;
//                    item = parent->getGroupItem(parent_parameter_name);
//                    if(!item) {
//                        // to provide partial loading of obsolete project files
//                        QString message = QString("Non existing SubItem '%1' of '%2'")
//                                          .arg(parent_parameter_name).arg(parent->modelType());
////                        report_error(NON_EXISTING_SUBITEM, message);
//                        parent_backup = parent;
//                    }
//                } else {

//                }
            } else if (reader->name() == SessionXML::ParameterTag) {
                /*parent_parameter_name = */readProperty(reader, item);
//                inside_parameter_tag = true;
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                if(item) {
                    item = item->parent();
                } else {
                    // handling the case when reading obsolete project file, when SubItem doesn't exist anymore
//                    item = parent_backup;
//                    parent_backup = 0;
                    qDebug() << "!!";
                }
            }
            if (reader->name() == modelType) {
                break;
            }
            if (reader->name() == SessionXML::ParameterTag) {
//                inside_parameter_tag = false;
            }
        }
    }
}

QString SessionReader::readProperty(QXmlStreamReader *reader, ParameterizedItem *item)
{
//    qDebug() << "SessionModel::readProperty() for" << item;
    if (item)
        qDebug() << item->modelType();
    const QString parameter_name
        = reader->attributes().value(SessionXML::ParameterNameAttribute).toString();
    const QString parameter_type
        = reader->attributes().value(SessionXML::ParameterTypeAttribute).toString();
    const int role
            = reader->attributes().value(SessionXML::ParameterRoleAttribute).toInt();
    // qDebug() << "           SessionModel::readProperty " << item->itemName() << item->modelType()
    // << parameter_name << parameter_type << parameter_name.toUtf8().constData();

    if(!item) {
        QString message = QString("Attempt to set property '%1' for non existing item")
                          .arg(parameter_name);
//        report_error(ITEM_IS_NOT_INITIALIZED, message);
        return parameter_name;
    }

//    if(!item->isRegisteredProperty(parameter_name)) {
//        QString message = QString("Unknown property '%1' for item type '%2'")
//                          .arg(parameter_name).arg(item->modelType());
////        report_error(SET_ITEM_PROPERTY_ERROR, message);
//        return parameter_name;
//    }
    QVariant variant;
    if (parameter_type == "double") {
        double parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toDouble();
        variant = parameter_value;
//        item->setRegisteredProperty(parameter_name, parameter_value);

    } else if (parameter_type == "int") {
        int parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        variant = parameter_value;
//        item->setRegisteredProperty(parameter_name, parameter_value);
    } else if (parameter_type == "bool") {
        bool parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toInt();
        variant = parameter_value;
//        item->setRegisteredProperty(parameter_name, parameter_value);

    } else if (parameter_type == "QString") {
        QString parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toString();
        variant = parameter_value;
//        item->setRegisteredProperty(parameter_name, parameter_value);

    } else if (parameter_type == "MaterialProperty") {
        QString identifier = reader->attributes().value(SessionXML::IdentifierAttribute).toString();

        MaterialProperty material_property(identifier);
        variant = material_property.getVariant();
//        item->setProperty(parameter_name.toUtf8().constData(), material_property.getVariant());
    } else if (parameter_type == "ComboProperty") {
        QString parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toString();

        ComboProperty combo_property
            = item->value().value<ComboProperty>();
        if (combo_property.getValues().contains(parameter_value)) {
            combo_property.setValue(parameter_value);
        }
        combo_property.setCachedValue(parameter_value);
        variant = combo_property.getVariant();
//        item->setRegisteredProperty(parameter_name, combo_property.getVariant());
    } else if (parameter_type == "ScientificDoubleProperty") {
        double parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toDouble();

        ScientificDoubleProperty scdouble_property(parameter_value);
        QVariant v;
        v.setValue(scdouble_property);
        variant = v;
//        item->setRegisteredProperty(parameter_name, v);
    } else if (parameter_type == "GroupProperty_t") {
        QString parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toString();

        GroupProperty_t group_property
            = item->value().value<GroupProperty_t>();
        group_property->setCurrentType(parameter_value);
        variant = QVariant::fromValue<GroupProperty_t>(group_property);
    } else if (parameter_type == "ColorProperty") {
        int r = reader->attributes().value(SessionXML::ColorRedAttribute).toInt();
        int g = reader->attributes().value(SessionXML::ColorGreenAttribute).toInt();
        int b = reader->attributes().value(SessionXML::ColorBlueAttribute).toInt();
        int a = reader->attributes().value(SessionXML::ColorAlphaAttribute).toInt();
        ColorProperty color(QColor(r, g, b, a));
//        item->setRegisteredProperty(parameter_name, color.getVariant());
        variant = color.getVariant();
    } else if (parameter_type == "AngleProperty") {
        double parameter_value
            = reader->attributes().value(SessionXML::ParameterValueAttribute).toDouble();
        QString units = reader->attributes().value(SessionXML::AngleUnitsAttribute).toString();
        AngleProperty angle_property(parameter_value, Constants::UnitsRadians);
        angle_property.setUnits(units);
        variant = angle_property.getVariant();
//        item->setRegisteredProperty(parameter_name, angle_property.getVariant());
    }

    else {
        throw GUIHelpers::Error("SessionModel::readProperty: "
                                "Parameter type not supported" + parameter_type);
    }
    if (variant.isValid()) {
        item->setData(role, variant);
    }

    return parameter_name;
}
