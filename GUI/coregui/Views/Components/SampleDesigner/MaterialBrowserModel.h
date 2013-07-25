#ifndef MATERIALBROWSERMODEL_H
#define MATERIALBROWSERMODEL_H


#include <QAbstractTableModel>
#include <QMap>
#include <QVector>
#include "MaterialBrowser.h"

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

    void resetSelection() { m_selected_row = -1; }
    bool hasSelection() { return (m_selected_row >= 0 ? true : false); }
    MaterialProperty getSelectedMaterialProperty();
    MaterialProperty getDefaultMaterialProperty();

public slots:
    void UpdateMaterials();
    void RemoveMaterials(const QModelIndexList &index_list);

signals:
    void SetDataMessage(const QString &message);

private:
    QColor suggestMaterialColor(const QString &name);
    double getDoubleValue(const QVariant &variant, bool &status);
    double evaluateDoubleValue(const QVariant &variant, bool &status);

    QMap<const IMaterial *, QColor> m_mat_color;
    QVector<const IMaterial *> m_nrow_mat;
    int m_selected_row;
};

#endif // MATERIALBROWSERMODEL_H
