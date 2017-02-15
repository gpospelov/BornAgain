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
class IntensityDataCanvas;
class IntensityDataPropertyWidget;
class IntensityDataItem;
class QAction;
class TestWidget;

//! A common widget to display color map (IntensityDataCanvas) and properties
//! (IntensityDataPropertyWidget) of intensity data item.

class BA_CORE_API_ IntensityDataWidget : public SessionItemWidget
{
    Q_OBJECT

public:
    IntensityDataWidget(QWidget* parent = 0);

    void setItem(SessionItem* item);

    QList<QAction*> actionList();

private slots:
    void onContextMenuRequest(const QPoint& point);

private:
    IntensityDataCanvas* m_intensityWidget;
    IntensityDataPropertyWidget* m_propertyWidget;
};

#endif // INTENSITYDATAWIDGET_H
