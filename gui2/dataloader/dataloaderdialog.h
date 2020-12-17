//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/dataloaderdialog.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_DATALOADERDIALOG_H
#define BORNAGAIN_GUI2_DATALOADER_DATALOADERDIALOG_H

#include "darefl_export.h"
#include "gui2/importdataview/graphimportdata.h"
#include <QDialog>
#include <memory>
#include <vector>

class QSplitter;

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_DATALOADERDIALOG_H
