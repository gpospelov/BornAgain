// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SessionModelView.cpp
//! @brief     Implements class SessionModelView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SessionModelView.h"
#include "InstrumentModel.h"
#include "JobModel.h"
#include "MaterialModel.h"
#include "RealDataModel.h"
#include "SampleModel.h"
#include "ModelTreeView.h"
#include "mainwindow.h"
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

SessionModelView::SessionModelView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
    , m_toolBar(new QToolBar)
    , m_tabs(new QTabWidget)
    , m_expandCollapseButton(new QToolButton)
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_expandCollapseButton->setText("Expand / collapse tree");
    m_expandCollapseButton->setIcon(QIcon(":/images/toolbar_expand_collapse_tree.svg"));
    m_expandCollapseButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_expandCollapseButton->setToolTip("Click to  switch between expanded/collapsed tree view");
    m_toolBar->addWidget(m_expandCollapseButton);
    connect(m_expandCollapseButton, SIGNAL(clicked()), this, SLOT(onExpandCollapseTree()));

    layout->addWidget(m_toolBar);
    layout->addWidget(m_tabs);
    setLayout(layout);

    init_tabs();
}

void SessionModelView::onExpandCollapseTree()
{
    m_content.at(m_tabs->currentIndex())->toggleExpanded();
}

//! Creates content for tab widget.

void SessionModelView::init_tabs()
{
    Q_ASSERT(m_content.empty());

    for (auto model : modelsForTabs()) {
        auto treeView = new ModelTreeView(this, model);
        m_tabs->addTab(treeView, treeView->objectName());
        m_content.push_back(treeView);
    }
}

//! Returns list of models to show in tabs.

QList<SessionModel*> SessionModelView::modelsForTabs()
{
    QList<SessionModel*> result = QList<SessionModel*>()
            << m_mainWindow->instrumentModel()
            << m_mainWindow->sampleModel()
            << m_mainWindow->realDataModel()
            << m_mainWindow->materialModel()
            << m_mainWindow->jobModel();
    return result;
}

