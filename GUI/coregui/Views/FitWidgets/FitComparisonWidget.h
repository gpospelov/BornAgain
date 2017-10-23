// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.h
//! @brief     Defines class FitComparisonWidget
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

#include "SessionItemWidget.h"
#include <QMap>

class JobItem;
class IntensityDataItem;
class ColorMapCanvas;
class SessionModel;
class FitFlowWidget;
class ColorMapLabel;
class QAction;
class PropertyRepeater;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit FitComparisonWidget(QWidget* parent = 0);
    ~FitComparisonWidget();

    virtual QList<QAction*> actionList();

private slots:
    void onResetViewAction();

protected:
    void subscribeToItem();
    void unsubscribeFromItem();

private:
    IntensityDataItem* createRelativeDifferenceItem();
    void calculateRelativeDifference();
    void restoreLabels(IntensityDataItem* intensityItem);
    void removeLabels(IntensityDataItem* intensityItem);

    JobItem* jobItem();
    IntensityDataItem* realDataItem();
    IntensityDataItem* simulatedDataItem();

    ColorMapCanvas* m_realDataPlot;
    ColorMapCanvas* m_simulatedDataPlot;
    ColorMapCanvas* m_relativeDiffPlot;
    FitFlowWidget* m_fitFlowWidget;
    ColorMapLabel* m_statusLabel;
    PropertyRepeater* m_repeater;

    IntensityDataItem* m_relativeDiffItem;
    QAction* m_resetViewAction;
    SessionModel* m_tempIntensityDataModel;
};

#endif // FITCOMPARISONWIDGET_H
