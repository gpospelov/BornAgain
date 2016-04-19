// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/VerticalSlicePlot.h
//! @brief     Defines class VerticalSlicePlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef NHISTOGRAMPLOT_H
#define NHISTOGRAMPLOT_H

#include "WinDllMacros.h"
#include <QWidget>
#include <memory>

class IntensityDataItem;
class QCustomPlot;
class QCPBars;
class ModelMapper;

//! Slice of 2D IntensityData along x-axis
class BA_CORE_API_ VerticalSlicePlot : public QWidget
{
    Q_OBJECT
public:
    explicit VerticalSlicePlot(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(128, 128); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

    void setItem(IntensityDataItem *item);

public slots:
    void plotData(const QVector<double> &x, const QVector<double> &y);

private slots:
//    void onPropertyChanged(const QString &property_name);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);

private:
    void plotItem(IntensityDataItem *intensityItem);
    void setLogz(bool logz, bool isReplot = false);
    void setXmin(double value);
    void setXmax(double value);
    void setYmin(double value);
    void setYmax(double value);
    void setZmin(double value);
    void setZmax(double value);

    QCustomPlot *m_customPlot;
    QCPBars *m_bars;
    IntensityDataItem *m_item;
//    ModelMapper *m_mapper;
    std::unique_ptr<ModelMapper> m_mapper;
};




#endif
