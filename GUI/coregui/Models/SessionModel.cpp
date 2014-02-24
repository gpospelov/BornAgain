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

namespace {
const int MaxCompression = 9;
enum Column {
    ItemName,
    ModelType,
    MaxColumns
};
const QString MimeType = "application/org.bornagainproject.xml.item.z";
}

SessionModel::SessionModel(QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(0)
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
                     |Qt::ItemIsEditable|Qt::ItemIsDragEnabled
                     |Qt::ItemIsDropEnabled;
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
            case ItemName: return item->getItemName();
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
    if (ParameterizedItem *item = parent_item->getChildAt(row)) {
        return createIndex(row, column, item);
    }
    return QModelIndex();
}

QModelIndex SessionModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) return QModelIndex();
    if (ParameterizedItem *child_item = itemForIndex(child)) {
        if (ParameterizedItem *parent_item = child_item->getParent()) {
            if (parent_item == m_root_item) return QModelIndex();
            if (ParameterizedItem *grandparent_item = parent_item->getParent())
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
    return QStringList() << MimeType;
}

QMimeData *SessionModel::mimeData(const QModelIndexList &indices) const
{
    if (indices.count() != 2) return 0;
    if (ParameterizedItem *item = itemForIndex(indices.at(0))) {
        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        writeItemAndChildItems(&writer, item);
        mime_data->setData(MimeType, qCompress(xml_data, MaxCompression));
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
            || !data->hasFormat(MimeType)) return false;
    if (!parent.isValid()) return true;
    QList<QString> acceptable_child_items = getAcceptableChildItems(parent);
    QByteArray xml_data = qUncompress(data->data(MimeType));
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
            || !data->hasFormat(MimeType)) return false;
    if (!canDropMimeData(data, action, row, column, parent)) return false;
    if (ParameterizedItem *item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(MimeType));
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
    ParameterizedItem *parent_item = item->getParent();
    int row = parent_item->rowOfChild(item);
    return createIndex(row, 0, item);
}

ParameterizedItem *SessionModel::insertNewItem(QString model_type,
                                               const QModelIndex &parent,
                                               int row)
{
    if (!m_root_item) {
        m_root_item = new ParameterizedItem;
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
        result = parent_item->getAcceptableChildren();
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
    m_root_item = new ParameterizedItem;
    QXmlStreamReader reader(&file);
    readItems(&reader, m_root_item);
    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
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

ParameterizedItem *SessionModel::insertNewItem(QString model_type,
                                               ParameterizedItem *parent,
                                               int row)
{
    if (!m_root_item) {
        m_root_item = new ParameterizedItem;
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
                const QString parameter_name = reader->attributes()
                        .value(SessionXML::ParameterNameAttribute)
                        .toString();
                double parameter_value = reader->attributes()
                        .value(SessionXML::ParameterValueAttribute)
                        .toDouble();
                item->setParameter(parameter_name, parameter_value);
            }
        }
        else if (reader->isEndElement()) {
            if (reader->name() == SessionXML::ItemTag) {
                item = item->getParent();
            }
        }
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
                               item->getItemName());
        QMapIterator<QString, double> it(item->getParameters());
        while (it.hasNext()) {
            it.next();
            writer->writeStartElement(SessionXML::ParameterTag);
            writer->writeAttribute(SessionXML::ParameterNameAttribute,
                                   it.key());
            writer->writeAttribute(SessionXML::ParameterValueAttribute,
                                   QString::number(it.value(), 'g', 12) );
            writer->writeEndElement(); // ParameterTag
        }
    }
    foreach (ParameterizedItem *child_item, item->childItems()) {
        writeItemAndChildItems(writer, child_item);
    }
    if (item != m_root_item) {
        writer->writeEndElement(); // ItemTag
    }
}
