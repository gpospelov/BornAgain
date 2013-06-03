#include "MaterialBrowserModel.h"
#include "DesignerHelper.h"
#include "MaterialManager.h"
#include <QColor>

MaterialBrowserModel::MaterialBrowserModel(QObject *parent)
    : QAbstractTableModel(parent)
{    
    std::cout << "MaterialBrowserModel XXX 1.1 " << std::endl;
    addMaterial("Air", 1., 0.);
    std::cout << "MaterialBrowserModel XXX 1.2 " << std::endl;
    addMaterial("Substrate", 1-6e-6, 2e-8);
    std::cout << "MaterialBrowserModel XXX 1.3 " << std::endl;
    addMaterial("Default", 1., 0.);
    std::cout << "MaterialBrowserModel XXX 1.4 " << std::endl;
}


void MaterialBrowserModel::addMaterial(const char *name, double index_real, double index_imag)
{
    const IMaterial *m = MaterialManager::getHomogeneousMaterial(name, index_real, index_imag);
    m_mat_color[m] = DesignerHelper::getRandomColor();
    m_nraw_mat.append(m);
}


int MaterialBrowserModel::rowCount(const QModelIndex & /*parent*/) const
 {
    return m_nraw_mat.size();
 }


int MaterialBrowserModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return 4;
 }


QVariant MaterialBrowserModel::data(const QModelIndex &index, int role) const
{
    std::cout << "MaterialBrowserModel::data() -> 1.1" << std::endl;
    const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nraw_mat.at(index.row()));
    if( !mat ) {
        std::cout << " MaterialBrowserModel::data() -> Panic" << std::endl;
        return QVariant();
    }
    std::cout << "MaterialBrowserModel::data() -> 1.2" << std::endl;

    if (role == Qt::DisplayRole)
    {
        std::cout << "MaterialBrowserModel::data() -> 1.3 " << index.row() << " " << m_nraw_mat.at(index.row()) << std::endl;
        const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nraw_mat.at(index.row()));
        if( !mat ) {
            std::cout << " MaterialBrowserModel::data() -> Panic" << std::endl;
            return QVariant();
        }
        std::cout << "XXX " << mat << " " << mat->getName() << " " << mat->getRefractiveIndex().real()<< std::endl;
        switch(index.column()) {
        case 0:
            return QString(mat->getName().c_str());
        case 1:
            return QString::number(mat->getRefractiveIndex().real());
        case 2:
            return QString::number(mat->getRefractiveIndex().imag());
        case 3:
            return QString();
        default:
            return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
        }
    } else if (role == Qt::DecorationRole && index.column() == 0) {
        return m_mat_color[mat];
    }
    return QVariant();
}


QVariant MaterialBrowserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Name");
            case 1:
                return QString("Index::real");
            case 2:
                return QString("Index::imag");
            case 3:
                return QString("Comment");
            }
        } else if (orientation == Qt::Vertical) {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}


