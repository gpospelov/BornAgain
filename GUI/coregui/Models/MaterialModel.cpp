#include "MaterialModel.h"
#include "MaterialItem.h"
#include "GUIHelpers.h"
#include "DesignerHelper.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>


MaterialModel::MaterialModel(QObject *parent)
    : QAbstractTableModel(parent)
    , m_name("DefaultName")
{

}


MaterialModel::~MaterialModel()
{
    qDeleteAll(m_materials);
}


int MaterialModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_materials.size();
}


int MaterialModel::columnCount(const QModelIndex & /*parent*/) const
{
    return NumberOfColumns;
}


QVariant MaterialModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row <0 && row >= m_materials.size() ) return QVariant();

    if (role == Qt::DisplayRole)
    {
        switch(index.column()) {
        case MaterialName:
            return m_materials.at(row)->getName();
        case MaterialType:
            return m_materials.at(row)->getTypeName();
        default:
            return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
        }
    }


    return QVariant();

}


QVariant MaterialModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case MaterialName:
                return QString("Name");
            case MaterialType:
                return QString("Type");
            default:
                return QString();
            }
        } else if (orientation == Qt::Vertical) {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}



MaterialItem *MaterialModel::addMaterial(const QString &name, MaterialItem::MaterialType type)
{
    int position = m_materials.size();
    beginInsertRows(QModelIndex(), position, position);
    MaterialItem *result = new MaterialItem(name, type);
    m_materials.append(result);
    endInsertRows();
    return result;
}


bool MaterialModel::removeMaterial(MaterialItem *material)
{
    if(m_materials.contains(material)) {
        int row = m_materials.indexOf(material);
        beginRemoveRows(QModelIndex(), row, row);
        m_materials.removeOne(material);
        delete material;
        endRemoveRows();
        return true;
    }
    Q_ASSERT(0);
    return false;
}


void MaterialModel::save(const QString &filename)
{
    if (filename.isEmpty())
        throw GUIHelpers::Error(tr("no filename specified"));
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", "1.9");

    writeTo(&writer);

    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();

}


void MaterialModel::writeTo(QXmlStreamWriter *writer)
{
    Q_ASSERT(writer);

    writer->writeStartElement(MaterialXML::ModelTag);
    writer->writeAttribute(MaterialXML::ModelNameAttribute, getName());

    foreach(MaterialItem *material, m_materials) {
        material->writeTo(writer);
    }
    writer->writeEndElement(); // ModelTag
}


void MaterialModel::clear()
{
    beginResetModel();
    qDeleteAll(m_materials);
    m_materials.clear();
    endResetModel();
}


void MaterialModel::load(const QString &filename)
{
    if (filename.isEmpty())
        throw GUIHelpers::Error(tr("no filename specified"));

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());


    QXmlStreamReader reader(&file);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == MaterialXML::ModelTag) {
                this->readFrom(&reader);
                break;
            }
        }
    }

    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());

}


void MaterialModel::readFrom(QXmlStreamReader *reader)
{
    if(reader->name() != MaterialXML::ModelTag) {
        throw GUIHelpers::Error("MaterialModel::readFrom() -> Format error in p1");
    }

    clear();
    beginResetModel();
    const QString name = reader->attributes()
            .value(MaterialXML::ModelNameAttribute).toString();
    qDebug() << "JobQueueModel::readFrom " << name;
    setName(name);

    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == MaterialXML::MaterialTag) {

                MaterialItem *material = addMaterial("Default", MaterialItem::HomogeneousMaterial);
                material->readFrom(reader);

            } else {
                qDebug() << "qqq   " << reader->name();
                throw GUIHelpers::Error("MaterialModel::readFrom() -> Format error in p2");
            }
        } else if (reader->isEndElement()) {
            if (reader->name() == MaterialXML::ModelTag) {
                endResetModel();
                break; // end of xml of current Job
            }
        }
    }
}


MaterialItem *MaterialModel::getMaterial(const QString &name)
{
    foreach(MaterialItem *item, m_materials) {
        if(item->getName() == name) return item;
    }
    return 0;
}



