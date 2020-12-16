// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DAREFL_DATALOADER_PARSERPROPERTYWIDGET_H
#define DAREFL_DATALOADER_PARSERPROPERTYWIDGET_H

#include <QWidget>
#include "darefl_export.h"
#include "gui2/dataloader/dataloader_types.h"
#include <memory>

class QGridLayout;
class QButtonGroup;
class QComboBox;
class QLineEdit;

namespace DaRefl {

class ParserInterface;

//! Panel to setup ASCII parser. Intended for concrete class DefaultParser.
//! Contains selection of separator symbols, patterns to ignore lines, and import target settings.

class DAREFLCORE_EXPORT ParserPropertyWidget : public QWidget {
    Q_OBJECT

public:
    enum SeparatorButtonId { AUTOMATIC, SPACE, COMMA, CUSTOM };

    ParserPropertyWidget(QWidget* parent = nullptr);
    ~ParserPropertyWidget();

    std::unique_ptr<ParserInterface> createParser() const;

    void setTargetCanvas(const QStringList& canvas_names, int current_index);

signals:
    void parserPropertyChanged();
    int targetCanvasChanged(int canvas_index);

private slots:
    void onParserPropertyChange();

private:
    void readSettings();
    void writeSettings();
    QGridLayout* createGridLayout();

    void addSectionLabel(const QString& text, QGridLayout* layout);
    void addStandardSeparatorRow(QGridLayout* layout, QButtonGroup* group);
    void addCustomSeparatorRow(QGridLayout* layout, QButtonGroup* group);
    void addIgnoreStringPatternRow(QGridLayout* layout);
    void addIgnoreNumbersPatternRow(QGridLayout* layout);
    void addImportToBlock(QGridLayout* layout);

    ParserOptions m_options;
    QButtonGroup* m_separatorButtonGroup{nullptr};
    QComboBox* m_targetCanvasCombo{nullptr};
    QLineEdit* m_customSeparatorLineEdit{nullptr};
};

} // namespace DaRefl

#endif // DAREFL_DATALOADER_PARSERPROPERTYWIDGET_H
