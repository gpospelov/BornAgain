// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditorActions.cpp
//! @brief     Implements class ProjectionsEditorActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsEditorActions.h"
#include <QAction>

ProjectionsEditorActions::ProjectionsEditorActions(QWidget* parent)
    : QObject(parent)
    , m_resetViewAction(new QAction(this))
    , m_togglePanelAction(new QAction(this))
{
    // Actions for top toolbar
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(triggered()), this, SIGNAL(resetViewRequest()));

    m_togglePanelAction = new QAction(this);
    m_togglePanelAction->setText("Properties");
    m_togglePanelAction->setIcon(QIcon(":/images/toolbar16light_propertypanel.svg"));
    m_togglePanelAction->setToolTip("Toggle Property Panel");
    connect(m_togglePanelAction, SIGNAL(triggered()), this, SIGNAL(propertyPanelRequest()));
}

QList<QAction*> ProjectionsEditorActions::topToolBarActions()
{
    return QList<QAction*>() << m_resetViewAction << m_togglePanelAction;
}
