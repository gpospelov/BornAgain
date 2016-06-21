// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/IntensityDataWidgetActions.cpp
//! @brief     Implements class IntensityDataWidgetActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "IntensityDataWidgetActions.h"
#include <QAction>

IntensityDataWidgetActions::IntensityDataWidgetActions(QObject *parent)
    : QObject(parent)
    , m_toggleProjectionsAction(0)
    , m_togglePropertyPanelAction(0)
    , m_resetViewAction(0)
    , m_savePlotAction(0)

{
    // projections button
    m_toggleProjectionsAction = new QAction(this);
    m_toggleProjectionsAction->setText("Projections");
    m_toggleProjectionsAction->setIcon(QIcon(":/images/toolbar_projections.png"));
    m_toggleProjectionsAction->setToolTip("Toggle Projections, Ctrl+P");
    m_toggleProjectionsAction->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(m_toggleProjectionsAction, SIGNAL(clicked()), this, SIGNAL(toggleProjections()));

    // plot properties button
    m_togglePropertyPanelAction = new QAction(this);
    m_togglePropertyPanelAction->setText("Plot Properties");
    m_togglePropertyPanelAction->setIcon(QIcon(":/images/toolbar_propertypanel.png"));
    m_togglePropertyPanelAction->setToolTip("Toggle Property Panel");
    connect(m_togglePropertyPanelAction, SIGNAL(clicked()), this, SIGNAL(togglePropertyPanel()));

    // reset view button
    m_resetViewAction = new QAction(this);
    m_resetViewAction->setText("Reset View");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar_refresh.png"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, SIGNAL(clicked()), this, SIGNAL(resetView()));

    // save plot button
    m_savePlotAction = new QAction(this);
    m_savePlotAction->setText("Save Plot");
    m_savePlotAction->setIcon(QIcon(":/images/toolbar_save.png"));
    m_savePlotAction->setToolTip("Save Plot");
    connect(m_savePlotAction, SIGNAL(clicked()), this, SIGNAL(savePlot()));
}

QList<QAction *> IntensityDataWidgetActions::actionList()
{
    return QList<QAction *>() << m_resetViewAction << m_toggleProjectionsAction
                              << m_togglePropertyPanelAction << m_savePlotAction;
}
