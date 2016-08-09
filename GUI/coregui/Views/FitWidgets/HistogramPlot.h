// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/HistogramPlot.h
//! @brief     Defines class HistogramPlot
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef HISTOGRAMPLOT_H
#define HISTOGRAMPLOT_H

#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>

class BA_CORE_API_ HistogramPlot : public QWidget
{
    Q_OBJECT
public:
    explicit HistogramPlot(QWidget *parent = 0);

public slots:
//    bool addData(double x, double y);

    void addData(double x, double y);
    void addData(const QVector<double> &x, const QVector<double> y);
    void setData(const QVector<double> &x, const QVector<double> y);

    void clearData();

private:

    QCustomPlot *m_customPlot;

};

#endif // HISTOGRAMPLOT_H

