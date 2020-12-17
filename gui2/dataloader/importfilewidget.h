//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/dataloader/importfilewidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_IMPORTFILEWIDGET_H
#define BORNAGAIN_GUI2_DATALOADER_IMPORTFILEWIDGET_H

#include "darefl_export.h"
#include <QWidget>

class QListView;
class QStringListModel;

namespace gui2 {

//! Provides the possibility to select file names on disk and add them to list view.
//! List represents names of ASCII files which will be later imported and parsed.
//! Part of LoaderPreviewPanel.

class DAREFLCORE_EXPORT ImportFileWidget : public QWidget {
    Q_OBJECT

public:
    ImportFileWidget(QWidget* parent = nullptr);
    ~ImportFileWidget();

public slots:
    void onAddFilesRequest();
    void onRemoveFileRequest();

    QStringList fileNames() const;

    QStringList selectedFileNames() const;

signals:
    void fileNamesChanged();
    void fileSelectionChanged();

private:
    void readSettings();
    void writeSettings();

    QStringList validateForBinaryFiles(const QStringList& file_names);

    void updateCurrentWorkdir(const QStringList& file_names);
    void addFileNamesToModel(const QStringList& file_names);

    void makeLastSelected();

    QListView* m_listView{nullptr};
    QStringListModel* m_listModel{nullptr};
    QString m_currentWorkdir;
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_IMPORTFILEWIDGET_H
