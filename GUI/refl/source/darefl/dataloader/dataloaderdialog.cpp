// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QDebug>
#include <QDialogButtonBox>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/core/app_constants.h>
#include <darefl/dataloader/datahandler.h>
#include <darefl/dataloader/dataloader_types.h>
#include <darefl/dataloader/dataloader_utils.h>
#include <darefl/dataloader/dataloaderdialog.h>
#include <darefl/dataloader/dataloadertoolbar.h>
#include <darefl/dataloader/loaderpreviewpanel.h>
#include <darefl/dataloader/loaderselectorpanel.h>
#include <darefl/dataloader/parserinterface.h>
#include <mvvm/utils/fileutils.h>
#include <mvvm/widgets/widgetutils.h>
#include <sstream>

namespace DaRefl
{

namespace
{

//! Wraps user method in try/catch and invoke it.
//! Provides busy-sign while executing, and warning dialog on exception catch.
template <typename T> void invoke_and_catch(T method)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    try {
        std::invoke(method);
        QApplication::restoreOverrideCursor();
    } catch (const std::exception& ex) {
        QApplication::restoreOverrideCursor();
        QMessageBox msgBox;

        QString message =
            QString("Exception was thrown while trying to load files\n\n%1").arg(ex.what());
        msgBox.setText(message);
        msgBox.setIcon(msgBox.Critical);
        msgBox.exec();
    }
}

const QString dialogsize_key = "dialogsize";
const QString splittersize_key = "splittersize";

const QString dialogsize_setting_name()
{
    return Constants::DataLoaderGroupKey + "/" + dialogsize_key;
}

const QString splittersize_setting_name()
{
    return Constants::DataLoaderGroupKey + "/" + splittersize_key;
}

//! Returns string representing import summary: filename and columns used for import.

std::string createImportDescription(const QString& file_name, const ColumnInfo& axis_info,
                                    const ColumnInfo& intensity_info)
{
    std::ostringstream ostr;
    ostr << "file: '" << ModelView::Utils::WithTildeHomePath(file_name).toStdString() << "', ";
    ostr << "columns: (" << axis_info.column << ", " << intensity_info.column << ")";
    return ostr.str();
}

} // namespace

DataLoaderDialog::DataLoaderDialog(QWidget* parent)
    : QDialog(parent)
    , m_toolBar(new DataLoaderToolBar)
    , m_selectorPanel(new LoaderSelectorPanel)
    , m_previewPanel(new LoaderPreviewPanel)
    , m_splitter(new QSplitter)
    , m_dataHandler(std::make_unique<DataHandler>())
{
    m_splitter->setChildrenCollapsible(false);
    m_splitter->addWidget(m_selectorPanel);
    m_splitter->addWidget(m_previewPanel);

    auto button_box = new QDialogButtonBox;
    auto button = button_box->addButton("Import data", QDialogButtonBox::AcceptRole);
    button->setAutoDefault(false);
    button->setDefault(false);

    button = button_box->addButton("Cancel", QDialogButtonBox::RejectRole);
    button->setAutoDefault(false);
    button->setDefault(false);

    connect(button_box, &QDialogButtonBox::accepted, this, &DataLoaderDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &DataLoaderDialog::reject);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(m_toolBar);
    layout->addWidget(m_splitter);
    layout->addWidget(button_box);

    initConnections();
    setWindowTitle("Data import dialog");

    readSettings();
}

DataLoaderDialog::~DataLoaderDialog()
{
    writeSettings();
}

//! Returns the result of whole parsing.

std::vector<GraphImportData> DataLoaderDialog::graphImportData() const
{
    return m_graphImportData;
}

//! Set list of target canvas to define entr where to import.

void DataLoaderDialog::setTargetCanvas(const std::vector<std::string>& canvas_names,
                                       int current_index)
{
    m_selectorPanel->setTargetCanvas(ModelView::Utils::toStringList(canvas_names), current_index);
}

//! Returns index of target canvas for graph import.

int DataLoaderDialog::targetCanvasIndex() const
{
    return m_selectorPanel->targetCanvasIndex();
}

//! Invokes file selector dialog.

void DataLoaderDialog::invokeFileSelectorDialog()
{
    m_selectorPanel->onAddFilesRequest();
}

QStringList DataLoaderDialog::fileNames() const
{
    return m_selectorPanel->fileNames();
}

//! Make dialog intact to enter-key to handle it by LoadSelectorPanel.

void DataLoaderDialog::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        return;
    QDialog::keyPressEvent(event);
}

void DataLoaderDialog::accept()
{
    invoke_and_catch([this]() { onParseAllRequest(); });

    QDialog::accept();
    close();
}

//! Loads ASCII data from all files in a list.

void DataLoaderDialog::onLoadFilesRequest()
{
    auto update_raw_data = [this]() {
        m_dataHandler->updateRawData(
            ModelView::Utils::fromStringList(m_selectorPanel->fileNames()));
    };
    invoke_and_catch(update_raw_data);
}

//! Show content of selected file in text/table views.

void DataLoaderDialog::onShowFilePreviewRequest()
{
    auto selected_files = m_selectorPanel->selectedFileNames();
    if (selected_files.empty()) {
        m_previewPanel->clearPanel();
        return;
    }

    auto data_to_parse = m_dataHandler->textData(selected_files.back().toStdString());

    // creating parser using current settings
    auto parser = m_selectorPanel->createParser();
    parser->process(data_to_parse);

    m_previewPanel->showData(parser.get());
}

//! Parse all string data and generate graph data.

void DataLoaderDialog::onParseAllRequest()
{
    m_graphImportData.clear();

    auto parser = m_selectorPanel->createParser();
    for (const auto& name : m_selectorPanel->fileNames()) {
        auto data_to_parse = m_dataHandler->textData(name.toStdString());

        parser->process(data_to_parse);
        auto parsed_text = parser->parsedData();

        auto columns = m_previewPanel->columnInfo();
        for (auto [axis_info, intensity_info] : Utils::CreateGraphInfoPairs(columns)) {
            auto data = Utils::CreateData(parsed_text, axis_info, intensity_info);
            data.graph_description = createImportDescription(name, axis_info, intensity_info);
            m_graphImportData.emplace_back(data);
        }
    }
}

//! Reads dialog settings.

void DataLoaderDialog::readSettings()
{
    QSettings settings;

    if (settings.contains(dialogsize_setting_name()))
        resize(settings.value(dialogsize_setting_name(), QSize(800, 600)).toSize());

    if (settings.contains(splittersize_setting_name())) {
        QStringList splitter_sizes = QStringList() << "400"
                                                   << "400";
        splitter_sizes = settings.value(splittersize_setting_name(), splitter_sizes).toStringList();
        QList<int> sizes;
        for (auto num : splitter_sizes)
            sizes.push_back(num.toInt());
        m_splitter->setSizes(sizes);
    }
}

//! Writes dialog settings.

void DataLoaderDialog::writeSettings()
{
    QSettings settings;
    settings.setValue(dialogsize_setting_name(), size());

    QStringList splitter_sizes;
    for (auto x : m_splitter->sizes())
        splitter_sizes.push_back(QString::number(x));
    settings.setValue(splittersize_setting_name(), splitter_sizes);
}

//! Init interconnections of all widgets.

void DataLoaderDialog::initConnections()
{
    // connect toolbar and LoaderSelectorPanel
    connect(m_toolBar, &DataLoaderToolBar::addFilesRequest, m_selectorPanel,
            &LoaderSelectorPanel::onAddFilesRequest);
    connect(m_toolBar, &DataLoaderToolBar::removeFilesRequest, m_selectorPanel,
            &LoaderSelectorPanel::onRemoveFileRequest);

    // updates raw data container when file list changed
    connect(m_selectorPanel, &LoaderSelectorPanel::fileNamesChanged, this,
            &DataLoaderDialog::onLoadFilesRequest);

    // update text/table view when file selection changed
    connect(m_selectorPanel, &LoaderSelectorPanel::fileSelectionChanged, this,
            &DataLoaderDialog::onShowFilePreviewRequest);

    // update text/table view when parser properties changed
    connect(m_selectorPanel, &LoaderSelectorPanel::parserPropertyChanged, this,
            &DataLoaderDialog::onShowFilePreviewRequest);
}

} // namespace DaRefl
