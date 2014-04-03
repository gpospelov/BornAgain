// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/SessionModel.cpp
//! @brief     Implements class SessionModel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SessionModel.h"
#include "ItemFactory.h"
#include "GUIHelpers.h"

#include <QFile>
#include <QMimeData>
#include <QDebug>

namespace {
const int MaxCompression = 9;
enum Column {
    ItemName,
    ModelType,
    MaxColumns
};
}

SessionModel::SessionModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(0)
    , m_name("DefaultName")
{
}

SessionModel::~SessionModel()
{
    delete m_root_item;
}

Qt::ItemFlags SessionModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled
                     |Qt::ItemIsEditable|Qt::ItemIsDragEnabled;
        QList<QString> acceptable_child_items = getAcceptableChildItems(index);
        if (acceptable_child_items.contains(m_dragged_item_type)) {
            result_flags |= Qt::ItemIsDropEnabled;
        }
    }
    else {
        result_flags |= Qt::ItemIsDropEnabled;
    }
    return result_flags;
}

QVariant SessionModel::data(const QModelIndex &index, int role) const
{
    if (!m_root_item || !index.isValid() || index.column() < 0
            || index.column() >= MaxColumns) {
        return QVariant();
    }
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            switch (index.column()) {
            case ItemName: return item->itemName();
            case ModelType: return item->modelType();
            default: return QVariant();
            }
        }
    }
    return QVariant();
}

QVariant SessionModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case ItemName: return tr("Name");
        case ModelType: return tr("Model Type");
        }
    }
    return QVariant();
}

int SessionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return 0;
    ParameterizedItem *parent_item = itemForIndex(parent);
    return parent_item ? parent_item->childItemCount() : 0;
}

int SessionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0) return 0;
    return MaxColumns;
}

QModelIndex SessionModel::index(int row, int column,
                                const QModelIndex &parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= MaxColumns
            || (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    ParameterizedItem *parent_item = itemForIndex(parent);
    if (ParameterizedItem *item = parent_item->childAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}

QModelIndex SessionModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) return QModelIndex();
    if (ParameterizedItem *child_item = itemForIndex(child)) {
        if (ParameterizedItem *parent_item = child_item->parent()) {
            if (parent_item == m_root_item) return QModelIndex();
            if (ParameterizedItem *grandparent_item = parent_item->parent())
            {
                int row = grandparent_item->rowOfChild(parent_item);
                return createIndex(row, 0, parent_item);
            }
        }
    }
    return QModelIndex();
}

bool SessionModel::setData(const QModelIndex &index,
                           const QVariant &value, int role)
{
    if (!index.isValid() || index.column()!=ItemName) return false;
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role==Qt::EditRole) {
            item->setItemName(value.toString());
        }
        else return false;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool SessionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!m_root_item) return false;
    ParameterizedItem *item = parent.isValid() ? itemForIndex(parent)
                                               : m_root_item;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i=0; i<count; ++i) {
        delete item->takeChildItem(row);
    }
    endRemoveRows();
    return true;
}

QStringList SessionModel::mimeTypes() const
{
    return QStringList() << SessionXML::MimeType;
}

QMimeData *SessionModel::mimeData(const QModelIndexList &indices) const
{
    if (indices.count() != 2) return 0;
    if (ParameterizedItem *item = itemForIndex(indices.at(0))) {
        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::MimeType,
                           qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}

bool SessionModel::canDropMimeData(const QMimeData *data, Qt::DropAction action,
                                   int row, int column,
                                   const QModelIndex &parent) const
{
    (void)row;
    if (action == Qt::IgnoreAction) return true;
    if (action != Qt::MoveAction || column > 0 || !data
            || !data->hasFormat(SessionXML::MimeType)) return false;
    if (!parent.isValid()) return true;
    QList<QString> acceptable_child_items = getAcceptableChildItems(parent);
    QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type = reader.attributes()
                        .value(SessionXML::ModelTypeAttribute).toString();
                return acceptable_child_items.contains(model_type);
            }
        }
    }
    return false;
}

bool SessionModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction) return true;
    if (action != Qt::MoveAction || column > 0 || !data
            || !data->hasFormat(SessionXML::MimeType)) return false;
    if (!canDropMimeData(data, action, row, column, parent)) return false;
    if (ParameterizedItem *item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
        QXmlStreamReader reader(xml_data);
        if (row == -1) row = item->childItemCount();
        beginInsertRows(parent, row, row);
        readItems(&reader, item, row);
        endInsertRows();
        return true;
    }
    return false;
}

QModelIndex SessionModel::indexOfItem(ParameterizedItem *item) const
{
    if (!item || item == m_root_item) return QModelIndex();
    ParameterizedItem *parent_item = item->parent();
    int row = parent_item->rowOfChild(item);
    return createIndex(row, 0, item);
}

ParameterizedItem *SessionModel::insertNewItem(QString model_type,
                                               const QModelIndex &parent,
                                               int row)
{
    if (!m_root_item) {
        m_root_item = ItemFactory::createEmptyItem();
    }
    ParameterizedItem *parent_item = itemForIndex(parent);
    if (row==-1) row = parent_item->childItemCount();
    beginInsertRows(parent, row, row);
    ParameterizedItem *new_item = insertNewItem(model_type, parent_item, row);
    endInsertRows();
    return new_item;
}

QList<QString> SessionModel::getAcceptableChildItems(
        const QModelIndex &parent) const
{
    QList<QString> result;
    if (ParameterizedItem *parent_item = itemForIndex(parent)) {
        result = parent_item->acceptableChildItems();
    }
    return result;
}

void SessionModel::clear()
{
    beginResetModel();
    delete m_root_item;
    m_root_item = 0;
    endResetModel();
}

void SessionModel::load(const QString &filename)
{
    beginResetModel();
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw GUIHelpers::Error(tr("no filename specified"));
    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());
    clear();
    m_root_item = ItemFactory::createEmptyItem();
    QXmlStreamReader reader(&file);
    readItems(&reader, m_root_item);
    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
    endResetModel();
}


void SessionModel::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);

    if(reader->name() != SessionXML::ModelTag) {
        throw GUIHelpers::Error("SessioneModel::readFrom() -> Format error in p1");
    }

    beginResetModel();
    clear();

    m_name = reader->attributes()
            .value(SessionXML::ModelNameAttribute).toString();

    m_root_item = ItemFactory::createEmptyItem();

    readItems(reader, m_root_item);
    if (reader->hasError())
        throw GUIHelpers::Error(reader->errorString());
    endResetModel();

}


void SessionModel::save(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;
    if (m_filename.isEmpty())
        throw GUIHelpers::Error(tr("no filename specified"));
    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", "1.9");
    writeItemAndChildItems(&writer, m_root_item);
    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();
}


void SessionModel::writeTo(QXmlStreamWriter *writer)
{
    writer->writeStartElement(SessionXML::ModelTag);
    writer->writeAttribute(SessionXML::ModelNameAttribute, m_name);

    writeItemAndChildItems(writer, m_root_item);

    writer->writeEndElement(); // ModelTag
}


ParameterizedItem *SessionModel::insertNewItem(QString model_type,
                                               ParameterizedItem *parent,
                                               int row)
{
    if (!m_root_item) {
        m_root_item = ItemFactory::createEmptyItem();
    }
    if (!parent) parent = m_root_item;
    if (row == -1) row = parent->childItemCount();
    if (row < 0 || row > parent->childItemCount()) return 0;
    if (parent != m_root_item) {
        if (!parent->acceptsAsChild(model_type))
            return 0;
    }
    ParameterizedItem *new_item = ItemFactory::createItem(model_type);
    parent->insertChildItem(row, new_item);
    return new_item;
}

ParameterizedItem *SessionModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (ParameterizedItem *item = static_cast<ParameterizedItem *>(
                    index.internalPointer()))
            return item;
    }
    return m_root_item;
}

void SessionModel::readItems(QXmlStreamReader *reader, ParameterizedItem *item,
                             int row)
{
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                const QString model_type = reader->attributes()
                        .value(SessionXML::ModelTypeAttribute).toString();
                item = insertNewItem(model_type, item, row);
                const QString item_name = reader->attributes()
                        .value(SessionXML::ItemNameAttribute).toString();
                item->setItemName(item_name);
                row = -1; // all but the first item should be appended
            }
            else if (reader->name() == SessionXML::ParameterTag) {
                readProperty(reader, item);
            }
        }
        else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                item = item->parent();
            }
            if (reader->name() == SessionXML::ModelTag) {
                break;
            }
        }
    }
}


void SessionModel::readProperty(QXmlStreamReader *reader, ParameterizedItem *item)
{
    const QString parameter_name = reader->attributes()
            .value(SessionXML::ParameterNameAttribute)
            .toString();
    const QString parameter_type = reader->attributes()
            .value(SessionXML::ParameterTypeAttribute)
            .toString();
    if (parameter_type == "double") {
        double parameter_value = reader->attributes()
                .value(SessionXML::ParameterValueAttribute)
                .toDouble();
        item->setProperty(parameter_name.toUtf8().constData(),
                          parameter_value);
    }
    else {
        throw GUIHelpers::Error(tr("SessionModel::readProperty: "
                                   "Parameter type not supported"));
    }
}

void SessionModel::writeItemAndChildItems(QXmlStreamWriter *writer,
                                          ParameterizedItem *item) const
{
    if (item != m_root_item) {
        writer->writeStartElement(SessionXML::ItemTag);
        writer->writeAttribute(SessionXML::ModelTypeAttribute,
                               item->modelType());
        writer->writeAttribute(SessionXML::ItemNameAttribute,
                               item->itemName());
        QListIterator<QByteArray> it(item->dynamicPropertyNames());
        while (it.hasNext()) {
            const char *name = it.next().constData();
            writeProperty(writer, item, name);
        }
    }
    foreach (ParameterizedItem *child_item, item->childItems()) {
        writeItemAndChildItems(writer, child_item);
    }
    if (item != m_root_item) {
        writer->writeEndElement(); // ItemTag
    }
}

void SessionModel::writeProperty(QXmlStreamWriter *writer,
                                 ParameterizedItem *item,
                                 const char *property_name) const
{
    QVariant variant = item->property(property_name);
    if (variant.isValid()) {
        writer->writeStartElement(SessionXML::ParameterTag);
        writer->writeAttribute(SessionXML::ParameterNameAttribute,
                               QString(property_name));
        writer->writeAttribute(SessionXML::ParameterTypeAttribute,
                               QString(variant.typeName()) );
        switch (variant.type()) {
        case QMetaType::Double:
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                QString::number(variant.toDouble(), 'e', 12));
            break;
        default:
            throw GUIHelpers::Error(tr("SessionModel::writeProperty: "
                                       "Parameter type not supported"));
        }
        writer->writeEndElement(); // end ParameterTag
    }
}



void SessionModel::moveParameterizedItem(ParameterizedItem *item, ParameterizedItem *new_parent, int row)
{
    qDebug() << "";
    qDebug() << "";
    qDebug() << "SessionModel::moveParameterizedItem() " << item << new_parent << row;

    if(!new_parent) new_parent = m_root_item;

    if(item->parent() == new_parent && indexOfItem(item).row() == row) {
        qDebug() << "SessionModel::moveParameterizedItem() -> no need to move, same parent, same raw. ";
        return;
    }

    QByteArray xml_data;
    QXmlStreamWriter writer(&xml_data);
    writeItemAndChildItems(&writer, item);

    QXmlStreamReader reader(xml_data);
    if (row == -1) row = new_parent->childItemCount();

    qDebug() << "    >>> Beginning to insert indexOfItem(new_parent)" << indexOfItem(new_parent);
    beginInsertRows(indexOfItem(new_parent), row, row);
    readItems(&reader, new_parent, row);
    endInsertRows();

    qDebug() << "    >>> Now deleting indexOfItem(item).row()" << indexOfItem(item).row();

    removeRows(indexOfItem(item).row(), 1, indexOfItem(item->parent()));

}
