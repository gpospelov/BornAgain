// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/FitWidgets/RunFitWidget.h
//! @brief     Defines class RunFitWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitProgressWidget.h"
#include "ColorMapPlot.h"
#include "IntensityDataItem.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>

FitProgressWidget::FitProgressWidget(QWidget *parent)
    : QWidget(parent)
    , m_status(new QLabel(this))
    , m_realdataplot(new ColorMapPlot(this))
    , m_simulatedplot(new ColorMapPlot(this))
    , m_chi2plot(new ColorMapPlot(this))
    , m_log(new QPlainTextEdit(this))
{
    QHBoxLayout *plots = new QHBoxLayout();
    plots->addWidget(m_realdataplot);
    plots->addWidget(m_simulatedplot);
    plots->addWidget(m_chi2plot);
    QWidget *plotsWidget = new QWidget();
    plotsWidget->setLayout(plots);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_status);
    layout->addWidget(plotsWidget);
    layout->addWidget(m_log);
    m_log->setReadOnly(true);
    m_log->setMaximumBlockCount(100000);
    m_status->setText("");
    setLayout(layout);
}

void FitProgressWidget::updateStatus(const QString &text)
{
    m_status->setText(text);
}

void FitProgressWidget::updateLog(const QString &msg)
{
    m_log->appendPlainText(msg);
    QTextCursor c = m_log->textCursor();
    c.movePosition(QTextCursor::End);
    m_log->setTextCursor(c);
}

void FitProgressWidget::updatePlots(IntensityDataItem *sim, IntensityDataItem *chi)
{
    m_simulatedplot->setItem(sim);
    m_chi2plot->setItem(chi);
    //delete sim;
    //delete chi;
}
