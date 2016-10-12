// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h
//! @brief     Defines class IntensityDataPropertyWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef INTENSITYDATAPROPERTYWIDGET_H
#define INTENSITYDATAPROPERTYWIDGET_H

#include "SessionItemWidget.h"

class JobModel;
class IntensityDataItem;
class ComponentEditor;
class SessionItem;

//! The IntensityDataPropertyWidget shows ComponentEditor for given IntensityDataItem.

class BA_CORE_API_ IntensityDataPropertyWidget : public SessionItemWidget
{
    Q_OBJECT
public:
    explicit IntensityDataPropertyWidget(QWidget *parent = 0);
    ~IntensityDataPropertyWidget();

    QSize sizeHint() const { return QSize(230, 256); }
    QSize minimumSizeHint() const { return QSize(230, 64); }

    void setItem(SessionItem *item);

    QList<QAction *> actionList();

public slots:
    void onTogglePanelAction();

private:
    void setPanelVisible(bool visible);

    QAction *m_togglePanelAction;
    SessionItem *m_currentItem;
    ComponentEditor *m_componentEditor;
};

#endif // INTENSITYDATAPROPERTYWIDGET_H
