// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI2_DATALOADER_LOADERSELECTORPANEL_H
#define BORNAGAIN_GUI2_DATALOADER_LOADERSELECTORPANEL_H

#include "darefl_export.h"
#include <QWidget>
#include <memory>

class QSplitter;

namespace gui2 {

class ParserInterface;
class ImportFileWidget;
class ParserPropertyWidget;

//! Panel with settings for DataLoaderDialog.
//! Located on its left side, contains file selection dialog and parser property widget.

class DAREFLCORE_EXPORT LoaderSelectorPanel : public QWidget {
    Q_OBJECT

public:
    LoaderSelectorPanel(QWidget* parent = nullptr);
    ~LoaderSelectorPanel();

    std::unique_ptr<ParserInterface> createParser() const;

    void setTargetCanvas(const QStringList& canvas_names, int current_index);

    int targetCanvasIndex() const;

public slots:
    void onAddFilesRequest();
    void onRemoveFileRequest();
    QStringList selectedFileNames() const;
    QStringList fileNames() const;

signals:
    void fileNamesChanged(const QStringList& file_names);
    void fileSelectionChanged(const QStringList& file_names);
    void parserPropertyChanged();

private:
    void init_connections();

    int m_targetCanvasIndex{-1};
    ImportFileWidget* m_fileSelectorWidget{nullptr};
    ParserPropertyWidget* m_propertyWidget{nullptr};
    QSplitter* m_splitter{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_LOADERSELECTORPANEL_H
