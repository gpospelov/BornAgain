// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/IntensityDataWidgets/IntensityDataPlotWidget.h
//! @brief     Defines class IntensityDataPlotWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAPLOTWIDGET_H
#define INTENSITYDATAPLOTWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QSplitter;
class HorizontalSlicePlot;
class VerticalSlicePlot;
class ColorMapPlot;
class QLabel;
class IntensityDataItem;
class ModelMapper;

//! The widget contains IntensityDataItem color map, two projections and all
//! logic. Belongs to IntensityDataWidget.
class BA_CORE_API_ IntensityDataPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntensityDataPlotWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(800, 800); }
    QSize minimumSizeHint() const { return QSize(512, 512); }

    void setItem(IntensityDataItem *item);

signals:
    void savePlotRequest();

public slots:
    void onSplitterMoved(int pos, int index);
    void resetView();
    void onMouseMove();
    void onMousePress(QMouseEvent *event);
    void savePlot(const QString &dirname);

private slots:
    void showProjections(bool flag);
    void onPropertyPanelAction(bool flag);
    void onProjectionsAction(bool flag);
    void showContextMenu(const QPoint &point);
    void onIntensityModified();

private:
    void setupContextMenuActions();
    void updateItem(IntensityDataItem *item);
    void initLeftRightAreaSize(int left_size, int right_size);
    void initTopBottomAreaSize(int bottom_size, int top_size);
    bool isBottomAreaVisible();
    bool isLeftAreaVisible();

    QSplitter *m_splitter;
    QSplitter *m_splitterTop;
    QSplitter *m_splitterBottom;
    QAction *m_propertyPanelAction;
    QAction *m_projectionsAction;
    QAction *m_resetAction;
    QAction *m_saveAction;
    ColorMapPlot *m_centralPlot;
    VerticalSlicePlot *m_verticalPlot;
    HorizontalSlicePlot *m_horizontalPlot;
    QLabel *m_statusLabel;
    int m_leftHistogramArea;
    int m_bottomHistogramArea;
    IntensityDataItem *m_item;
    ModelMapper *m_mapper;
};

#endif
