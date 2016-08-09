// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidget.h
//! @brief     Defines class IntensityDataWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAWIDGET_H
#define INTENSITYDATAWIDGET_H

#include "SessionItemWidget.h"

class SessionItem;
class IntensityDataItem;
class ColorMapCanvas;
class QAction;

//! The IntensityDataWidget class represents IntensityDataItem as color map,
//! provides standard actions (reset view, save as) for external toolbars and context menus.

class BA_CORE_API_ IntensityDataWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit IntensityDataWidget(QWidget *parent = 0);

    void setItem(SessionItem *item);
    void setIntensityData(IntensityDataItem *intensityItem);

    QSize sizeHint() const { return QSize(500, 400); }
    QSize minimumSizeHint() const { return QSize(128, 128); }

    QList<QAction *> actionList();

public slots:
    void onResetViewAction();
    void onSavePlotAction();

private:
    void initActions();

    ColorMapCanvas *m_colorMap;
    IntensityDataItem *m_currentItem;
    QAction *m_resetViewAction;
    QAction *m_savePlotAction;
};

#endif // INTENSITYDATAWIDGET_H
