// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionModel.h
//! @brief     Defines class SessionModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include "SessionItem.h"
#include "SessionXML.h"
#include <QStringList>
#include <QtCore/QXmlStreamWriter>

class IconProvider;

class BA_CORE_API_ SessionModel : public QAbstractItemModel
{
    Q_OBJECT
    friend class SessionItem; // NEW
public:
    explicit SessionModel(QString model_tag, QObject *parent = 0);
    virtual ~SessionModel();
    void createRootItem(); //NEW

    enum EColumn {ITEM_NAME, ITEM_VALUE, MAX_COLUMNS}; // NEW column usage

    enum ERoles {ModelTypeRole = Qt::UserRole + 1, FlagRole, DisplayNameRole, LimitsRole,
                 DecimalRole, DefaultTagRole, EndSessionRoles}; // NEW roles

    enum EAppearance {
        VISIBLE = 0x001,
        ENABLED = 0x002,
        EDITABLE = 0x004
    };

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

    QModelIndex indexOfItem(SessionItem *item) const;
    SessionItem *insertNewItem(QString model_type, const QModelIndex &parent = QModelIndex(),
                                     int row = -1, QString tag = QString());

    QString getModelTag() const;
    QString getModelName() const;
    void setModelName(const QString &name);

    QVector<QString> getAcceptableDefaultItemTypes(const QModelIndex &parent) const;

    virtual void clear();
    void load(const QString &filename = QString());
    void save(const QString &filename = QString());

    // Sets mimedata pointer of item being dragged
    void setDraggedItemType(const QString &type);

    // Returns root item if index is not valid
    SessionItem *itemForIndex(const QModelIndex &index) const;

    void readFrom(QXmlStreamReader *reader, WarningMessageService *messageService=0);
    void writeTo(QXmlStreamWriter *writer, SessionItem *parent = 0);

    SessionItem *moveParameterizedItem(SessionItem *item,
                                             SessionItem *new_parent = 0, int row = -1,
                                       const QString &tag = QString());

    SessionItem *copyParameterizedItem(const SessionItem *item_to_copy,
                                             SessionItem *new_parent = 0,
                                             const QString &tag = QString());

    void setIconProvider(IconProvider *icon_provider);

    virtual SessionModel *createCopy(SessionItem *parent = 0);

    SessionItem *topItem(const QString &model_type = QString(),
                         const QString &item_name = QString()) const;
    QList<SessionItem *> topItems(const QString &model_type = QString(),
                                  const QModelIndex &parentIndex = QModelIndex()) const;
    QStringList topItemNames(const QString &model_type = QString(),
                             const QModelIndex &parentIndex = QModelIndex()) const;

    virtual void initFrom(SessionModel *model, SessionItem *parent);
    SessionItem* rootItem() const;

    virtual void loadNonXMLData(const QString &projectDir);
    virtual void saveNonXMLData(const QString &projectDir);

    virtual QVector<SessionItem*> nonXMLData() const;

protected:
    void setRootItem(SessionItem *root) {m_root_item = root;}

private:
    SessionItem *m_root_item;
    QString m_dragged_item_type;
    QString m_name;      //!< model name
    QString m_model_tag; //!< model tag (SampleModel, InstrumentModel)
    std::unique_ptr<IconProvider> m_iconProvider;
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

#endif // SESSIONMODEL_H
