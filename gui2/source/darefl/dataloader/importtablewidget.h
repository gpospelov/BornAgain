// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_IMPORTTABLEWIDGET_H
#define DAREFL_DATALOADER_IMPORTTABLEWIDGET_H

#include <QWidget>
#include <darefl/darefl_export.h>
#include <memory>
#include <string>
#include <vector>

class QTableView;

namespace ModelView {
class ViewModelDelegate;
}

namespace DaRefl {

struct ColumnInfo;

class ImportTableModel;

//! Contains table with imported data.
//! Belongs to LoaderPreviewPanel.

class DAREFLCORE_EXPORT ImportTableWidget : public QWidget {
    Q_OBJECT

public:
    ImportTableWidget(QWidget* parent = nullptr);
    ~ImportTableWidget();

    void setRawData(const std::vector<std::vector<std::string>>& table_data);

    std::vector<ColumnInfo> columnInfo() const;

private:
    ImportTableModel* m_tableModel{nullptr};
    QTableView* m_tableView{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_IMPORTTABLEWIDGET_H
