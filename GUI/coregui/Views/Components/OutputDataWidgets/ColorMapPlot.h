// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/ColorMapPlot.h
//! @brief     Defines class ColorMapPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPPLOT_H
#define COLORMAPPLOT_H

#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>
#include <QMap>

class NIntensityDataItem;
class QCustomPlot;
class QCPColorMap;
class QCPColorScale;

class BA_CORE_API_ ColorMapPlot : public QWidget
{
    Q_OBJECT
public:
    explicit ColorMapPlot(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(64, 64); }
    QSize minimumSizeHint() const { return QSize(64, 64); }

    void setItem(NIntensityDataItem *item);

public slots:
    void setLogz(bool logz, bool isReplot = true);
    void resetView();

private slots:
    void onPropertyChanged(const QString &property_name);
    void onDataRangeChanged(QCPRange newRange);
    void onXaxisRangeChanged(QCPRange newRange);
    void onYaxisRangeChanged(QCPRange newRange);

private:
    void initColorMap();
    void plotItem(NIntensityDataItem *intensityItem);
    QCPRange calculateDataRange(NIntensityDataItem *intensityItem);

    QCustomPlot *m_customPlot;
    QCPColorMap *m_colorMap;
    QCPColorScale *m_colorScale;

    NIntensityDataItem *m_item;

    QMap<QString, QCPColorGradient > m_gradient_map;
    bool m_block_update;
};



#endif
