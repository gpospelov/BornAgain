// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/dataloader/importtablemodel.h"
#include "gui2/dataloader/dataloader_types.h"
#include "gui2/dataloader/importtableheader.h"
#include <QBrush>

namespace DaRefl {

namespace {
//! Returns maximum number of columns in 2D data vector.
int maxColumnCount(const ImportTableModel::raw_data_t& data) {
    int result{0};
    for (const auto& x : data)
        result = std::max(result, static_cast<int>(x.size()));
    return result;
}

const int default_header_ncols = 2;
}; // namespace

ImportTableModel::ImportTableModel(QObject* parent)
    : QAbstractTableModel(parent)
    , m_header(std::make_unique<ImportTableHeader>(default_header_ncols)) {}

ImportTableModel::~ImportTableModel() = default;

//! Sets content of the model.

void ImportTableModel::setRawData(const ImportTableModel::raw_data_t& raw_data) {
    beginResetModel();
    m_maxColumnCount = maxColumnCount(raw_data);
    m_header = std::make_unique<ImportTableHeader>(m_maxColumnCount);
    m_rawData = raw_data;
    endResetModel();
}

int ImportTableModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(m_rawData.size()) + utilityRowCount();
}

int ImportTableModel::columnCount(const QModelIndex&) const {
    return m_maxColumnCount;
}

QVariant ImportTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return dataFromIndex(index);

    else if (role == Qt::BackgroundRole && index.row() < utilityRowCount())
        return QBrush(Qt::lightGray);

    return QVariant();
}

bool ImportTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid())
        return false;

    if (index.row() < utilityRowCount() && role == Qt::EditRole)
        return m_header->setData(index.row(), index.column(), value);

    return false;
}

QVariant ImportTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    return section < utilityRowCount() ? QString::fromStdString(m_header->rowName(section))
                                       : QVariant(section - utilityRowCount() + 1);
}

Qt::ItemFlags ImportTableModel::flags(const QModelIndex& index) const {
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    if (index.row() < utilityRowCount())
        result |= Qt::ItemIsEnabled | Qt::ItemIsEditable;
    else
        result |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    return result;
}

std::vector<ColumnInfo> ImportTableModel::columnInfo() const {
    return m_header->columnInfo();
}

int ImportTableModel::utilityRowCount() const {
    return m_header ? m_header->rowCount() : 0;
}

//! Returns data from index. Combines header data with parsed user data.

QVariant ImportTableModel::dataFromIndex(const QModelIndex& index) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() < utilityRowCount()) {
        return m_header->data(index.row(), index.column());

    } else {
        int row = index.row() - utilityRowCount();
        if (row >= 0 && row < static_cast<int>(m_rawData.size())) {
            int col = index.column();
            if (col >= 0 && col < static_cast<int>(m_rawData[row].size())) {
                auto str = m_rawData[static_cast<int>(row)][static_cast<int>(col)];
                return QString::fromStdString(str);
            }
        }
    }
    return QVariant();
}

} // namespace DaRefl
