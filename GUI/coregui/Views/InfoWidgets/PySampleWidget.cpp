// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/InfoWidgets/PySampleWidget.cpp
//! @brief     Implements class PySampleWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PySampleWidget.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "PythonSyntaxHighlighter.h"
#include "DomainObjectBuilder.h"
#include "MultiLayer.h"
#include "PyGenVisitor.h"
#include "WarningSignWidget.h"
#include "DesignerHelper.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QModelIndex>
#include <QScrollBar>
#include <QTimer>
#include <QTextCodec>
#include <QDebug>
#include <QPixmap>
#include <QPainter>

namespace {
const int timer_interval_msec = 10;
const int update_every_msec = 20.;
const int warning_sign_xpos = 52;
const int warning_sign_ypos = 38;

const QString welcome_message =
"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />"
"<title>QTextEdit Example</title><style type=\"text/css\">"
"p, li { white-space: pre-wrap; }"
"</style></head><body style=\" font-family:'Helvetica'; font-size:9pt; font-weight:400; font-style:normal;\">"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">Sample Script View</span></p>"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">The Sample Script View displays Python code corresponding to the sample being constructed. Start building a multilayer and corresponding code snippet will start appear in this window.</span></p>"
"<ul type=\"circle\" style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This is an experimental feature and is provided as tech preview only</li>"
"<li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Only items which are connected to the multilayer will be translated</li></ul>"
"<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"><br /></p></body></html>";
}

PySampleWidget::PySampleWidget(QWidget *parent)
    : QWidget(parent)
    , m_textEdit(new QTextEdit)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_time_to_update(update_every_msec)
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

    m_textEdit->setHtml(welcome_message);
    m_textEdit->setReadOnly(true);
    m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());

}

void PySampleWidget::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(sampleModel);
    if(sampleModel != m_sampleModel) {

        if(m_sampleModel) disableEditor();

        m_sampleModel = sampleModel;

        //updateEditor();

//        connect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onModifiedRow(QModelIndex,int,int)), Qt::UniqueConnection);
//        connect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onModifiedRow(QModelIndex,int,int)), Qt::UniqueConnection);
//        connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)), Qt::UniqueConnection);
//        connect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateEditor()), Qt::UniqueConnection);

    }

}

void PySampleWidget::setInstrumentModel(InstrumentModel *instrumentModel)
{
    Q_ASSERT(instrumentModel);
    m_instrumentModel = instrumentModel;

}

void PySampleWidget::onModifiedRow(const QModelIndex &, int, int)
{
    scheduleUpdate();
}

void PySampleWidget::onDataChanged(const QModelIndex &, const QModelIndex &)
{
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

    m_time_to_update = update_every_msec;
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

    if(m_sampleModel->getSampleMap().empty()) {
        // negative number would mean that editor was never used and still contains welcome message we want to keep
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
    qDebug() << "PySampleWidget::onTimerTimeout()" << m_time_to_update << "scheduled updates" << m_n_of_sceduled_updates;
    m_time_to_update -= timer_interval_msec;

    if(m_time_to_update < 0) {
        m_timer->stop();
        updateEditor();
    }
}

//! adjusts position of warning label on widget move
void PySampleWidget::resizeEvent(QResizeEvent *event)
{
    if(m_warningSign) {
        m_warningSign->setPosition(event->size().width()-warning_sign_xpos,
                                   event->size().height()-warning_sign_ypos);
    }
}

//! generates string representing code snippet for all multi layers in the model
QString PySampleWidget::generateCodeSnippet()
{
    delete m_warningSign;
    m_warningSign = 0;

    QString result;

    QMap<QString, ParameterizedItem *> sampleMap = m_sampleModel->getSampleMap();
    if(!sampleMap.isEmpty()) {

        DomainObjectBuilder builder;
        PyGenVisitor visitor;
        ParameterizedItem *sampleItem = sampleMap.first();

        try {
            boost::scoped_ptr<MultiLayer> multilayer(builder.buildMultiLayer(*sampleItem));
            VisitSampleTree(*multilayer, visitor);
            std::ostringstream ostr;
            ostr << visitor.defineGetSample();
            result.append(QString::fromStdString(ostr.str()));
        } catch(const std::exception &ex) {
            m_warningSign = new WarningSignWidget(this);
            m_warningSign->setWarningMessage(QString::fromStdString(ex.what()));
            m_warningSign->setPosition(width()-warning_sign_xpos, height()-warning_sign_ypos);
            m_warningSign->show();

        }
    }

    return result;
}


