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
#include <QDebug>

PySampleWidget::PySampleWidget(QWidget *parent)
    : QWidget(parent)
    , m_textEdit(new QTextEdit)
    , m_sampleModel(0)
    , m_instrumentModel(0)
    , m_block_update(false)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    PythonSyntaxHighlighter *highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
    Q_UNUSED(highlighter);

//    QWidget *infoPanel = new QWidget(parent);
//    infoPanel->setGeometry(QRect(100, 100, 400, 200));
//    infoPanel->show();

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

        updateEditor();

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
    updateEditor();
}

void PySampleWidget::onDataChanged(const QModelIndex &, const QModelIndex &)
{
    updateEditor();
}

void PySampleWidget::updateEditor()
{
    if(m_block_update) return;

    qDebug() << "PySampleWidget::updateEditor()";
    m_block_update = true;

    QMap<QString, ParameterizedItem *> sampleMap = m_sampleModel->getSampleMap();
    if(!sampleMap.isEmpty()) {

        DomainObjectBuilder builder;
        ParameterizedItem *sampleItem = sampleMap.first();
        boost::scoped_ptr<MultiLayer> multilayer(builder.buildMultiLayer(*sampleItem));
        multilayer->printSampleTree();

        PyGenVisitor visitor;
        VisitSampleTree(*multilayer, visitor);

        std::ostringstream result;
        result << visitor.defineGetSample();

        m_textEdit->setText(QString::fromStdString(result.str()));
    }

    m_block_update = false;
}
