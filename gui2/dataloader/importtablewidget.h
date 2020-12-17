//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/dataloader/importtablewidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_IMPORTTABLEWIDGET_H
#define BORNAGAIN_GUI2_DATALOADER_IMPORTTABLEWIDGET_H

#include "darefl_export.h"
#include <QWidget>
#include <memory>
#include <string>
#include <vector>

class QTableView;

namespace ModelView {
class ViewModelDelegate;
}

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_IMPORTTABLEWIDGET_H
