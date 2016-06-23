// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMap.h
//! @brief     Declares class ColorMap
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAP_H
#define COLORMAP_H

#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>
#include <QMap>
#include <QPoint>
#include <memory>

class IntensityDataItem;
class QCustomPlot;
class QCPColorMap;
class QCPColorScale;
class UpdateTimer;
class ColorMapEvent;

//! The ColorMap class presents 2D intensity data from IntensityDataItem as color map.
//! Provides a minimal functionality to plot the data, interact with the axes and report mouse
//! move events to higher level. Should be a component for more complicated plotting widgets.

//! This is a replacement for ColorMapPlot.

class BA_CORE_API_ ColorMap : public QWidget {
    Q_OBJECT

public:
    explicit ColorMap(QWidget *parent = 0);
    ~ColorMap();

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    void setItem(IntensityDataItem *item);

    QString getStatusString();

    QCustomPlot *customPlot() { return m_customPlot; }

    //! transform axes coordinates to CustomPlot widget coordinates
    double xAxisCoordToPixel(double axis_coordinate) const;
    double yAxisCoordToPixel(double axis_coordinate) const;

    //! transform widget coordinates to axes coordinates
    double pixelToXaxisCoord(double pixel) const;
    double pixelToYaxisCoord(double pixel) const;

    //! returns rectangle representing current axes zoom state in widget coordinates
    QRectF getViewportRectangleInWidgetCoordinates();

    void setTrackMoveEvents(bool flag);

signals:
    void validMousMove();

public slots:
    void setLogz(bool logz);
    void resetView();

private slots:
    void onIntensityModified();
    void onPropertyChanged(const QString &property_name);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);
    void onDataRangeChanged(QCPRange newRange);
    void onXaxisRangeChanged(QCPRange newRange);
    void onYaxisRangeChanged(QCPRange newRange);
    void replot();
    void onTimeToReplot();

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

    void setConnected(bool isConnected);
    void setAxesRangeConnected(bool isConnected);
    void setDataRangeConnected(bool isConnected);
    void setUpdateTimerConnected(bool isConnected);

    void setFixedColorMapMargins();

    void setColorMapFromItem(IntensityDataItem *intensityItem);
    void setAxesRangeFromItem(IntensityDataItem *item);
    void setAxesZoomFromItem(IntensityDataItem *item);
    void setLabelsFromItem(IntensityDataItem *item);
    void setDataFromItem(IntensityDataItem *item);
    void setColorScaleAppearanceFromItem(IntensityDataItem *item);
    void setDataRangeFromItem(IntensityDataItem *item);

    void setColorScaleVisible(bool visibility_flag);

    void resetColorMap();

    QCustomPlot *m_customPlot;
    QCPColorMap *m_colorMap;
    QCPColorScale *m_colorScale;

    IntensityDataItem *m_item;

    bool m_block_update;
    PositionData m_posData;

    UpdateTimer *m_updateTimer;
    ColorMapEvent *m_colorMapEvent;

};

#endif
