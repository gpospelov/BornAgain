// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <QTabWidget>
#include <QVBoxLayout>
#include <darefl/dataloader/dataloader_utils.h>
#include <darefl/dataloader/importtablewidget.h>
#include <darefl/dataloader/importtextview.h>
#include <darefl/dataloader/loaderpreviewpanel.h>
#include <darefl/dataloader/parserinterface.h>

namespace DaRefl
{

namespace
{
const std::string gray{"#aab7b8"};
const std::string blue{"#1b4f72"};

} // namespace

LoaderPreviewPanel::LoaderPreviewPanel(QWidget* parent)
    : QWidget(parent)
    , m_textView(new ImportTextView)
    , m_tableWidget(new ImportTableWidget)
    , m_tabWidget(new QTabWidget)
{
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_tabWidget->addTab(m_textView, "Text view");
    m_tabWidget->addTab(m_tableWidget, "Table view");

    layout->addWidget(m_tabWidget);
}

//! Sets raw text to the TextView.

void LoaderPreviewPanel::showData(const ParserInterface* parser)
{
    m_textView->clear();
    for (size_t index = 0; index < parser->totalLineCount(); ++index) {
        auto line_data = parser->getLine(index);
        auto parts = parser->parseResults(index);
        auto string_to_show = Utils::AddHtmlColorTagToParts(line_data, parts, blue, gray);
        m_textView->appendHtml(QString::fromStdString(string_to_show));
    }
    m_textView->moveCursor(QTextCursor::Start);

    m_tableWidget->setRawData(parser->parsedData());
}

std::vector<ColumnInfo> LoaderPreviewPanel::columnInfo() const
{
    return m_tableWidget->columnInfo();
}

void LoaderPreviewPanel::clearPanel()
{
    m_textView->clear();
    m_tableWidget->setRawData({});
}

} // namespace DaRefl
