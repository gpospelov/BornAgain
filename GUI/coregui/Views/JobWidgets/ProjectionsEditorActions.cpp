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
#include "SessionModel.h"
#include <QAction>
#include <QItemSelectionModel>
#include <QModelIndexList>

ProjectionsEditorActions::ProjectionsEditorActions(QWidget* parent)
    : QObject(parent)
    , m_resetViewAction(new QAction(this))
    , m_togglePanelAction(new QAction(this))
    , m_model(nullptr)
    , m_selectionModel(nullptr)
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

    m_deleteAction = new QAction(QStringLiteral("Remove selected"), parent);
    m_deleteAction->setToolTip("Remove selected (Del)");
    m_deleteAction->setShortcuts(QKeySequence::Delete);
    parent->addAction(m_deleteAction);
    connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(onDeleteAction()));
}

void ProjectionsEditorActions::setModel(SessionModel* maskModel, const QModelIndex& rootIndex)
{
    m_model = maskModel;
    m_rootIndex = rootIndex;
}

void ProjectionsEditorActions::setSelectionModel(QItemSelectionModel* selectionModel)
{
    m_selectionModel = selectionModel;
}

QList<QAction*> ProjectionsEditorActions::topToolBarActions()
{
    return QList<QAction*>() << m_resetViewAction << m_togglePanelAction;
}

void ProjectionsEditorActions::onDeleteAction()
{
    Q_ASSERT(m_model);
    Q_ASSERT(m_selectionModel);

    QModelIndexList indexes = m_selectionModel->selectedIndexes();
    while (indexes.size()) {
        m_model->removeRows(indexes.back().row(), 1, indexes.back().parent());
        indexes = m_selectionModel->selectedIndexes();
    }
}
