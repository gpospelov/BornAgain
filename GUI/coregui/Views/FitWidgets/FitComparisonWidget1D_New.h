// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget1D_New.h
//! @brief     Defines class FitComparisonWidget1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITCOMPARISONWIDGET1D_NEW_H
#define FITCOMPARISONWIDGET1D_NEW_H

#include "SessionItemWidget.h"

class FitComparisonController1D;
class FitFlowWidget;
class IntensityDataPropertyWidget;
class JobItem;
class PlotStatusLabel;
class QAction;
class SpecularDataItem;
class SpecularPlotCanvas;

//! The FitComparisonWidget class plots realdata, simulated data and relative difference map
//! during the course of the fit.

class BA_CORE_API_ FitComparisonWidget1D_New : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit FitComparisonWidget1D_New(QWidget* parent = nullptr);
    ~FitComparisonWidget1D_New() override;

    virtual QList<QAction*> actionList() override;

private slots:
    void onResetViewAction();

protected:
    void subscribeToItem() override;
    void unsubscribeFromItem() override;

private:
    JobItem* jobItem();
    SpecularDataItem* realDataItem();
    SpecularDataItem* simulatedDataItem();

    SpecularPlotCanvas* m_data_plot;
    SpecularPlotCanvas* m_diff_plot;
    FitFlowWidget* m_fitFlowWidget;
    PlotStatusLabel* m_statusLabel;
    IntensityDataPropertyWidget* m_propertyWidget;

    QAction* m_resetViewAction;
    FitComparisonController1D* m_comparisonController;
};

#endif // FITCOMPARISONWIDGET1D_NEW_H
