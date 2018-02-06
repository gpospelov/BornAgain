// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataWidget.h
//! @brief     Defines class SpecularDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDATACANVAS_H
#define SPECULARDATACANVAS_H

#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>

class SpecularDataItem;

class BA_CORE_API_ SpecularDataCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit SpecularDataCanvas(QWidget* parent = nullptr);

public slots:
    void setData(SpecularDataItem* data_item);
    void clearData();

private:
    void initGraph();
    void initGraphFromItem();
    SpecularDataItem* intensityData() {return m_data_item;}

    QCustomPlot* m_customPlot;
    SpecularDataItem* m_data_item;
};

#endif // SPECULARDATACANVAS_H
