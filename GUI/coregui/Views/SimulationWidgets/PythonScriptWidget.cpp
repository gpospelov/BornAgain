// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/PythonScriptWidget.cpp
//! @brief     Implements class PythonScriptWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "PythonScriptWidget.h"
#include "DesignerHelper.h"
#include "DomainSimulationBuilder.h"
#include "GISASSimulation.h"
#include "InstrumentModel.h"
#include "PythonFormatting.h"
#include "PythonSyntaxHighlighter.h"
#include "SampleModel.h"
#include "SimulationOptionsItem.h"
#include "WarningSignWidget.h"
#include "projectdocument.h"
#include "projectmanager.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStyle>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

PythonScriptWidget::PythonScriptWidget(QWidget *parent)
    : QDialog(parent)
    , m_toolBar(0)
    , m_textEdit(0)
    , m_warningSign(0)
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

    QPushButton *exportToFileButton = new QPushButton;
    exportToFileButton->setText("Save to file");
    exportToFileButton->setToolTip("Opens dialog to save given script into the file");
    connect(exportToFileButton, SIGNAL(clicked()), this, SLOT(onExportToFileButton()));
    exportToFileButton->setAutoDefault(false);
    m_toolBar->addWidget(exportToFileButton);

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

void PythonScriptWidget::generatePythonScript(const MultiLayerItem *sampleItem,
        const InstrumentItem *instrumentItem, const SimulationOptionsItem *optionItem,
                                              const QString &outputDir)
{
    m_outputDir = outputDir;

    delete m_warningSign;
    m_warningSign = 0;

    try{
        const std::unique_ptr<GISASSimulation> P_simulation(
            DomainSimulationBuilder::getSimulation(sampleItem, instrumentItem, optionItem));

        QString code = QString::fromStdString(
            PythonFormatting::simulationToPython(P_simulation.get()));
        m_textEdit->clear();
        m_textEdit->setText(code);

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

//! adjusts position of warning label on widget move
void PythonScriptWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    if(m_warningSign) {
        QPoint pos = getPositionForWarningSign();
        m_warningSign->setPosition(pos.x(),pos.y());
    }
}

void PythonScriptWidget::onExportToFileButton()
{
    QString dirname(m_outputDir);
    if(dirname.isEmpty())
        dirname = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);

    QString file_name = QFileDialog::getSaveFileName(this, "Select file", dirname,
                            "Python scipts (*.py)", 0,
                            QFileDialog::DontResolveSymlinks);

    if(file_name.isEmpty()) return;

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "PythonScriptWidget::onExportToFileButton: Error! Can't save file";
        QMessageBox warning_dialog(this);
        warning_dialog.setIcon(QMessageBox::Warning);
        warning_dialog.setText("File could not be opened for writing!");
        warning_dialog.exec();
        return;
    }
    QTextStream out(&file);
    out << m_textEdit->toPlainText();
    file.close();
    raise();
}

//! Returns position for warning sign at the bottom left corner of the editor. The position will
//! be adjusted according to the visibility of scroll bars
QPoint PythonScriptWidget::getPositionForWarningSign()
{
    const int warning_sign_xpos = 38;
    const int warning_sign_ypos = 38;

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
