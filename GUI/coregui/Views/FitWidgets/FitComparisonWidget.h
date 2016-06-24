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

#include "SessionItemWidget.h"

class IntensityDataItem;
class ColorMap;
class SessionModel;
class FitFlowWidget;
class ColorMapLabel;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    explicit FitComparisonWidget(QWidget *parent = 0);
    ~FitComparisonWidget();

    void setItem(class SessionItem *item);

protected:
    void setJobItem(class JobItem *jobItem);

private:
    void setSimulatedDataItem(IntensityDataItem *simulatedDataItem);

    IntensityDataItem *createRelativeDifferenceItem();
    void calculateRelativeDifference();

    ColorMap *m_realDataPlot;
    ColorMap *m_simulatedDataPlot;
    ColorMap *m_relativeDiffPlot;
    FitFlowWidget *m_fitFlowWidget;
    ColorMapLabel *m_statusLabel;

    IntensityDataItem *m_realDataItem;
    IntensityDataItem *m_simulatedDataItem;
    IntensityDataItem *m_relativeDiffItem;

    SessionModel *m_tempIntensityDataModel;
};

#endif
