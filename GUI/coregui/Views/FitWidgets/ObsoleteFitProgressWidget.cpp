// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/ObsoleteFitProgressWidget.cpp
//! @brief     Defines class ObsoleteFitProgressWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ObsoleteFitProgressWidget.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include "GUIFitObserver.h"
#include "FitSuite.h"
#include "qcustomplot.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QScrollBar>
#include <QFont>
#include <QSlider>

ObsoleteFitProgressWidget::ObsoleteFitProgressWidget(QWidget *parent)
    : QWidget(parent)
    , m_status(new QLabel(this))
    , m_realdataplot(new ColorMapPlot(this))
    , m_simulatedplot(new ColorMapPlot(this))
    , m_chi2plot(new ColorMapPlot(this))
    , m_realdata(new IntensityDataItem())
    , m_simulated(new IntensityDataItem())
    , m_chi2(new IntensityDataItem())
    , m_log(new QPlainTextEdit(this))
    , m_splitter(new QSplitter())
{
    m_guifitobserver = std::shared_ptr<GUIFitObserver>(new GUIFitObserver(this));

    connect(m_guifitobserver.get(), SIGNAL(updateStatus(const QString&)),
            this, SLOT(updateStatus(const QString&)));
    connect(m_guifitobserver.get(), SIGNAL(updatePlots(OutputData<double>*, OutputData<double>*)),
            this, SLOT(updatePlots(OutputData<double>*, OutputData<double>*)));
    connect(m_guifitobserver.get(), SIGNAL(updateLog(const QString&)),
            this, SLOT(updateLog(const QString&)));
    connect(m_guifitobserver.get(), SIGNAL(startFitting(OutputData<double>*)),
            this, SLOT(startFitting(OutputData<double>*)));

    // chi2 is the last plot to finish, so we wait for it
    connect(m_chi2plot->getCustomPlot(), SIGNAL(afterReplot()),
            this, SLOT(afterReplot()));

    m_realdataplot->setItem(m_realdata);
    m_simulatedplot->setItem(m_simulated);
    m_chi2plot->setItem(m_chi2);
    m_chi2->setProperty("Gradient", "Hot");

    QHBoxLayout *plots = new QHBoxLayout();
    plots->addWidget(m_realdataplot);
    plots->addWidget(m_simulatedplot);
    plots->addWidget(m_chi2plot);
    QWidget *plotsWidget = new QWidget();
    plotsWidget->setLayout(plots);

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(plotsWidget);
    m_splitter->addWidget(m_log);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_status);
    layout->addWidget(m_splitter);
    m_log->setReadOnly(true);
    m_log->setMaximumBlockCount(100000);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    m_log->setFont(f);
    m_status->setText("");
    setLayout(layout);
}

void ObsoleteFitProgressWidget::startFitting(OutputData<double> *real)
{
    m_realdata->setOutputData(real);
    m_simulated->setOutputData(real->clone());
    m_simulated->setZAxisLocked(true);
    disableInteractions();
    m_log->clear();
}

void ObsoleteFitProgressWidget::connectSlider(QSlider *slider)
{
    connect(slider, SIGNAL(valueChanged(int)),
                m_guifitobserver.get(), SLOT(setInterval(int)));
}

void ObsoleteFitProgressWidget::setObserverToSuite(FitSuite *suite)
{
    suite->attachObserver(m_guifitobserver);
}

void ObsoleteFitProgressWidget::updateStatus(const QString &text)
{
    m_status->setText(text);
}

void ObsoleteFitProgressWidget::updateLog(const QString &msg)
{
    QScrollBar *scrollbar = m_log->verticalScrollBar();
    bool autoscroll = scrollbar->value() == scrollbar->maximum();
    m_log->appendPlainText(msg);
    if (autoscroll) {
        QTextCursor c = m_log->textCursor();
        c.movePosition(QTextCursor::End);
        m_log->setTextCursor(c);
    }
}

void ObsoleteFitProgressWidget::updatePlots(OutputData<double> *sim, OutputData<double> *chi)
{
    m_simulated->setOutputData(sim);
    m_simulated->setLowerAndUpperZ(m_realdata->getLowerZ(), m_realdata->getUpperZ());
    m_chi2->setOutputData(chi);
    disableInteractions();
}

void ObsoleteFitProgressWidget::afterReplot()
{
    m_guifitobserver->finishedPlotting();
}

void ObsoleteFitProgressWidget::disableInteractions()
{
    // as ColorMapPlot enables Interactions every time, we must disenable them as well
    m_realdataplot->getCustomPlot()->setInteraction(QCP::iRangeDrag, false);
    m_realdataplot->getCustomPlot()->setInteraction(QCP::iRangeZoom, false);
    m_simulatedplot->getCustomPlot()->setInteraction(QCP::iRangeDrag, false);
    m_simulatedplot->getCustomPlot()->setInteraction(QCP::iRangeZoom, false);
    m_chi2plot->getCustomPlot()->setInteraction(QCP::iRangeDrag, false);
    m_chi2plot->getCustomPlot()->setInteraction(QCP::iRangeZoom, false);
}
