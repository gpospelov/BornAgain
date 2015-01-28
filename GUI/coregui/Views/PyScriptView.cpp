// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/PyScriptView.cpp
//! @brief     Implements class PyScriptView
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyScriptView.h"

#include "PyScriptSyntaxHighlighter.h"

#include <iostream>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

PyScriptView::PyScriptView(SimulationDataModel *p_simulation_data_model, QWidget *parent)
    : QWidget(parent)
    , mp_simulation_data_model(p_simulation_data_model)
{
    QLabel *openLabel = new QLabel(tr("Open Script:"));
    QLabel *saveLabel = new QLabel(tr("Save Script:"));
    openButton = new QPushButton(tr("Open..."));
    openButton->show();
    saveButton = new QPushButton(tr("Save as..."));
    saveButton->setEnabled(false);
    saveButton->show();

    connect(openButton, SIGNAL(clicked()), this, SLOT(onOpenScript()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(onSaveScript()));

    QGridLayout *buttonLayoutNoStretch = new QGridLayout;
    buttonLayoutNoStretch->addWidget(openLabel, 0, 0);
    buttonLayoutNoStretch->addWidget(openButton, 0, 1);
    buttonLayoutNoStretch->addWidget(saveLabel, 1, 0);
    buttonLayoutNoStretch->addWidget(saveButton, 1, 1);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addLayout(buttonLayoutNoStretch);
    buttonLayout->addStretch();

    scriptEdit = new QTextEdit;
    scriptEdit->setFontFamily("Courier");
    scriptEdit->setFontPointSize(14);
    connect(scriptEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    PyScriptSyntaxHighlighter *highlighter = new PyScriptSyntaxHighlighter(scriptEdit->document());
    Q_UNUSED(highlighter);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(buttonLayout, 0, 0);
    mainLayout->addWidget(scriptEdit, 1, 0);

    setLayout(mainLayout);
    setWindowTitle(tr("Python script editing"));
}

void PyScriptView::onOpenScript()
{
    QString newScriptFilename = QFileDialog::getOpenFileName(this, tr("Open Python Script"),
        QDir::homePath(), tr("Python SCripts (*.py)"),
        0, QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);
    if (newScriptFilename.isNull()) {
        return;
    }
    QFile scriptFile(newScriptFilename);
    if (!scriptFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream fileStream(&scriptFile);
    oldScriptFilename = newScriptFilename;
    scriptEdit->setText(fileStream.readAll());
}

void PyScriptView::onSaveScript()
{
    QString saveFilename = QFileDialog::getSaveFileName(this, tr("Save Python SCript"),
                              oldScriptFilename, tr("Python Scripts (*.py)"),
                              0, QFileDialog::ReadOnly | QFileDialog::DontUseNativeDialog);
    if (saveFilename.isNull()) {
        return;
    }
    QFile scriptFile(saveFilename);
    if (!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream fileStream(&scriptFile);
    fileStream << scriptEdit->toPlainText();
    saveButton->setEnabled(false);
}

void PyScriptView::onTextChanged()
{
    saveButton->setEnabled(true);
}
