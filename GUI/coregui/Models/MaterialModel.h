#ifndef MATERIALMODEL_H
#define MATERIALMODEL_H

#include "MaterialItem.h"
#include <QAbstractTableModel>
#include <QList>
#include <QString>
class QXmlStreamWriter;


namespace MaterialXML
{
    const QString ModelTag("MaterialModel");
    const QString ModelNameAttribute("Name");
    const QString MaterialTag("Material");
    const QString MaterialNameAttribute("Name");
    const QString MaterialTypeAttribute("Type");
//    const QString PropertyTag("Property");
//    const QString PropertyNameAttribute("Name");

    const QString ParameterTag("Parameter");
    const QString ParameterNameAttribute("ParName");
    const QString ParameterTypeAttribute("ParType");
    const QString ParameterValueAttribute("ParValue");

    const QString MaterialColorRedAttribute("Red");
    const QString MaterialColorGreenAttribute("Green");
    const QString MaterialColorBlueAttribute("Blue");
    const QString MaterialColorAlphaAttribute("Alpha");

}


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

    MaterialItem *addMaterial(const QString &name, MaterialItem::MaterialType type);
    bool removeMaterial(MaterialItem *);

    void save(const QString &filename=QString());
    void writeTo(QXmlStreamWriter *writer);

//    void load(const QString &filename=QString());
//    void readFrom(QXmlStreamReader *reader);


    QList<MaterialItem *> materials() const { return m_materials; }

private:
    QList<MaterialItem *> m_materials;
    QString m_name;
};

#endif

