// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Models/SessionModel.h
//! @brief     Defines class SessionModel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SESSIONMODEL_H
#define SESSIONMODEL_H

#include <QAbstractItemModel>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#include "ParameterizedItem.h"

namespace SessionXML {
const QString ItemTag("Item");
const QString ModelTypeAttribute("ModelType");
const QString ParameterTag("Parameter");
const QString ParameterNameAttribute("Name");
const QString ParameterValueAttribute("Value");
}

class SessionModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit SessionModel(QObject *parent=0);
    ~SessionModel();

    // Begin overriden methods from QAbstractItemModel
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    bool setHeaderData(int, Qt::Orientation, const QVariant&,
                       int=Qt::EditRole) { return false; }
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRows(int row, int count, const QModelIndex &parent);

    Qt::DropActions supportedDragActions() const
        { return Qt::MoveAction; }
    Qt::DropActions supportedDropActions() const
        { return Qt::MoveAction; }
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action,
                         int row, int column, const QModelIndex &parent) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                      int row, int column, const QModelIndex &parent);
    // End overriden methods from QAbstractItemModel

    QModelIndex indexOfItem(ParameterizedItem *item) const;
    ParameterizedItem *insertNewItem(QString model_type,
                                     const QModelIndex &parent=QModelIndex(),
                                     int row=-1);
    QString filename() const { return m_filename; }
    void setFilename(const QString &filename) {
        m_filename = filename;
    }

    QList<QString> getAcceptableChildItems(const QModelIndex &parent) const;

    void clear();
    void load(const QString &filename=QString());
    void save(const QString &filename=QString());

private:
    ParameterizedItem *insertNewItem(QString model_type,
                                     ParameterizedItem *parent,
                                     int row=-1);
    ParameterizedItem *itemForIndex(const QModelIndex &index) const;
    void readItems(QXmlStreamReader *reader, ParameterizedItem *item,
                   int row=-1);
    void writeItemAndChildItems(QXmlStreamWriter *writer,
                                ParameterizedItem *item) const;
    QString m_filename;
    ParameterizedItem *m_root_item;
};

#endif // SESSIONMODEL_H
