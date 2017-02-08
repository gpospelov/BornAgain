// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/InfoWidgets/DistributionWidget.h
//! @brief     Defines class DistributionWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DISTRIBUTIONWIDGET_H
#define DISTRIBUTIONWIDGET_H

#include "WarningSignWidget.h"
#include "qcustomplot.h"
#include <QWidget>

class SessionItem;
class QLabel;
class QCustomPlot;
class DistributionItem;
class QAction;
class RealLimits;

//! The DistributionWidget class plots 1d functions corresponding to domain's Distribution1D
class DistributionWidget : public QWidget
{
    Q_OBJECT

public:
    DistributionWidget(QWidget *parent = 0);
    ~DistributionWidget();

    void setItem(DistributionItem *item);
    void plotItem();
    void setXAxisName(const QString& xAxisName);

public slots:
    void onMouseMove(QMouseEvent *event);
    void onMousePress(QMouseEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void resetView();

private:
    void init_plot();
    void plot_distributions();
    void plot_single_value();
    void plot_multiple_values();
    void setPlotRange(const QPair<double, double>& xRange, const QPair<double, double>& yRange);
    void plotBars(const QVector<double>& xbars, const QVector<double>& ybars);
    void plotFunction(const QVector<double>& xFunc, const QVector<double>& ybars);
    void plotVerticalLine(double xMin, double yMin, double xMax, double yMax,
                          const QColor& color = Qt::blue);
    void plotLimits(const RealLimits& limits);
    QPoint positionForWarningSign();

    QCustomPlot *m_plot;
    DistributionItem *m_item;
    QLabel *m_label;
    QAction *m_resetAction;
    QCPRange m_xRange, m_yRange;
    WarningSignWidget *m_warningSign;
};

#endif // DISTRIBUTIONWIDGET_H
