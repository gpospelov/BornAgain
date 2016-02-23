// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SessionModel.h
//! @brief     Defines class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QAbstractItemModel>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "ParameterizedItem.h"

namespace SessionXML
{
const QString MimeType = "application/org.bornagainproject.xml.item.z";
const QString ModelTag("SessionModel");
const QString InstrumentModelTag("InstrumentModel");
const QString SampleModelTag("SampleModel");
const QString MaterialModelTag("MaterialModel");
const QString FitModelTag("FitModel");
const QString JobModelTag("JobModel");
const QString MaskModelTag("MaskModel");

const QString ModelNameAttribute("Name");
const QString ItemTag("Item");
const QString ModelTypeAttribute("ModelType");
const QString ItemNameAttribute("ItemName");
const QString ParameterTag("Parameter");
const QString ParameterNameAttribute("ParName");
const QString ParameterTypeAttribute("ParType");
const QString ParameterValueAttribute("ParValue");

const QString IdentifierAttribute("Identifier");

const QString ColorRedAttribute("Red");
const QString ColorGreenAttribute("Green");
const QString ColorBlueAttribute("Blue");
const QString ColorAlphaAttribute("Alpha");

const QString AngleUnitsAttribute("Units");
}

class IconProvider;
class WarningMessageService;

class /*BA_CORE_API_*/ SessionModel : public QAbstractItemModel
{
    Q_OBJECT
    friend class ParameterizedItem; // NEW
public:
    explicit SessionModel(QString model_tag, QObject *parent = 0);
    virtual ~SessionModel();
    void createRootItem(); //NEW

    enum EColumn {ITEM_NAME, ITEM_VALUE, MAX_COLUMNS}; // NEW column usage

//    // Begin overriden methods from QAbstractItemModel
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    virtual bool setHeaderData(int, Qt::Orientation, const QVariant &, int = Qt::EditRole);
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool removeRows(int row, int count, const QModelIndex &parent);

    virtual Qt::DropActions supportedDragActions() const;
    virtual Qt::DropActions supportedDropActions() const;
    virtual QStringList mimeTypes() const;
    virtual QMimeData *mimeData(const QModelIndexList &indexes) const;
    virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                         const QModelIndex &parent) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column,
                      const QModelIndex &parent);
    // End overridden methods from QAbstractItemModel

    QModelIndex indexOfItem(ParameterizedItem *item) const;
    ParameterizedItem *insertNewItem(QString model_type, const QModelIndex &parent = QModelIndex(),
                                     int row = -1, ParameterizedItem::PortInfo::EPorts port
                                                   = ParameterizedItem::PortInfo::DEFAULT);

    QString getModelTag() const;
    QString getModelName() const;
    void setModelName(const QString &name);

    QList<QString> getAcceptableChildItems(const QModelIndex &parent) const;

    void clear();
    void load(const QString &filename = QString());
    void save(const QString &filename = QString());

    // Sets mimedata pointer of item being dragged
    void setDraggedItemType(const QString &type);

    // Returns root item if index is not valid
    ParameterizedItem *itemForIndex(const QModelIndex &index) const;

    void readFrom(QXmlStreamReader *reader);
    void writeTo(QXmlStreamWriter *writer, ParameterizedItem *parent = 0);

    ParameterizedItem *moveParameterizedItem(ParameterizedItem *item,
                                             ParameterizedItem *new_parent = 0, int row = -1);

    ParameterizedItem *copyParameterizedItem(const ParameterizedItem *item_to_copy,
                                             ParameterizedItem *new_parent = 0, int row = -1);

    void setIconProvider(IconProvider *icon_provider);

    virtual SessionModel *createCopy(ParameterizedItem *parent = 0);

    QMap<QString, ParameterizedItem *> getTopItemMap(const QString &model_type = QString()) const;
    ParameterizedItem *getTopItem(const QString &model_type = QString(),
                                  const QString &item_name = QString()) const;

    void setMessageService(WarningMessageService *messageService);

    virtual void initFrom(SessionModel *model, ParameterizedItem *parent);
    ParameterizedItem* rootItem() const;



public slots:
    void onItemPropertyChange(const QString &property_name, const QString &name = QString());

protected:
    void setRootItem(ParameterizedItem *root) {m_root_item = root;}

private:

    ParameterizedItem *insertNewItem(QString model_type, ParameterizedItem *parent, int row = -1,
                                     ParameterizedItem::PortInfo::EPorts port
                                     = ParameterizedItem::PortInfo::DEFAULT);
    void readItems(QXmlStreamReader *reader, ParameterizedItem *item, int row = -1);
    QString readProperty(QXmlStreamReader *reader, ParameterizedItem *item);
    void writeItemAndChildItems(QXmlStreamWriter *writer, const ParameterizedItem *item) const;
    void writeProperty(QXmlStreamWriter *writer, const ParameterizedItem *item,
                       const char *property_name) const;
    void writePropertyItem(QXmlStreamWriter *writer, ParameterizedItem *item) const;

    void cleanItem(const QModelIndex &parent, int first, int last);

    void report_error(const QString &error_type, const QString &message);

    ParameterizedItem *m_root_item;
    QString m_dragged_item_type;
    QString m_name;      //!< model name
    QString m_model_tag; //!< model tag (SampleModel, InstrumentModel)
    IconProvider *m_iconProvider;
    WarningMessageService *m_messageService;
};

inline bool SessionModel::setHeaderData(int, Qt::Orientation, const QVariant &, int)
{
    return false;
}

inline Qt::DropActions SessionModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

inline Qt::DropActions SessionModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

inline QString SessionModel::getModelTag() const
{
    return m_model_tag;
}

inline QString SessionModel::getModelName() const
{
    return m_name;
}

inline void SessionModel::setModelName(const QString &name)
{
    m_name = name;
}

inline void SessionModel::setDraggedItemType(const QString &type)
{
    m_dragged_item_type = type;
}

inline void SessionModel::setIconProvider(IconProvider *icon_provider)
{
    m_iconProvider = icon_provider;
}

#endif // SESSIONMODEL_H
