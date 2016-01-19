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

#ifndef FITPROGRESSWIDGET_H
#define FITPROGRESSWIDGET_H

#include "WinDllMacros.h"
#include "OutputData.h"
#include <boost/shared_ptr.hpp>
#include <QWidget>

class QLabel;
class ColorMapPlot;
class IntensityDataItem;
class QPlainTextEdit;
class QSplitter;
class GUIFitObserver;

class BA_CORE_API_ FitProgressWidget : public QWidget
{
    Q_OBJECT

public:

    FitProgressWidget(QWidget *parent = 0);

    boost::shared_ptr<GUIFitObserver> getObserver();

public slots:

    void updateStatus(const QString &text);

    void updateLog(const QString &msg);

    void updatePlots(OutputData<double> *sim, OutputData<double> *chi);

    void startFitting(OutputData<double> *real);

    void afterReplot();

private:

    QLabel *m_status;
    ColorMapPlot *m_realdataplot;
    ColorMapPlot *m_simulatedplot;
    ColorMapPlot *m_chi2plot;
    IntensityDataItem *m_realdata;
    IntensityDataItem *m_simulated;
    IntensityDataItem *m_chi2;
    QPlainTextEdit *m_log;
    QSplitter *m_splitter;
    boost::shared_ptr<GUIFitObserver> m_guifitobserver;

    void disableInteractions();
};





#endif
