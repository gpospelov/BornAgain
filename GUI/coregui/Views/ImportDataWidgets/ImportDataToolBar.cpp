// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataWidgets/ImportDataToolBar.cpp
//! @brief     Implements class ImportDataToolBar
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ImportDataToolBar.h"
#include <QAction>

ImportDataToolBar::ImportDataToolBar(QWidget *parent)
    : StyledToolBar(parent)
    , m_importDataAction(0)
    , m_cloneDataAction(0)
    , m_removeDataAction(0)
{

    m_importDataAction = new QAction(QStringLiteral("Add new material"), parent);
    m_importDataAction->setIcon(QIcon(":/images/toolbar32dark_newitem.svg"));
    m_importDataAction->setToolTip(QStringLiteral("Add new material"));
    connect(m_importDataAction, SIGNAL(triggered()), this,
            SLOT(onImportDataAction()));
    addAction(m_importDataAction);

    m_cloneDataAction = new QAction(QStringLiteral("Clone material"), parent);
    m_cloneDataAction->setIcon(
        QIcon(":/images/toolbar32dark_cloneitem.svg"));
    m_cloneDataAction->setToolTip(QStringLiteral("Clone selected material"));
    connect(m_cloneDataAction, SIGNAL(triggered()), this,
            SLOT(onCloneDataAction()));
    addAction(m_cloneDataAction);

    m_removeDataAction = new QAction(QStringLiteral("Remove selected material"), parent);
    m_removeDataAction->setIcon(QIcon(":/images/toolbar32dark_remove.svg"));
    m_removeDataAction->setToolTip(QStringLiteral("Remove selected material"));
    connect(m_removeDataAction, SIGNAL(triggered()), this,
            SLOT(onRemoveDataAction()));
    addAction(m_removeDataAction);

}

void ImportDataToolBar::onImportDataAction()
{

}

void ImportDataToolBar::onCloneDataAction()
{

}

void ImportDataToolBar::onRemoveDataAction()
{

}
