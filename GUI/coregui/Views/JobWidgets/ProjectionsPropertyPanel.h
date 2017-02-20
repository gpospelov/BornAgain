// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsPropertyPanel.h
//! @brief     Defines class ProjectionsPropertyPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef PROJECTIONSPROPERTYPANEL_H
#define PROJECTIONSPROPERTYPANEL_H

#include "SessionItemWidget.h"

class ComponentEditor;

class BA_CORE_API_ ProjectionsPropertyPanel : public SessionItemWidget
{
    Q_OBJECT

public:
    ProjectionsPropertyPanel(QWidget* parent = 0);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

protected:
    virtual void subscribeToItem();
    virtual void unsubscribeFromItem();

private:
    ComponentEditor* m_componentEditor;
};

#endif // PROJECTIONSPROPERTYPANEL_H
