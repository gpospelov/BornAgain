// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/OutputDataWidgets/IntensityDataPlotWidget.h
//! @brief     Defines class IntensityDataPlotWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAPLOTWIDGET_H
#define INTENSITYDATAPLOTWIDGET_H

#include "WinDllMacros.h"
#include <QWidget>

class QSplitter;
class NHistogramPlot;
class ColorMapPlot;
class QLabel;
class NIntensityDataItem;

class BA_CORE_API_ IntensityDataPlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IntensityDataPlotWidget(QWidget *parent = 0);

    QSize sizeHint() const { return QSize(800, 800); }
    QSize minimumSizeHint() const { return QSize(512, 512); }

    void setItem(NIntensityDataItem *item);

public slots:
    void onSplitterMoved(int pos, int index);

private slots:
    void onPropertyChanged(const QString &property_name);

private:
//    void initSplitterSizes(int horizontal_size, int vertical_size);
    void initLeftRightAreaSize(int left_size, int right_size);
    void initBottomTopAreaSize(int bottom_size, int top_size);

    QSplitter *m_splitter;
    QSplitter *m_splitterTop;
    QSplitter *m_splitterBottom;
    ColorMapPlot *m_centralPlot;
    NHistogramPlot *m_verticalPlot;
    NHistogramPlot *m_horizontalPlot;
    QLabel *m_statusLabel;
    int m_leftHistogramArea;
    int m_bottomHistogramArea;
    NIntensityDataItem *m_item;
};




#endif
