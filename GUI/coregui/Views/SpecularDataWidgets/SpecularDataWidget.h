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

#ifndef SPECULARDATAWIDGET_H
#define SPECULARDATAWIDGET_H

#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>

class SpecularDataItem;

class BA_CORE_API_ SpecularDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpecularDataWidget(QWidget* parent = nullptr);

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

#endif // SPECULARDATAWIDGET_H
