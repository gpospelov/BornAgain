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
#include <QPoint>

class NIntensityDataItem;
class QCustomPlot;
class QCPColorMap;
class QCPColorScale;

class BA_CORE_API_ ColorMapPlot : public QWidget
{
    Q_OBJECT
public:
    explicit ColorMapPlot(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    void setItem(NIntensityDataItem *item);

    QString getStatusString();

signals:
    void validMousMove();

public slots:
    void setLogz(bool logz, bool isReplot = true);
    void resetView();
    void onMouseMove(QMouseEvent *event);

    void getHorizontalSlice(QVector<double> &x, QVector<double> &y);

private slots:
    void onPropertyChanged(const QString &property_name);
    void onDataRangeChanged(QCPRange newRange);
    void onXaxisRangeChanged(QCPRange newRange);
    void onYaxisRangeChanged(QCPRange newRange);

private:

    class PositionData {
    public:
        PositionData() { reset(); }
        bool valid;
        int key;
        int value;
        double m_xPos;
        double m_yPos;
        double cellValue;
        void reset() {
            valid = false;
            key = 0;
            value = 0;
            m_xPos = 0;
            m_yPos = 0;
            cellValue = 0;
        }
    };

    void initColorMap();
    void plotItem(NIntensityDataItem *intensityItem);
    QCPRange calculateDataRange(NIntensityDataItem *intensityItem);

    QCustomPlot *m_customPlot;
    QCPColorMap *m_colorMap;
    QCPColorScale *m_colorScale;

    NIntensityDataItem *m_item;

    QMap<QString, QCPColorGradient > m_gradient_map;
    bool m_block_update;
    PositionData m_posData;
};



#endif
