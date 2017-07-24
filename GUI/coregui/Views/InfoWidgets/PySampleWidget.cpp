// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/PySampleWidget.cpp
//! @brief     Implements class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PySampleWidget.h"
#include "DesignerHelper.h"
#include "DomainObjectBuilder.h"
#include "MultiLayer.h"
#include "PythonFormatting.h"
#include "PythonSyntaxHighlighter.h"
#include "SampleModel.h"
#include "WarningSign.h"
#include "UpdateTimer.h"
#include <QScrollBar>
#include <QTextEdit>
#include <QVBoxLayout>

namespace {
const int accumulate_updates_during_msec = 20.;

const QString welcome_message =
"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta http-equiv=\"Content-Type\" "
"content=\"text/html; charset=UTF-8\" /><title>QTextEdit Example</title><style type=\"text/css\">"
"p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'Helvetica';"
" font-size:10pt; font-weight:400; font-style:normal;\"><p align=\"center\" style=\""
" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0;"
" text-indent:0px;\"><span style=\" font-size:14pt;\">Sample Script View</span></p>"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px;"
" margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">"
"The Sample Script View displays Python code corresponding to the sample being constructed."
" Start building a multilayer and corresponding code snippet will start appear in this window."
"</span></p>"
"<ul type=\"circle\" style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right:"
" 0px; -qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\""
" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0;"
" text-indent:0px;\">This is an experimental feature and is provided as tech preview only</li>"
"<li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px;"
" margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
"Only items which are connected to the multilayer will be translated</li></ul>"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px;"
" margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"><br /></p></body></html>";
}

PySampleWidget::PySampleWidget(QWidget *parent)
    : QWidget(parent)
    , m_textEdit(new QTextEdit)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_highlighter(0)
    , m_updateTimer(new UpdateTimer(accumulate_updates_during_msec, this))
    , m_warningSign(new WarningSign(m_textEdit))
{
    m_textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    m_textEdit->setHtml(welcomeMessage());
    m_textEdit->setReadOnly(true);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());

}

void PySampleWidget::setSampleModel(SampleModel* sampleModel)
{
    Q_ASSERT(sampleModel);
    if (sampleModel != m_sampleModel) {
        if (m_sampleModel)
            setEditorConnected(false);
        m_sampleModel = sampleModel;
    }
}

void PySampleWidget::setInstrumentModel(InstrumentModel* instrumentModel)
{
    Q_ASSERT(instrumentModel);
    m_instrumentModel = instrumentModel;
}

void PySampleWidget::onModifiedRow(const QModelIndex&, int, int)
{
    m_updateTimer->scheduleUpdate();
}

void PySampleWidget::onDataChanged(const QModelIndex&, const QModelIndex&)
{
    m_updateTimer->scheduleUpdate();
}

//! Update the editor with the script content
void PySampleWidget::updateEditor()
{
    if (!m_highlighter) {
        m_highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
        m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }

    const int old_scrollbar_value = m_textEdit->verticalScrollBar()->value();

    QString code_snippet = generateCodeSnippet();

    if (!code_snippet.isEmpty())
        m_textEdit->setText(code_snippet);
    else
        m_textEdit->clear();

    m_textEdit->verticalScrollBar()->setValue(old_scrollbar_value);
}

void PySampleWidget::setEditorConnected(bool isConnected)
{
    if (isConnected) {
        connect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                SLOT(onModifiedRow(QModelIndex, int, int)), Qt::UniqueConnection);
        connect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                SLOT(onModifiedRow(QModelIndex, int, int)), Qt::UniqueConnection);
        connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                SLOT(onDataChanged(QModelIndex, QModelIndex)), Qt::UniqueConnection);
        connect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateEditor()),
                Qt::UniqueConnection);

        connect(m_updateTimer, SIGNAL(timeToUpdate()), this, SLOT(updateEditor()),
                Qt::UniqueConnection);

        m_updateTimer->scheduleUpdate();

    } else {
        disconnect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                   SLOT(onModifiedRow(QModelIndex, int, int)));
        disconnect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                   SLOT(onModifiedRow(QModelIndex, int, int)));
        disconnect(m_sampleModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
                   SLOT(onDataChanged(QModelIndex, QModelIndex)));
        disconnect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateEditor()));

        disconnect(m_updateTimer, SIGNAL(timeToUpdate()), this, SLOT(updateEditor()));
    }
}

//! generates string representing code snippet for all multi layers in the model

QString PySampleWidget::generateCodeSnippet()
{
    m_warningSign->clear();
    QString result;

    foreach (SessionItem* sampleItem, m_sampleModel->topItems(Constants::MultiLayerType)) {
        DomainObjectBuilder builder;
        try {
            auto multilayer = builder.buildMultiLayer(*sampleItem);
            if (!result.isEmpty())
                result.append("\n");
            result.append(QString::fromStdString(
                          PythonFormatting::generateCode(*multilayer)));
        } catch (const std::exception& ex) {
            QString message
                = QString("Generation of Python Script failed. Code is not complete.\n\n"
                          "It can happen if sample requires further assembling or some of sample "
                          "parameters "
                          "are not valid. See details below.\n\n%1")
                      .arg(QString::fromStdString(ex.what()));

            m_warningSign->setWarningMessage(message);
        }
    }

    return result;
}

//! returns welcome message with fonts adjusted to the system

QString PySampleWidget::welcomeMessage()
{
    QString result = welcome_message;

    result.replace("font-size:10pt;",
                   QString("font-size:%1pt;").arg(DesignerHelper::getPythonEditorFontSize()));

    result.replace("font-size:14pt;",
                   QString("font-size:%1pt;").arg(DesignerHelper::getPythonEditorFontSize() + 2));

    return result;
}
