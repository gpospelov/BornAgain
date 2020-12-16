// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_IMPORTTABLEMODEL_H
#define DAREFL_DATALOADER_IMPORTTABLEMODEL_H

#include "darefl_export.h"
#include <QAbstractTableModel>
#include <memory>
#include <string>
#include <vector>

namespace DaRefl {

struct ColumnInfo;

class ImportTableHeader;

//! Table model to hold imported ASCII data after parsing it to multi-column presentation.

class DAREFLCORE_EXPORT ImportTableModel : public QAbstractTableModel {
    Q_OBJECT

public:
    using raw_data_t = std::vector<std::vector<std::string>>;

    ImportTableModel(QObject* parent = nullptr);
    ~ImportTableModel() override;

    void setRawData(const raw_data_t& raw_data);

    int rowCount(const QModelIndex& = QModelIndex()) const override;

    int columnCount(const QModelIndex& = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    std::vector<ColumnInfo> columnInfo() const;

private:
    int utilityRowCount() const;
    QVariant dataFromIndex(const QModelIndex& index) const;

    std::unique_ptr<ImportTableHeader> m_header;
    raw_data_t m_rawData; //! parsed column data

    int m_maxColumnCount{0};
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_IMPORTTABLEMODEL_H
