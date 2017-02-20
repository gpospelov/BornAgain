// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/ProjectionsEditor.cpp
//! @brief     Implements class ProjectionsEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ProjectionsEditor.h"
#include "ProjectionsEditorActions.h"
#include "ProjectionsToolBar.h"
#include "ProjectionsWidget.h"
#include "ProjectionsPropertyPanel.h"
#include "ProjectionsEditorCanvas.h"
#include "minisplitter.h"
#include "SessionModel.h"
#include "IntensityDataItem.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>

ProjectionsEditor::ProjectionsEditor(QWidget* parent)
    : QMainWindow(parent)
    , m_editorActions(new ProjectionsEditorActions(this))
    , m_toolBar(new ProjectionsToolBar(m_editorActions))
    , m_projectionsCanvas(new ProjectionsEditorCanvas)
    , m_projectionsWidget(new ProjectionsWidget)
    , m_propertyPanel(new ProjectionsPropertyPanel)
    , m_rightSplitter(new Manhattan::MiniSplitter)
    , m_bottomSplitter(new QSplitter)
{
    addToolBar(Qt::RightToolBarArea, m_toolBar);

    m_bottomSplitter->setOrientation(Qt::Vertical);
    m_bottomSplitter->addWidget(m_projectionsCanvas);
    m_bottomSplitter->addWidget(m_projectionsWidget);
    m_bottomSplitter->setStyleSheet("background-color:white;");

    m_rightSplitter->addWidget(m_bottomSplitter);
    m_rightSplitter->addWidget(m_propertyPanel);

    setCentralWidget(m_rightSplitter);
}

void ProjectionsEditor::setContext(SessionModel* model, const QModelIndex& shapeContainerIndex,
                                   IntensityDataItem* intensityItem)
{
    Q_UNUSED(model);
    Q_UNUSED(shapeContainerIndex);
    m_propertyPanel->setItem(intensityItem);
}
