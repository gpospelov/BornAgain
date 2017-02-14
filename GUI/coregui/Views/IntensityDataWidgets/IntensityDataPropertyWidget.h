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

class IntensityDataItem;
class ComponentEditor;
class SessionItem;

//! The IntensityDataPropertyWidget shows ComponentEditor for given IntensityDataItem.

class BA_CORE_API_ IntensityDataPropertyWidget : public NewSessionItemWidget
{
    Q_OBJECT
public:
    explicit IntensityDataPropertyWidget(QWidget* parent = 0);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    QList<QAction*> actionList();

public slots:
    void onTogglePanelAction();

protected:
    virtual void subscribeToItem();
    virtual void unsubscribeFromItem();

private:
    QAction* m_togglePanelAction;
    ComponentEditor* m_componentEditor;
};

#endif // INTENSITYDATAPROPERTYWIDGET_H
