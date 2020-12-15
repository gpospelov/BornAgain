// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_LOADERPREVIEWPANEL_H
#define DAREFL_DATALOADER_LOADERPREVIEWPANEL_H

#include <QWidget>
#include <darefl/darefl_export.h>

class ImportTextView;
class ImportTableWidget;
class QTabWidget;

namespace DaRefl
{

class ParserInterface;
struct ColumnInfo;

//! Panel with settings for DataLoaderDialog.
//! Located on its right side, contains text and table views.

class DAREFLCORE_EXPORT LoaderPreviewPanel : public QWidget
{
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

} // namespace DaRefl

#endif // DAREFL_DATALOADER_LOADERPREVIEWPANEL_H
