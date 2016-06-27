// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ObsoleteIntensityDataWidget.h
//! @brief     Declares class ObsoleteIntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef OBSOLETEINTENSITYDATAWIDGET_H
#define OBSOLETEINTENSITYDATAWIDGET_H

#include "SessionItemWidget.h"

class IntensityDataItem;
class ObsoleteIntensityDataWidgetActions;
class ObsoleteIntensityDataPlotWidget;
class ObsoleteIntensityDataPropertyWidget;

//! The widget presents IntensityData color map and property editor.
//! Belongs to the stack handled by JobOutputDataWidget
class BA_CORE_API_ ObsoleteIntensityDataWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit ObsoleteIntensityDataWidget(QWidget *parent = 0);

    void setItem(class SessionItem *item);
    void setIntensityData(IntensityDataItem *intensityItem);

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    QList<QAction *> actionList();

signals:
    void savePlotRequest();

public slots:
    void onResetView();
    void togglePropertyPanel();
    void savePlot();
    void toggleProjections();
    void setPropertyPanelVisible(bool visible);

private:
    ObsoleteIntensityDataWidgetActions *m_widgetActions;
    ObsoleteIntensityDataPlotWidget *m_plotWidget;
    ObsoleteIntensityDataPropertyWidget *m_propertyWidget;
    IntensityDataItem *m_currentItem;
};

#endif
