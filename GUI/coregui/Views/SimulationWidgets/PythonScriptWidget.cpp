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

#include "PythonScriptWidget.h"
#include "PythonSyntaxHighlighter.h"
#include "SampleModel.h"
#include "InstrumentModel.h"
#include "DesignerHelper.h"
#include "Simulation.h"
#include "PyGenTools.h"
#include "DomainSimulationBuilder.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QToolBar>
#include <QTextEdit>
#include <QStyle>
#include <QDebug>

PythonScriptWidget::PythonScriptWidget(QWidget *parent)
    : QDialog(parent)
    , m_toolBar(0)
    , m_textEdit(0)
    , m_sampleModel(0)
    , m_instrumentModel(0)
{
    setWindowTitle("Python Script View");
    setMinimumSize(128, 128);
    resize(512, 400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_toolBar = new QToolBar;
    m_toolBar->setFixedHeight(28);
    m_toolBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    const int size = style()->pixelMetric(QStyle::PM_SmallIconSize);
    m_toolBar->setIconSize(QSize(size, size));
    m_toolBar->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    m_textEdit = new QTextEdit;
    m_textEdit->setReadOnly(true);
    QFont textFont("Monospace");
    m_textEdit->setFont(textFont);
    m_textEdit->setFontPointSize(DesignerHelper::getPythonEditorFontSize());
    m_textEdit->setLineWrapMode(QTextEdit::NoWrap);
    PythonSyntaxHighlighter *highlighter = new PythonSyntaxHighlighter(m_textEdit->document());
    Q_UNUSED(highlighter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_textEdit);

    setLayout(mainLayout);

    setAttribute(Qt::WA_DeleteOnClose, true);
}

PythonScriptWidget::~PythonScriptWidget()
{
    qDebug() << "PythonScriptWidget::~PythonScriptWidget()";
    delete m_sampleModel;
    delete m_instrumentModel;
}

void PythonScriptWidget::generatePythonScript(SampleModel *sampleModel, InstrumentModel *instrumentModel)
{
    delete m_sampleModel;
    m_sampleModel = sampleModel;

    delete m_instrumentModel;
    m_instrumentModel = instrumentModel;

    Simulation *simulation(0);
    try{
        simulation = DomainSimulationBuilder::getSimulation(sampleModel, instrumentModel);
    } catch(const std::exception &ex) {
        QMessageBox::warning(this, tr("Could not create simulation"), tr(ex.what()));
        return;
    }

    QString code = QString::fromStdString(PyGenTools::genPyScript(simulation));
    m_textEdit->clear();
    m_textEdit->setText(code);


}
