// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_DATALOADERDIALOG_H
#define DAREFL_DATALOADER_DATALOADERDIALOG_H

#include <QDialog>
#include "darefl_export.h"
#include "gui2/importdataview/graphimportdata.h"
#include <memory>
#include <vector>

class QSplitter;

namespace DaRefl {

class DataLoaderToolBar;
class LoaderSelectorPanel;
class LoaderPreviewPanel;
class DataHandler;

//! Main dialog for the data loader.

class DAREFLCORE_EXPORT DataLoaderDialog : public QDialog {
    Q_OBJECT

public:
    DataLoaderDialog(QWidget* parent = nullptr);
    ~DataLoaderDialog();

    std::vector<GraphImportData> graphImportData() const;

    void setTargetCanvas(const std::vector<std::string>& canvas_names, int current_index);

    int targetCanvasIndex() const;

    void invokeFileSelectorDialog();

    QStringList fileNames() const;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void accept() override;

private slots:
    void onLoadFilesRequest();
    void onShowFilePreviewRequest();
    void onParseAllRequest();

private:
    void readSettings();
    void writeSettings();
    void initConnections();

    DataLoaderToolBar* m_toolBar{nullptr};
    LoaderSelectorPanel* m_selectorPanel{nullptr};
    LoaderPreviewPanel* m_previewPanel{nullptr};
    QSplitter* m_splitter{nullptr};

    std::unique_ptr<DataHandler> m_dataHandler;
    std::vector<GraphImportData> m_graphImportData;
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_DATALOADERDIALOG_H
