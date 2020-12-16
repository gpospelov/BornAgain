// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QSplitter>
#include <QVBoxLayout>
#include <darefl/dataloader/defaultparser.h>
#include <darefl/dataloader/importfilewidget.h>
#include <darefl/dataloader/loaderselectorpanel.h>
#include <darefl/dataloader/parserpropertywidget.h>

namespace DaRefl {

LoaderSelectorPanel::LoaderSelectorPanel(QWidget* parent)
    : QWidget(parent)
    , m_fileSelectorWidget(new ImportFileWidget)
    , m_propertyWidget(new ParserPropertyWidget)
    , m_splitter(new QSplitter) {
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->setChildrenCollapsible(false);

    m_splitter->addWidget(m_fileSelectorWidget);
    m_splitter->addWidget(m_propertyWidget);

    layout->addWidget(m_splitter);

    init_connections();
}

LoaderSelectorPanel::~LoaderSelectorPanel() = default;

std::unique_ptr<ParserInterface> LoaderSelectorPanel::createParser() const {
    return m_propertyWidget->createParser();
}

void LoaderSelectorPanel::setTargetCanvas(const QStringList& canvas_names, int current_index) {
    m_propertyWidget->setTargetCanvas(canvas_names, current_index);
}

int LoaderSelectorPanel::targetCanvasIndex() const {
    return m_targetCanvasIndex;
}

void LoaderSelectorPanel::onAddFilesRequest() {
    m_fileSelectorWidget->onAddFilesRequest();
}

void LoaderSelectorPanel::onRemoveFileRequest() {
    m_fileSelectorWidget->onRemoveFileRequest();
}

QStringList LoaderSelectorPanel::selectedFileNames() const {
    return m_fileSelectorWidget->selectedFileNames();
}

QStringList LoaderSelectorPanel::fileNames() const {
    return m_fileSelectorWidget->fileNames();
}

void LoaderSelectorPanel::init_connections() {
    auto on_file_names_changed = [this]() { fileNamesChanged(m_fileSelectorWidget->fileNames()); };
    connect(m_fileSelectorWidget, &ImportFileWidget::fileNamesChanged, on_file_names_changed);

    auto on_selection_changed = [this]() {
        fileSelectionChanged(m_fileSelectorWidget->selectedFileNames());
    };
    connect(m_fileSelectorWidget, &ImportFileWidget::fileSelectionChanged, on_selection_changed);

    connect(m_propertyWidget, &ParserPropertyWidget::parserPropertyChanged, this,
            &LoaderSelectorPanel::parserPropertyChanged);

    auto on_target_changed = [this](auto index) { m_targetCanvasIndex = index; };
    connect(m_propertyWidget, &ParserPropertyWidget::targetCanvasChanged, on_target_changed);
}

} // namespace DaRefl
