//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      gui2/dataloader/parserpropertywidget.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI2_DATALOADER_PARSERPROPERTYWIDGET_H
#define BORNAGAIN_GUI2_DATALOADER_PARSERPROPERTYWIDGET_H

#include "darefl_export.h"
#include "gui2/dataloader/dataloader_types.h"
#include <QWidget>
#include <memory>

class QGridLayout;
class QButtonGroup;
class QComboBox;
class QLineEdit;

namespace gui2 {

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

} // namespace gui2

#endif // BORNAGAIN_GUI2_DATALOADER_PARSERPROPERTYWIDGET_H
