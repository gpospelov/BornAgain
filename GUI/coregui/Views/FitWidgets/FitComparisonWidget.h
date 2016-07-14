// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.h
//! @brief     Declares class FitComparisonWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef FITCOMPARISONWIDGET_H
#define FITCOMPARISONWIDGET_H

#include <QMap>
#include "SessionItemWidget.h"

class JobItem;
class IntensityDataItem;
class ColorMapCanvas;
class SessionModel;
class FitFlowWidget;
class ColorMapLabel;
class QAction;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit FitComparisonWidget(QWidget *parent = 0);
    ~FitComparisonWidget();

    void setItem(class SessionItem *item);

    virtual QList<QAction *> actionList();

private slots:
    void onResetViewAction();

protected:
    void setJobItem(class JobItem *jobItem);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:

    struct LabelBackup {
        QString xlabel, ylabel;
    };

    void processJobItemItem(JobItem *jobItem);
    void setSimulatedDataItem(IntensityDataItem *simulatedDataItem);

    IntensityDataItem *createRelativeDifferenceItem();
    void calculateRelativeDifference();
    void backupLabels(IntensityDataItem *intensityItem);
    void restoreLabels(IntensityDataItem *intensityItem);
    void removeLabels(IntensityDataItem *intensityItem);

    ColorMapCanvas *m_realDataPlot;
    ColorMapCanvas *m_simulatedDataPlot;
    ColorMapCanvas *m_relativeDiffPlot;


    FitFlowWidget *m_fitFlowWidget;
    ColorMapLabel *m_statusLabel;

    JobItem *m_currentJobItem;
    IntensityDataItem *m_realDataItem;
    IntensityDataItem *m_simulatedDataItem;
    IntensityDataItem *m_relativeDiffItem;

    QAction *m_resetViewAction;

    SessionModel *m_tempIntensityDataModel;
    QMap<IntensityDataItem *, LabelBackup> m_labelBackup;
};

#endif // FITCOMPARISONWIDGET_H
