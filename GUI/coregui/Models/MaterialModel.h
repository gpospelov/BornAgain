#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "MaterialItem.h"
#include <QAbstractTableModel>
#include <QList>


class MaterialModel :public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        MaterialName,
        MaterialType,
        NumberOfColumns
    };

    MaterialModel(QObject *parent = 0);
    ~MaterialModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QString getName() const { return m_name; }
    void setName(QString name) { m_name = name; }

    void addMaterial(const QString &name, MaterialItem::MaterialType type);

    QList<MaterialItem *> materials() const { return m_materials; }

private:
    QList<MaterialItem *> m_materials;
    QString m_name;
};

#endif

