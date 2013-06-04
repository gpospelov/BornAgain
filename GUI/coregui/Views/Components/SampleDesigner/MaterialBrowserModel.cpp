#include "MaterialBrowserModel.h"
#include "DesignerHelper.h"
#include "MaterialManager.h"
#include <QColor>

#if QT_VERSION < 0x050000
#define QStringLiteral QString
#endif

MaterialBrowserModel::MaterialBrowserModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    UpdateMaterials();
}


MaterialBrowserModel::~MaterialBrowserModel()
{
    std::cout << "MaterialBrowserModel::~MaterialBrowserModel()" << std::endl;
}


// collecting info about defined materials
void MaterialBrowserModel::UpdateMaterials()
{
    std::cout << "MaterialBrowserModel::UpdateMaterials() -> nmaterials " << MaterialManager::getNumberOfMaterials() << std::endl;
    for(MaterialManager::iterator it = MaterialManager::instance().begin(); it!= MaterialManager::instance().end(); ++it) {
        const IMaterial *m = (*it).second;
        if(m_mat_color.contains(m)) continue;
        std::cout << " MaterialBrowserModel::UpdateMaterials() -> getting new material " << m->getName() << std::endl;
        m_mat_color[m] = getMaterialColor( QString(m->getName().c_str()) );
        m_nrow_mat.append(m);
    }
    emit layoutChanged();
}


void MaterialBrowserModel::RemoveMaterial(int nrow)
{
    const IMaterial *mat = m_nrow_mat[nrow];
    std::cout << "MaterialBrowserModel::RemoveMaterial(int nrow) -> removing material " << nrow << " " << mat->getName() << std::endl;
    MaterialManager::instance().deleteMaterial(mat->getName());
    m_mat_color.remove(mat);
    m_nrow_mat.remove(nrow);
    emit layoutChanged();
}


int MaterialBrowserModel::rowCount(const QModelIndex & /*parent*/) const
 {
    return MaterialManager::getNumberOfMaterials();
//    return m_nraw_mat.size();
 }


int MaterialBrowserModel::columnCount(const QModelIndex & /*parent*/) const
 {
     return NumberOfMaterialProperties;
 }


QVariant MaterialBrowserModel::data(const QModelIndex &index, int role) const
{
//    std::cout << "MaterialBrowserModel::data() -> 1.1" << std::endl;
    const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nrow_mat.at(index.row()));
    if( !mat ) {
        std::cout << " MaterialBrowserModel::data() -> Panic" << std::endl;
        return QVariant();
    }
//    std::cout << "MaterialBrowserModel::data() -> 1.2" << std::endl;

    if (role == Qt::DisplayRole)
    {
//        std::cout << "MaterialBrowserModel::data() -> 1.3 " << index.row() << " " << m_nraw_mat.at(index.row()) << std::endl;
        const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nrow_mat.at(index.row()));
        if( !mat ) {
            std::cout << " MaterialBrowserModel::data() -> Panic" << std::endl;
            return QVariant();
        }
        std::cout << "MaterialBrowserModel::data() -> " << mat << " " << mat->getName() << " " << mat->getRefractiveIndex().real()<< std::endl;
        switch(index.column()) {
        case MaterialName:
            return QString(mat->getName().c_str());
        case MaterialIndexReal:
            return QString::number(mat->getRefractiveIndex().real());
        case MaterialIndexImag:
            return QString::number(mat->getRefractiveIndex().imag());
        case MaterialTitle:
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
            case MaterialName:
                return QString("Name");
            case MaterialIndexReal:
                return QString("Index::real");
            case MaterialIndexImag:
                return QString("Index::imag");
            case MaterialTitle:
                return QString("Comment");
            }
        } else if (orientation == Qt::Vertical) {
            return QString("%1").arg(section);
        }
    }
    return QVariant();
}


bool MaterialBrowserModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        const HomogeneousMaterial *mat = dynamic_cast<const HomogeneousMaterial *>(m_nrow_mat.at(index.row()));
        complex_t refractiveIndex;
        bool status(true);
        double double_value;
        if( !mat ) {
            std::cout << " MaterialBrowserModel::setData() -> Panic #1" << std::endl;
            return false;
        }
        switch(index.column()) {
        case MaterialName:
            std::cout << " MaterialBrowserModel::setData() -> 1.1 " << value.toString().toStdString() << std::endl;

            MaterialManager::instance().setMaterialName(mat->getName(), value.toString().toStdString());
//            return QString(mat->getName().c_str());
            break;
        case MaterialIndexReal:
            double_value = value.toDouble(&status);
            std::cout << " MaterialBrowserModel::setData() -> 1.2 " << double_value << " result " << status << std::endl;
            if(status) {
                refractiveIndex = mat->getRefractiveIndex();
                refractiveIndex.real() = double_value;
                MaterialManager::instance().setMaterialRefractiveIndex(mat->getName(), refractiveIndex);
            }
//            return QString::number(mat->getRefractiveIndex().real());
            break;
        case MaterialIndexImag:
//            return QString::number(mat->getRefractiveIndex().imag());
            break;
        case MaterialTitle:
            break;
        default:
            std::cout << " MaterialBrowserModel::setData() -> Panic #2" << std::endl;
            return false;
        }
        return true;

//        //save value from editor to member m_gridData
//        m_gridData[index.row()][index.column()] = value.toString();
//        //for presentation purposes only: build and emit a joined string
//        QString result;
//        for(int row= 0; row < ROWS; row++)
//        {
//            for(int col= 0; col < COLS; col++)
//            {
//                result += m_gridData[row][col] + " ";
//            }
//        }
//        emit editCompleted( result );
    }
    return true;
}


Qt::ItemFlags MaterialBrowserModel::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}


QColor MaterialBrowserModel::getMaterialColor(const QString &name)
{
    if(name == QStringLiteral("Air") ) {
        return QColor(176, 226, 255);
    } else if(name == QStringLiteral("Substrate") ) {
        return QColor(205,102,0);
    } else if ( name == QStringLiteral("Default") ) {
        return QColor(Qt::green);
    }
    return DesignerHelper::getRandomColor();
}

