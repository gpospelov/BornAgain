// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SpecularDataWidgets/SpecularDataCanvas.h
//! @brief     Defines class SpecularDataCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARDATACANVAS_H
#define SPECULARDATACANVAS_H

#include "SessionItemWidget.h"
#include "WinDllMacros.h"
#include "qcustomplot.h"
#include <QWidget>

class SpecularDataItem;

class BA_CORE_API_ SpecularDataCanvas : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit SpecularDataCanvas(QWidget* parent = nullptr);

    void setItem(SessionItem* intensityItem) override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    QList<QAction*> actionList() override;

public slots:
    void onResetViewAction();
    void onSavePlotAction();
    void onMousePress(QMouseEvent* event);
    //void clearData();

private:
    void initGraph();
    void initGraphFromItem();
    SpecularDataItem* specularDataItem();
    void initActions();

    QCustomPlot* m_customPlot;
    QAction* m_resetViewAction;
    QAction* m_savePlotAction;
};

#endif // SPECULARDATACANVAS_H
