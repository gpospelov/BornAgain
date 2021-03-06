//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/loaderpreviewpanel.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_LOADERPREVIEWPANEL_H
#define BORNAGAIN_GUI2_DATALOADER_LOADERPREVIEWPANEL_H

#include "darefl_export.h"
#include <QWidget>

class QTabWidget;

namespace gui2 {

class ImportTextView;
class ImportTableWidget;

class ParserInterface;
struct ColumnInfo;

//! Panel with settings for DataLoaderDialog.
//! Located on its right side, contains text and table views.

class DAREFLCORE_EXPORT LoaderPreviewPanel : public QWidget {
    Q_OBJECT

public:
    LoaderPreviewPanel(QWidget* parent = nullptr);

    void showData(const ParserInterface* parser);

    std::vector<ColumnInfo> columnInfo() const;

    void clearPanel();

private:
    ImportTextView* m_textView{nullptr};
    ImportTableWidget* m_tableWidget{nullptr};
    QTabWidget* m_tabWidget{nullptr};
};

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_LOADERPREVIEWPANEL_H
