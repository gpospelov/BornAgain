//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      gui2/dataloader/parserpropertywidget.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "gui2/dataloader/parserpropertywidget.h"
#include "gui2/core/app_constants.h"
#include "gui2/dataloader/defaultparser.h"
#include "mvvm/widgets/widgetutils.h"
#include <QButtonGroup>
#include <QComboBox>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QRegExpValidator>
#include <QSettings>
#include <QVBoxLayout>

namespace {

//! Creates widget with label and little space above. Intended for grid layouts.
QWidget* createSectionWidget(const QString& text) {
    auto widget = new QWidget;
    auto layout = new QVBoxLayout(widget);
    layout->addSpacing(10);
    auto label = new QLabel(text);
    QFont font = label->font();
    font.setPointSize(ModelView::Utils::SystemPointSize() * 1.05);
    label->setFont(font);
    layout->addWidget(label);
    return widget;
}

const QString separatorgroupid_setting_name() {
    const QString key = "separatorgroup_id";
    return gui2::Constants::ParserPropertyGroupKey + "/" + key;
}

const QString customseparatortext_setting_name() {
    const QString key = "customseparator_text";
    return gui2::Constants::ParserPropertyGroupKey + "/" + key;
}

} // namespace

namespace gui2 {

ParserPropertyWidget::ParserPropertyWidget(QWidget* parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    layout->addLayout(createGridLayout());
    layout->addStretch(1);

    readSettings();
}

ParserPropertyWidget::~ParserPropertyWidget() {
    writeSettings();
}

//! Creates parser from parser properties.

std::unique_ptr<ParserInterface> ParserPropertyWidget::createParser() const {
    ParserOptions options = m_options;

    // sanity check for empty separator
    options.m_separator = options.m_separator.empty() ? std::string(" ") : options.m_separator;
    return std::make_unique<DefaultParser>(options);
}

//! Sets list of canvas names as possible import targets.

void ParserPropertyWidget::setTargetCanvas(const QStringList& canvas_names, int current_index) {
    m_targetCanvasCombo->insertItems(0, canvas_names);
    m_targetCanvasCombo->setCurrentIndex(current_index);
}

void ParserPropertyWidget::onParserPropertyChange() {
    qDebug() << "option"
             << "header:" << QString::fromStdString(m_options.m_header_prefix)
             << "separator:" << QString::fromStdString(m_options.m_separator) << "pattern"
             << QString::fromStdString(m_options.m_skip_index_pattern);
    emit parserPropertyChanged();
}

//! Reads widget settings.

void ParserPropertyWidget::readSettings() {
    QSettings settings;

    if (settings.contains(separatorgroupid_setting_name())) {
        int button_id = settings.value(separatorgroupid_setting_name()).toInt();
        if (auto button = m_separatorButtonGroup->button(button_id); button) {
            button->click();
        }
    }

    if (settings.contains(customseparatortext_setting_name()))
        m_customSeparatorLineEdit->setText(
            settings.value(customseparatortext_setting_name()).toString());
}

//! Writes widget settings.

void ParserPropertyWidget::writeSettings() {
    QSettings settings;

    settings.setValue(separatorgroupid_setting_name(), m_separatorButtonGroup->checkedId());
    settings.setValue(customseparatortext_setting_name(), m_customSeparatorLineEdit->text());
}

QGridLayout* ParserPropertyWidget::createGridLayout() {
    auto grid_layout = new QGridLayout;

    addSectionLabel("Separator", grid_layout);
    m_separatorButtonGroup = new QButtonGroup(this);
    addStandardSeparatorRow(grid_layout, m_separatorButtonGroup);
    addCustomSeparatorRow(grid_layout, m_separatorButtonGroup);

    addSectionLabel("Ignore lines", grid_layout);
    addIgnoreStringPatternRow(grid_layout);
    addIgnoreNumbersPatternRow(grid_layout);

    addSectionLabel("Import target", grid_layout);
    addImportToBlock(grid_layout);

    // make first colum with invisible label fixed
    for (int col = 0; col < grid_layout->columnCount(); ++col)
        grid_layout->setColumnStretch(col, 10);
    grid_layout->setColumnStretch(0, 0);

    return grid_layout;
}

void ParserPropertyWidget::addSectionLabel(const QString& text, QGridLayout* layout) {
    int row = layout->rowCount();
    layout->addWidget(createSectionWidget(text), row, 0, 1, 3, Qt::AlignLeft);
}

//! Adds row to the grid: elements with standard separator settings.

void ParserPropertyWidget::addStandardSeparatorRow(QGridLayout* layout, QButtonGroup* group) {
    // automatic separator
    int row = layout->rowCount();
    auto automaticRadio = new QRadioButton;
    automaticRadio->setChecked(true);
    automaticRadio->setText("Automatic");
    automaticRadio->setToolTip("Try to guess column separator");
    connect(automaticRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator.clear();
        onParserPropertyChange();
    });

    // space separator
    auto spaceRadio = new QRadioButton;
    spaceRadio->setText("Space");
    spaceRadio->setToolTip("Use empty space as column separator");
    connect(spaceRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator = " ";
        onParserPropertyChange();
    });

    // comma separator
    auto commaRadio = new QRadioButton;
    commaRadio->setText("Comma");
    commaRadio->setToolTip("Use comma as column separator");
    connect(commaRadio, &QRadioButton::clicked, [this](auto) {
        m_options.m_separator = ",";
        onParserPropertyChange();
    });

    // adding all to layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(automaticRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(spaceRadio, row, 2, Qt::AlignLeft);
    layout->addWidget(commaRadio, row, 3, Qt::AlignLeft);
    group->addButton(automaticRadio, AUTOMATIC);
    group->addButton(spaceRadio, SPACE);
    group->addButton(commaRadio, COMMA);
}

//! Adds row to the grid: elements with custom separator settings.

void ParserPropertyWidget::addCustomSeparatorRow(QGridLayout* layout, QButtonGroup* group) {
    int row = layout->rowCount();
    m_customSeparatorLineEdit = new QLineEdit;
    auto customRadio = new QRadioButton;

    // custom separator radio
    customRadio->setText("Custom");
    customRadio->setToolTip("Use given symbols as column separator");
    auto on_custom_separator = [this](auto) {
        m_options.m_separator = m_customSeparatorLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(customRadio, &QRadioButton::clicked, on_custom_separator);

    // custom separator text
    m_customSeparatorLineEdit->setMaximumWidth(ModelView::Utils::WidthOfLetterM() * 4);
    m_customSeparatorLineEdit->setToolTip("Use given symbols as column separator");
    auto on_custom_lineedit = [this, customRadio]() {
        if (customRadio->isChecked())
            m_options.m_separator = m_customSeparatorLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(m_customSeparatorLineEdit, &QLineEdit::editingFinished, on_custom_lineedit);

    // adding to the layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(customRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(m_customSeparatorLineEdit, row, 2, Qt::AlignLeft);
    group->addButton(customRadio, CUSTOM);
}

//! Adds row to the grid: elements with pattern to ignore lines.

void ParserPropertyWidget::addIgnoreStringPatternRow(QGridLayout* layout) {
    auto startingWithRadio = new QRadioButton;
    auto startingFromLineEdit = new QLineEdit;

    // radio settings
    int row = layout->rowCount();
    startingWithRadio->setText("Starting with");
    startingWithRadio->setAutoExclusive(false);
    startingWithRadio->setChecked(true);
    startingWithRadio->setToolTip("Ignore lines starting with a given character(s)");
    auto on_startingfrom_radio = [this, startingFromLineEdit](auto checked) {
        m_options.m_header_prefix =
            checked ? startingFromLineEdit->text().toStdString() : std::string();
        onParserPropertyChange();
    };
    connect(startingWithRadio, &QRadioButton::clicked, on_startingfrom_radio);

    // line edit settings
    startingFromLineEdit->setText("#");
    startingFromLineEdit->setToolTip("Ignore lines starting with a given character(s)");
    auto on_startingfrom_lineedit = [this, startingWithRadio, startingFromLineEdit]() {
        if (startingWithRadio->isChecked())
            m_options.m_header_prefix = startingFromLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(startingFromLineEdit, &QLineEdit::editingFinished, on_startingfrom_lineedit);

    // adding to layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(startingWithRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(startingFromLineEdit, row, 2, Qt::AlignLeft);
}

//! Adds row to the grid: elements with pattern to ignore line numbers.

void ParserPropertyWidget::addIgnoreNumbersPatternRow(QGridLayout* layout) {
    auto lineNumbersRadio = new QRadioButton;
    auto lineNumbersLineEdit = new QLineEdit;

    // radio settings
    int row = layout->rowCount();
    lineNumbersRadio->setAutoExclusive(false);
    lineNumbersRadio->setText("Line numbers");
    lineNumbersRadio->setToolTip("Ignore lines with line numbers matching the pattern");
    auto on_linenumbers_radio = [this, lineNumbersLineEdit](auto checked) {
        m_options.m_skip_index_pattern =
            checked ? lineNumbersLineEdit->text().toStdString() : std::string();
        onParserPropertyChange();
    };
    connect(lineNumbersRadio, &QRadioButton::clicked, on_linenumbers_radio);

    // line edit settings
    lineNumbersLineEdit->setPlaceholderText("Example: 1-5,42");
    lineNumbersLineEdit->setToolTip("Ignore lines with line numbers matching the pattern");
    auto on_linenumbers_lineedit = [this, lineNumbersRadio, lineNumbersLineEdit]() {
        if (lineNumbersRadio->isChecked())
            m_options.m_skip_index_pattern = lineNumbersLineEdit->text().toStdString();
        onParserPropertyChange();
    };
    connect(lineNumbersLineEdit, &QLineEdit::editingFinished, on_linenumbers_lineedit);

    // adding to the layout
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(lineNumbersRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(lineNumbersLineEdit, row, 2, Qt::AlignLeft);

    // validator
    auto validator = new QRegExpValidator(QRegExp("^[0-9,-]*$"), this);
    lineNumbersLineEdit->setValidator(validator);
}

//! Adds row to the grid: elements related to the import target.

void ParserPropertyWidget::addImportToBlock(QGridLayout* layout) {
    auto newCanvasRadio = new QRadioButton;
    auto existingCanvasRadio = new QRadioButton;
    m_targetCanvasCombo = new QComboBox;

    // radio settings
    newCanvasRadio->setText("New canvas");
    newCanvasRadio->setChecked(true);
    newCanvasRadio->setToolTip("Data will be imported into the new canvas");
    auto on_newcanvas_radio = [this](auto checked) {
        if (checked)
            targetCanvasChanged(-1);
    };
    connect(newCanvasRadio, &QRadioButton::clicked, on_newcanvas_radio);

    existingCanvasRadio->setText("Existing canvas");
    existingCanvasRadio->setToolTip("Data will be imported into existing canvas");
    auto on_existingcanvas_radio = [this](auto checked) {
        if (checked)
            targetCanvasChanged(m_targetCanvasCombo->currentIndex());
    };
    connect(existingCanvasRadio, &QRadioButton::clicked, on_existingcanvas_radio);

    // combo settings
    m_targetCanvasCombo->setToolTip("Data will be imported into existing canvas");
    auto on_canvas_combo = [this, existingCanvasRadio](int index) {
        if (existingCanvasRadio->isChecked())
            targetCanvasChanged(index);
    };
    connect(m_targetCanvasCombo,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            on_canvas_combo);

    // adding to the layout
    int row = layout->rowCount();
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(newCanvasRadio, row, 1, Qt::AlignLeft);
    row = layout->rowCount();
    layout->addWidget(new QLabel("  "), row, 0, Qt::AlignLeft);
    layout->addWidget(existingCanvasRadio, row, 1, Qt::AlignLeft);
    layout->addWidget(m_targetCanvasCombo, row, 2, Qt::AlignLeft);
    auto buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(newCanvasRadio);
    buttonGroup->addButton(existingCanvasRadio);
}

} // namespace gui2
