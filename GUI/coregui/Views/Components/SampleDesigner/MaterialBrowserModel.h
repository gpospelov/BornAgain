#ifndef MATERIALBROWSERMODEL_H
#define MATERIALBROWSERMODEL_H


#include <QAbstractTableModel>
#include <QMap>

class IMaterial;

class MaterialBrowserModel : public QAbstractTableModel
{
public:
    MaterialBrowserModel(QObject *parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
//    struct MaterialData {
//        QColor color;
//    };
    void addMaterial(const char *name, double index_real, double index_imag);

    QMap<const IMaterial *, QColor> m_mat_color;
    QVector<const IMaterial *> m_nraw_mat;
};

#endif // MATERIALBROWSERMODEL_H
