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
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QModelIndex>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>

namespace {
const int timer_interval_msec = 10;
const int update_every_msec = 20.;
}

PySampleWidget::PySampleWidget(QWidget *parent)
    : QWidget(parent)
    , m_textEdit(new QTextEdit)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_time_to_update(update_every_msec)
    , m_n_of_sceduled_updates(0)
//    , m_block_update(false)
{
    m_textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    PythonSyntaxHighlighter *highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
    Q_UNUSED(highlighter);

//    QWidget *infoPanel = new QWidget(parent);
//    infoPanel->setGeometry(QRect(100, 100, 400, 200));
//    infoPanel->show();

    m_timer = new QTimer(this);
    m_timer->setInterval(timer_interval_msec);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));

}

void PySampleWidget::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(sampleModel);
    if(sampleModel != m_sampleModel) {

        if(m_sampleModel) {
            disconnect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onModifiedRow(QModelIndex,int,int)));
            disconnect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onModifiedRow(QModelIndex,int,int)));
            disconnect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
            disconnect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateEditor()));
        }

        m_sampleModel = sampleModel;

        //updateEditor();

        connect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onModifiedRow(QModelIndex,int,int)));
        connect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onModifiedRow(QModelIndex,int,int)));
        connect(m_sampleModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(onDataChanged(QModelIndex,QModelIndex)));
        connect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateEditor()));

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

void PySampleWidget::scheduleUpdate()
{
    return;
    m_n_of_sceduled_updates++;
    qDebug() << "PySampleWidget::scheduleUpdate()" << m_n_of_sceduled_updates;
    if(!m_timer->isActive()) m_timer->start();
}

void PySampleWidget::updateEditor()
{
//    if(m_block_update) return;
//    m_block_update = true;

//    Q_ASSERT(m_timer->isActive());
//    m_timer->stop();

    qDebug() << "PySampleWidget::updateEditor() -> begin" << m_n_of_sceduled_updates;
    m_n_of_sceduled_updates = 0;

    const int old_scrollbar_value = m_textEdit->verticalScrollBar()->value();

    m_textEdit->clear();

    QMap<QString, ParameterizedItem *> sampleMap = m_sampleModel->getSampleMap();
    if(!sampleMap.isEmpty()) {

        DomainObjectBuilder builder;
        ParameterizedItem *sampleItem = sampleMap.first();
        boost::scoped_ptr<MultiLayer> multilayer(builder.buildMultiLayer(*sampleItem));
        //multilayer->printSampleTree();

        PyGenVisitor visitor;
        VisitSampleTree(*multilayer, visitor);

        std::ostringstream result;
        result << visitor.defineGetSample();

        m_textEdit->setText(QString::fromStdString(result.str()));
    }

    m_textEdit->verticalScrollBar()->setValue(old_scrollbar_value);


//    m_time_to_update = update_every_msec;

//    m_block_update = false;
    qDebug() << "       PySampleWidget::updateEditor() -> begin" << m_n_of_sceduled_updates;

}

void PySampleWidget::onTimerTimeout()
{
    qDebug() << "PySampleWidget::onTimerTimeout()" << m_time_to_update << "scheduled updates" << m_n_of_sceduled_updates;
    m_time_to_update -= timer_interval_msec;

    if(m_time_to_update < 0) {
        m_timer->stop();
        updateEditor();
        m_time_to_update = update_every_msec;
    }
}


