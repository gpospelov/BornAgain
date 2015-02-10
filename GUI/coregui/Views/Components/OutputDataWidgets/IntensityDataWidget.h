// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/IntensityDataWidget.h
//! @brief     Defines class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAWIDGET_H
#define INTENSITYDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class ProjectManager;
class IntensityDataPropertyWidget;
//class PlotWidget;
class NIntensityDataItem;
class IntensityDataPlotWidget;

class BA_CORE_API_ IntensityDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntensityDataWidget(QWidget *parent = 0);

    void setItem(NIntensityDataItem *item);
    void setProjectManager(ProjectManager *projectManager);

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

public slots:

    void onResetView();
    void togglePropertyPanel();
    void savePlot();
    void toggleProjections();
    void setPropertyPanelVisible(bool visible);

private:
//    PlotWidget *m_plotWidget;
    ProjectManager *m_projectManager;
    IntensityDataPlotWidget *m_plotWidget;
    IntensityDataPropertyWidget *m_propertyWidget;
    NIntensityDataItem *m_currentItem;
};




#endif
