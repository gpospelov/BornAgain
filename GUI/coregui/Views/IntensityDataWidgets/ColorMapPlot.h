// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/ColorMapPlot.h
//! @brief     Declares class ColorMapPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef COLORMAPPLOT_H
#define COLORMAPPLOT_H

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

//! 2D color map widget for IntensityData
class BA_CORE_API_ ColorMapPlot : public QWidget
{
    Q_OBJECT
public:
    explicit ColorMapPlot(QWidget *parent = 0);
    ~ColorMapPlot();

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    void setItem(IntensityDataItem *item);

    QString getStatusString();

    void drawLinesOverTheMap();

    void showLinesOverTheMap(bool isVisible);

    QCustomPlot *getCustomPlot() { return m_customPlot; }

    //! transform axes coordinates to CustomPlot widget coordinates
    double xAxisCoordToPixel(double axis_coordinate) const;
    double yAxisCoordToPixel(double axis_coordinate) const;

    //! transform widget coordinates to axes coordinates
    double pixelToXaxisCoord(double pixel) const;
    double pixelToYaxisCoord(double pixel) const;

    //! returns rectangle representing current axes zoom state in widget coordinates
    QRectF getViewportRectangleInWidgetCoordinates();

    void setTrackMoveEventsFlag(bool flag);

signals:
    void validMousMove();

public slots:
    void setLogz(bool logz, bool isReplot = false);
    void resetView();
    void onMouseMove(QMouseEvent *event);

    void getHorizontalSlice(QVector<double> &x, QVector<double> &y);
    void getVerticalSlice(QVector<double> &x, QVector<double> &y);

private slots:
    void onIntensityModified();
    void onPropertyChanged(const QString &property_name);
    void onSubItemPropertyChanged(const QString &property_group, const QString &property_name);
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

    void plotItem(IntensityDataItem *intensityItem);

    void setConnected(bool isConnected);

    void setAxesRangeConnected(bool isConnected);
    void setDataRangeConnected(bool isConnected);
    void setMouseMoveConnected(bool isConnected);


    QCPRange calculateDataRange(IntensityDataItem *intensityItem);
    void setFixedColorMapMargins();

    void setColorMapFromItem(IntensityDataItem *intensityItem);
    void setAxesRangeFromItem(IntensityDataItem *item);
    void setAxesZoomFromItem(IntensityDataItem *item);
    void setLabelsFromItem(IntensityDataItem *item);
    void setDataFromItem(IntensityDataItem *item);
    void setColorScaleAppearanceFromItem(IntensityDataItem *item);
    void setDataRangeFromItem(IntensityDataItem *item);

    void setColorScaleVisible(bool visibility_flag);

    QCustomPlot *m_customPlot;
    QCPColorMap *m_colorMap;
    QCPColorScale *m_colorScale;

    IntensityDataItem *m_item;

    bool m_block_update;
    PositionData m_posData;
};



#endif
