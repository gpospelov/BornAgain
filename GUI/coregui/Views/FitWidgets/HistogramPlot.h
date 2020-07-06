// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/HistogramPlot.h
//! @brief     Defines class HistogramPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "Wrap/WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>

class BA_CORE_API_ HistogramPlot : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramPlot(QWidget* parent = 0);

public slots:
    void addData(double x, double y);
    void addData(const QVector<double>& x, const QVector<double>& y);
    void setData(const QVector<double>& x, const QVector<double>& y);
    void clearData();

private:
    void initGraph();

    QCustomPlot* m_customPlot;
};

#endif // HISTOGRAMPLOT_H
