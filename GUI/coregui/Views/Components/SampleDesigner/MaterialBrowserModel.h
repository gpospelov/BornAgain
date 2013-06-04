#ifndef MATERIALBROWSERMODEL_H
#define MATERIALBROWSERMODEL_H


#include <QAbstractTableModel>
#include <QMap>
#include <QVector>

class IMaterial;

//! Model responsible for representation of MaterialManager in QTableView
class MaterialBrowserModel : public QAbstractTableModel
{    
    Q_OBJECT
public:
    enum MaterialProperties {
        MaterialName,
        MaterialIndexReal,
        MaterialIndexImag,
        MaterialTitle,
        NumberOfMaterialProperties
    };

    MaterialBrowserModel(QObject *parent);
    ~MaterialBrowserModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const;

public slots:
    void UpdateMaterials();
    void RemoveMaterial(int nrow);

private:
    QColor getMaterialColor(const QString &name);

    QMap<const IMaterial *, QColor> m_mat_color;
    QVector<const IMaterial *> m_nrow_mat;
};

#endif // MATERIALBROWSERMODEL_H
