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

#include "SessionModel.h"
#include "ItemFactory.h"
#include "GUIHelpers.h"
#include "MaterialEditor.h"
#include "ComboProperty.h"
#include "ScientificDoubleProperty.h"
#include "IconProvider.h"
#include "GroupProperty.h"
#include "MaterialUtils.h"
#include "MaterialProperty.h"
#include "AngleProperty.h"
#include "ParameterizedGraphicsItem.h"
#include "WarningMessageService.h"
#include <QFile>
#include <QMimeData>
#include <QDebug>

namespace
{
const int MaxCompression = 9;
//enum EColumn { ITEM_NAME, MODEL_TYPE, MAX_COLUMNS };

const QString SET_ITEM_PROPERTY_ERROR = "SET_ITEM_PROPERTY_ERROR";
const QString ITEM_IS_NOT_INITIALIZED = "ITEM_IS_NOT_INITIALIZED";
const QString NON_EXISTING_SUBITEM = "NON_EXISTING_SUBITEM";
}

SessionModel::SessionModel(QString model_tag, QObject *parent)
    : QAbstractItemModel(parent)
    , m_root_item(0)
    , m_name("DefaultName")
    , m_model_tag(model_tag)
    , m_iconProvider(0)
    , m_messageService(0)
{
    createRootItem();
}

//NEW
void SessionModel::createRootItem()
{
    m_root_item = ItemFactory::createEmptyItem();
    m_root_item->setData(0, "Name");
    m_root_item->setData(1, "Value");
    m_root_item->setModel(this);
}

SessionModel::~SessionModel()
{
    delete m_root_item;
    delete m_iconProvider;
}

Qt::ItemFlags SessionModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result_flags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        result_flags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled // | Qt::ItemIsEditable
                        | Qt::ItemIsDragEnabled;
        ParameterizedItem *item = itemForIndex(index); // NEW make data editable as default
        if (item->data(index.column()).isValid())      // NEW
            result_flags |= Qt::ItemIsEditable;        // NEW
        QList<QString> acceptable_child_items = getAcceptableChildItems(index);
        if (acceptable_child_items.contains(m_dragged_item_type)) {
            result_flags |= Qt::ItemIsDropEnabled;
        }
    } else {
        result_flags |= Qt::ItemIsDropEnabled;
    }
    return result_flags;
}

QVariant SessionModel::data(const QModelIndex &index, int role) const
{
    if (!m_root_item || !index.isValid() || index.column() < 0 || index.column() >= columnCount(QModelIndex())) {
        return QVariant();
    }
    if (ParameterizedItem *item = itemForIndex(index)) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return item->data(index.column());
        } else if (role == Qt::DecorationRole && m_iconProvider) {
            return m_iconProvider->icon(item->modelType());
        }
    }
    return QVariant();
}

QVariant SessionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section >= 0 && section < columnCount(QModelIndex())) // NEW header data is storedin root item
            return m_root_item->data(section);      // NEW
//        switch (section) {
//        case ITEM_NAME:
//            return tr("Name");
//        case MODEL_TYPE:
//            return tr("Model Type");
//        }
    }
    return QVariant();
}

int SessionModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    ParameterizedItem *parent_item = itemForIndex(parent);
    return parent_item ? parent_item->childItemCount() : 0;
}

int SessionModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    return MAX_COLUMNS;
}

QModelIndex SessionModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_root_item || row < 0 || column < 0 || column >= columnCount(QModelIndex())
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
    if (!child.isValid())
        return QModelIndex();
    if (ParameterizedItem *child_item = itemForIndex(child)) {
        if (ParameterizedItem *parent_item = child_item->parent()) {
            if (parent_item == m_root_item)
                return QModelIndex();
//            if (ParameterizedItem *grandparent_item = parent_item->parent()) {
//                int row = grandparent_item->rowOfChild(parent_item);
                return createIndex(parent_item->childNumber(), 0, parent_item); // CHANGED use new method
//            }
        }
    }
    return QModelIndex();
}

bool SessionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    if (!index.isValid() || index.column() != ITEM_NAME)
    if (!index.isValid()/* || !index.data(role).isValid()*/) // NEW
        return false;
    QModelIndex dataIndex = index;                  // NEW
    if (role == Qt::UserRole) {                     // NEW
        dataIndex = index.sibling(index.row(), 1);  // NEW
    }                                               // NEW
    if (ParameterizedItem *item = itemForIndex(dataIndex)) {
//        if (role == Qt::EditRole) {
//            qDebug() << "SessionModel::setData ";
//            item->setItemName(value.toString());
//        } else
//            return false;
        if (item->setData(dataIndex.column(), value)) { // NEW
//            emit dataChanged(dataIndex, dataIndex);
            return true;
        }
    }
    return false;
}

bool SessionModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (!m_root_item)
        return false;
    ParameterizedItem *item = parent.isValid() ? itemForIndex(parent) : m_root_item;
    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i) {
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
    if (indices.count() != 2)
        return 0;
    if (ParameterizedItem *item = itemForIndex(indices.at(0))) {
        QMimeData *mime_data = new QMimeData;
        QByteArray xml_data;
        QXmlStreamWriter writer(&xml_data);
        SessionWriter::writeItemAndChildItems(&writer, item);
        mime_data->setData(SessionXML::MimeType, qCompress(xml_data, MaxCompression));
        return mime_data;
    }
    return 0;
}

bool SessionModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                                   int column, const QModelIndex &parent) const
{
    (void)row;
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !data || !data->hasFormat(SessionXML::MimeType))
        return false;
    if (!parent.isValid())
        return true;
    QList<QString> acceptable_child_items = getAcceptableChildItems(parent);
    QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
    QXmlStreamReader reader(xml_data);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == SessionXML::ItemTag) {
                const QString model_type
                    = reader.attributes().value(SessionXML::ModelTypeAttribute).toString();
                return acceptable_child_items.contains(model_type);
            }
        }
    }
    return false;
}

bool SessionModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                                const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;
    if (action != Qt::MoveAction || column > 0 || !data || !data->hasFormat(SessionXML::MimeType))
        return false;
    if (!canDropMimeData(data, action, row, column, parent))
        return false;
    if (ParameterizedItem *item = itemForIndex(parent)) {
        QByteArray xml_data = qUncompress(data->data(SessionXML::MimeType));
        QXmlStreamReader reader(xml_data);
        if (row == -1)
            row = item->childItemCount();
        beginInsertRows(parent, row, row);
        SessionReader::readItems(&reader, item, row);
        endInsertRows();
        return true;
    }
    return false;
}

QModelIndex SessionModel::indexOfItem(ParameterizedItem *item) const
{
    if (!item || item == m_root_item)
        return QModelIndex();
    ParameterizedItem *parent_item = item->parent();
//    qDebug() << "OOO indexOfItem:" << item << " parent_item" <<  parent_item << "m_root_item:" << m_root_item;
    int row = parent_item->rowOfChild(item);
    Q_ASSERT(row>=0); // FIXME For Debugging
    return createIndex(row, 0, item);
}

ParameterizedItem *SessionModel::insertNewItem(QString model_type, const QModelIndex &parent,
                                               int row, ParameterizedItem::PortInfo::EPorts port)
{
//    if (!m_root_item) {
//        m_root_item = ItemFactory::createEmptyItem();
//    }
    ParameterizedItem *parent_item = itemForIndex(parent);
    if (row == -1)
        row = parent_item->childItemCount();
    beginInsertRows(parent, row, row);
    ParameterizedItem *new_item = insertNewItem(model_type, parent_item, row, port);
    endInsertRows();

    cleanItem(indexOfItem(parent_item), row, row);
    return new_item;
}

QList<QString> SessionModel::getAcceptableChildItems(const QModelIndex &parent) const
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
    createRootItem();
    endResetModel();
}

void SessionModel::load(const QString &filename)
{
    beginResetModel();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        throw GUIHelpers::Error(file.errorString());
    clear();
    m_root_item = ItemFactory::createEmptyItem();
    QXmlStreamReader reader(&file);
    SessionReader::readItems(&reader, m_root_item);
    if (reader.hasError())
        throw GUIHelpers::Error(reader.errorString());
    endResetModel();
}

void SessionModel::save(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw GUIHelpers::Error(file.errorString());

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("BornAgain");
    writer.writeAttribute("Version", GUIHelpers::getBornAgainVersionString());
    SessionWriter::writeItemAndChildItems(&writer, m_root_item);
    writer.writeEndElement(); // BornAgain
    writer.writeEndDocument();
}

ParameterizedItem *SessionModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (ParameterizedItem *item = static_cast<ParameterizedItem *>(index.internalPointer()))
            return item;
    }
    return m_root_item;
}

void SessionModel::readFrom(QXmlStreamReader *reader)
{
    Q_ASSERT(reader);

    qDebug() << "SessionModel::readFrom()" << m_model_tag << reader->name() << m_root_item;

    if (reader->name() != m_model_tag) {
        throw GUIHelpers::Error("SessionModel::readFrom() -> Format error in p1");
    }

    beginResetModel();
    clear();

    m_name = reader->attributes().value(SessionXML::ModelNameAttribute).toString();

    createRootItem();

    SessionReader::readItems(reader, m_root_item);
    if (reader->hasError())
        throw GUIHelpers::Error(reader->errorString());
    endResetModel();

}

void SessionModel::writeTo(QXmlStreamWriter *writer, ParameterizedItem *parent)
{
    // MOVED OUT TO SessionXML.h

    qDebug() << "SessionModel::writeTo";
    if (!parent)
        parent = m_root_item;
    SessionWriter::writeTo(writer, parent);
}

//! Move given parameterized item to the new_parent at given row. If new_parent is not defined,
//! use root_item as a new parent.
ParameterizedItem *SessionModel::moveParameterizedItem(ParameterizedItem *item, ParameterizedItem *new_parent,
                                         int row)
{
    qDebug() << "";
    qDebug() << "";
    qDebug() << "SessionModel::moveParameterizedItem() " << item << new_parent << row;

    if (new_parent) {
        if (!new_parent->acceptsAsChild(item->modelType()))
            return 0;
    } else {
        new_parent = m_root_item;
    }

    if (item->parent() == new_parent && indexOfItem(item).row() == row) {
        qDebug()
            << "SessionModel::moveParameterizedItem() -> no need to move, same parent, same row. ";
        return item;
    }

    QByteArray xml_data;
    QXmlStreamWriter writer(&xml_data);
    SessionWriter::writeItemAndChildItems(&writer, item);

    QXmlStreamReader reader(xml_data);
    if (row == -1)
        row = new_parent->childItemCount();

    qDebug() << "   SessionModel::moveParameterizedItem()  >>> Beginning to insert "
                "indexOfItem(new_parent)" << indexOfItem(new_parent);
    beginInsertRows(indexOfItem(new_parent), row, row);
    SessionReader::readItems(&reader, new_parent, row);
    endInsertRows();

    ParameterizedItem *newItem = new_parent->childAt(row);

    qDebug() << " ";
    qDebug() << "    SessionModel::moveParameterizedItem() >>> Now deleting indexOfItem(item).row()"
             << indexOfItem(item).row();

    removeRows(indexOfItem(item).row(), 1, indexOfItem(item->parent()));

    cleanItem(indexOfItem(new_parent), row, row);

    return newItem;
}

//! Copy given item to the new_parent at given raw. Item indended for copying can belong to
//! another model and it will remains intact. Returns pointer to the new child.
ParameterizedItem *SessionModel::copyParameterizedItem(const ParameterizedItem *item_to_copy,
                                                       ParameterizedItem *new_parent, int row)
{
    if (new_parent) {
        if (!new_parent->acceptsAsChild(item_to_copy->modelType()))
            return 0;
    } else {
        new_parent = m_root_item;
    }

    QByteArray xml_data;
    QXmlStreamWriter writer(&xml_data);
    SessionWriter::writeItemAndChildItems(&writer, item_to_copy);

    QXmlStreamReader reader(xml_data);
    if (row == -1)
        row = new_parent->childItemCount();

    beginInsertRows(indexOfItem(new_parent), row, row);
    SessionReader::readItems(&reader, new_parent, row);
    endInsertRows();

    return new_parent->childAt(row);
}

SessionModel *SessionModel::createCopy(ParameterizedItem *parent)
{
    (void)parent;
    throw GUIHelpers::Error("SessionModel::createCopy() -> Error. Not implemented.");
}

//! returns map of item name to ParameterizedItem for all top level items in the model
QMap<QString, ParameterizedItem *> SessionModel::getTopItemMap(const QString &model_type) const
{
    QMap<QString, ParameterizedItem *> result;
    QModelIndex parentIndex;
    for (int i_row = 0; i_row < rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = index(i_row, 0, parentIndex);
        if (ParameterizedItem *item = itemForIndex(itemIndex)) {
            if (model_type.isEmpty()) {
                result.insertMulti(item->itemName(), item);
            } else {
                if (item->modelType() == model_type) {
                    result.insertMulti(item->itemName(), item);
                }
            }
        }
    }
    return result;
}

//! returns top level item with given name and model type
ParameterizedItem *SessionModel::getTopItem(const QString &model_type,
                                            const QString &item_name) const
{
    ParameterizedItem *result(0);
    QMap<QString, ParameterizedItem *> item_map = getTopItemMap(model_type);
    if (item_map.size()) {
        if (item_name.isEmpty()) {
            result = item_map.first();
        } else {
            result = item_map[item_name];
        }
    }
    return result;
}

void SessionModel::setMessageService(WarningMessageService *messageService)
{
    m_messageService = messageService;
}

ParameterizedItem *SessionModel::insertNewItem(QString model_type, ParameterizedItem *parent,
                                               int row, ParameterizedItem::PortInfo::EPorts port)
{
//    if (!m_root_item) {
//        m_root_item = ItemFactory::createEmptyItem();
//    }
    if (!parent)
        parent = m_root_item;
    if (row == -1)
        row = parent->childItemCount();
    if (row < 0 || row > parent->childItemCount())
        return 0;
    if (parent != m_root_item) {
        if (!parent->acceptsAsChild(model_type)) {
            qDebug() << "Child of type " << model_type << " not acceptable!\n";
            return 0;
        }
    }

//    ParameterizedItem *new_item = new ParameterizedItem(model_type); // NEW -> item factory!
    ParameterizedItem *new_item = ItemFactory::createItem(model_type);
    if (port != ParameterizedItem::PortInfo::DEFAULT)
        new_item->setPort(port);

    if (!new_item)
        throw GUIHelpers::Error("SessionModel::insertNewItem() -> Wrong model type " + model_type);

    //note: now done by items themselves
//    connect(new_item, SIGNAL(propertyChanged(const QString &)),
//            this, SLOT(onItemPropertyChange(const QString &)));
//    connect(new_item, SIGNAL(subItemChanged(const QString &)),
//            this, SLOT(onItemPropertyChange(const QString &)));
//    connect(new_item, SIGNAL(subItemPropertyChanged(QString,QString)),
//            this, SLOT(onItemPropertyChange(const QString &, const QString &)));

    parent->insertChildItem(row, new_item);

    return new_item;
}

void SessionModel::initFrom(SessionModel *model, ParameterizedItem *parent)
{
    qDebug() << "SessionModel::initFrom() -> " << model->getModelTag() << parent;
    QByteArray byte_array;
    QXmlStreamWriter writer(&byte_array);
    writer.setAutoFormatting(true);

    model->writeTo(&writer);

    QXmlStreamReader reader(byte_array);

    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            readFrom(&reader);
        }
    }
}

void SessionModel::cleanItem(const QModelIndex &parent, int first, int /* last */)
{
    ParameterizedItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    QModelIndex childIndex = index(first, 0, parent);
    ParameterizedItem *childItem = itemForIndex(childIndex);
    Q_ASSERT(childItem);

    ParameterizedItem *candidate_for_removal = parentItem->getCandidateForRemoval(childItem);
    if (candidate_for_removal) {
        // qDebug() << " candidate_for_removal" << candidate_for_removal;
        moveParameterizedItem(candidate_for_removal, 0);
    }
}

//! reports error
void SessionModel::report_error(const QString &error_type, const QString &message)
{
    if(m_messageService) {
        m_messageService->send_message(this, error_type, message);
    } else {
        throw GUIHelpers::Error(error_type + QString(" ") + message);
    }
}

ParameterizedItem* SessionModel::rootItem() const{
    return m_root_item;
}
