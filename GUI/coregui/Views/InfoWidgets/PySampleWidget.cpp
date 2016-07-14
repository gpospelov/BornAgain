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

#include <QDebug>
#include <QFile>
#include <QModelIndex>
#include <QPainter>
#include <QPixmap>
#include <QScrollBar>
#include <QTextCodec>
#include <QTextEdit>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include "DesignerHelper.h"
#include "DomainObjectBuilder.h"
#include "InstrumentModel.h"
#include "MultiLayer.h"
#include "PyGenVisitor.h"
#include "PythonSyntaxHighlighter.h"
#include "SampleModel.h"
#include "WarningSignWidget.h"
#include "PySampleWidget.h"

namespace {
const int timer_interval_msec = 10;
const int accumulate_updates_during_msec = 20.;
const int warning_sign_xpos = 38;
const int warning_sign_ypos = 38;

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
    , m_time_to_update(accumulate_updates_during_msec)
    , m_n_of_sceduled_updates(-1)
    , m_highlighter(0)
    , m_warningSign(0)
{
    m_textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    m_timer = new QTimer(this);
    m_timer->setInterval(timer_interval_msec);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

    m_textEdit->setHtml(getWelcomeMessage());
    m_textEdit->setReadOnly(true);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());

    // FIXME First appearance of the editor takes ~0.3sec delay which is unconfortable.
    // It can be made faster, if one uncomment line below. But we would like to have it
    // commented because of welcome message (we need to wrap welcome message).
    //m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
}

void PySampleWidget::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(sampleModel);
    if(sampleModel != m_sampleModel) {
        if(m_sampleModel) disableEditor();
        m_sampleModel = sampleModel;
    }
}

void PySampleWidget::setInstrumentModel(InstrumentModel *instrumentModel)
{
    Q_ASSERT(instrumentModel);
    m_instrumentModel = instrumentModel;
}

void PySampleWidget::onModifiedRow(const QModelIndex &, int, int)
{
    //if(m_sampleModel->getSampleMap().empty()) return;
    scheduleUpdate();
}

void PySampleWidget::onDataChanged(const QModelIndex &, const QModelIndex &)
{
    //if(m_sampleModel->getSampleMap().empty()) return;
    scheduleUpdate();
}

//! Schedule subsequent update of the editor
void PySampleWidget::scheduleUpdate()
{
    m_n_of_sceduled_updates++;
    qDebug() << "PySampleWidget::scheduleUpdate()" << m_n_of_sceduled_updates;
    if(!m_timer->isActive()) m_timer->start();
}

//! Update the editor with the script content
void PySampleWidget::updateEditor()
{
    if(!m_highlighter) {
        m_highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
        m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    }

    Q_ASSERT(!m_timer->isActive());
    qDebug() << "PySampleWidget::updateEditor() -> begin" << m_n_of_sceduled_updates;
    m_n_of_sceduled_updates = 0;

    const int old_scrollbar_value = m_textEdit->verticalScrollBar()->value();

    QString code_snippet = generateCodeSnippet();
    if(!m_warningSign) m_textEdit->clear();

    if(!code_snippet.isEmpty()) {
        m_textEdit->setText(code_snippet);
    }

    m_textEdit->verticalScrollBar()->setValue(old_scrollbar_value);

    m_time_to_update = accumulate_updates_during_msec;
}

//! Disconnect from all signals to prevent editor update
void PySampleWidget::disableEditor()
{
    Q_ASSERT(m_sampleModel);
    m_timer->stop();
    disconnect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int,int)),
               this, SLOT(onModifiedRow(QModelIndex,int,int)));
    disconnect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int,int)),
               this, SLOT(onModifiedRow(QModelIndex,int,int)));
    disconnect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
               this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
    disconnect(m_sampleModel, SIGNAL(modelReset()),
               this, SLOT(updateEditor()));
}

void PySampleWidget::enableEditor()
{
    Q_ASSERT(m_sampleModel);

    if(m_sampleModel->topItems().isEmpty()) {
        // negative number would mean that editor was never used and still contains welcome message
        // which we want to keep
        if(m_n_of_sceduled_updates >= 0) updateEditor();
    } else {
        updateEditor();
    }

    connect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int,int)),
            this, SLOT(onModifiedRow(QModelIndex,int,int)), Qt::UniqueConnection);
    connect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int,int)),
            this, SLOT(onModifiedRow(QModelIndex,int,int)), Qt::UniqueConnection);
    connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(onDataChanged(QModelIndex,QModelIndex)), Qt::UniqueConnection);
    connect(m_sampleModel, SIGNAL(modelReset()),
            this, SLOT(updateEditor()), Qt::UniqueConnection);
}

//! Triggers the update of the editor
void PySampleWidget::onTimerTimeout()
{
    qDebug() << "PySampleWidget::onTimerTimeout()" << m_time_to_update
             << "scheduled updates" << m_n_of_sceduled_updates;
    m_time_to_update -= timer_interval_msec;

    if(m_time_to_update < 0) {
        m_timer->stop();
        updateEditor();
    }
}

//! adjusts position of warning label on widget move
void PySampleWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(m_warningSign) {
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(),pos.y());
    }
}

//! generates string representing code snippet for all multi layers in the model
QString PySampleWidget::generateCodeSnippet()
{
    delete m_warningSign;
    m_warningSign = 0;

    QString result;

    foreach(SessionItem *sampleItem, m_sampleModel->topItems()) {
        DomainObjectBuilder builder;
        PyGenVisitor visitor;

        try {
            auto P_multilayer = builder.buildMultiLayer(*sampleItem);
            VisitSampleTreePostorder(*P_multilayer, visitor);
            std::ostringstream ostr;
            ostr << visitor.defineGetSample();
            if(!result.isEmpty()) result.append("\n");
            result.append(QString::fromStdString(ostr.str()));
        } catch(const std::exception &ex) {
            m_warningSign = new WarningSignWidget(this);

            QString message = QString(
                "Generation of Python Script failed. Code is not complete.\n\n"
                "It can happen if sample requires further assembling or some of sample parameters "
                "are not valid. See details below.\n\n%1").arg(QString::fromStdString(ex.what()));

            m_warningSign->setWarningMessage(message);
            QPoint pos = getPositionForWarningSign();
            m_warningSign->setPosition(pos.x(), pos.y());
            m_warningSign->show();

        }
    }

    return result;
}

//! Returns position for warning sign at the bottom right corner of the editor. The position will
//! be adjusted according to the visibility of scroll bars
QPoint PySampleWidget::getPositionForWarningSign()
{
    int x = width()-warning_sign_xpos;
    int y = height()-warning_sign_ypos;

    if(QScrollBar *horizontal = m_textEdit->horizontalScrollBar()) {
        if(horizontal->isVisible())
            y -= horizontal->height();
    }

    if(QScrollBar *vertical = m_textEdit->verticalScrollBar()) {
        if(vertical->isVisible())
            x -= vertical->width();
    }


    return QPoint(x, y);
}

//! returns welcome message with fonts adjusted to the system
QString PySampleWidget::getWelcomeMessage()
{
    QString result = welcome_message;

    result.replace("font-size:10pt;", QString("font-size:%1pt;")
                   .arg(DesignerHelper::getPythonEditorFontSize()));

    result.replace("font-size:14pt;", QString("font-size:%1pt;")
                   .arg(DesignerHelper::getPythonEditorFontSize()+2));

    return result;
}


