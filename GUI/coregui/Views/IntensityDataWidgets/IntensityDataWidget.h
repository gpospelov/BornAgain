// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataWidget.h
//! @brief     Declares class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAWIDGET_H
#define INTENSITYDATAWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class IntensityDataPropertyWidget;
class IntensityDataItem;
class IntensityDataPlotWidget;

//! The widget presents IntensityData color map and property editor.
//! Belongs to the stack handled by JobOutputDataWidget
class BA_CORE_API_ IntensityDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntensityDataWidget(QWidget *parent = 0);

    void setItem(IntensityDataItem *item);

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

signals:
    void savePlotRequest();

public slots:
    void onResetView();
    void togglePropertyPanel();
    void savePlot(const QString &dirname);
    void toggleProjections();
    void setPropertyPanelVisible(bool visible);

private:
    IntensityDataPlotWidget *m_plotWidget;
    IntensityDataPropertyWidget *m_propertyWidget;
    IntensityDataItem *m_currentItem;
};

#endif
