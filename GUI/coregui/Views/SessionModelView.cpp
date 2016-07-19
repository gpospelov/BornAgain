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
#include "SessionModelDelegate.h"
#include "mainwindow.h"
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QVBoxLayout>


SessionModelView::ModelTree::ModelTree(SessionModel *model, QTreeView *tree)
    : m_model(model), m_tree(tree), m_is_expanded(false)
{
    Q_ASSERT(m_model);
    Q_ASSERT(m_tree);
    m_tree->setModel(m_model);
    if(model->rowCount(QModelIndex()) > 0) {
        setExpanded(true);
    }
}

void SessionModelView::ModelTree::toggleExpanded()
{
    setExpanded(!isExpanded());
}

void SessionModelView::ModelTree::setExpanded(bool expanded)
{
    Q_ASSERT(m_tree);
    if(expanded) {
        m_tree->expandAll();
        m_tree->resizeColumnToContents(0);
        m_tree->resizeColumnToContents(1);
    } else {
        m_tree->collapseAll();
    }
    m_is_expanded = expanded;
}

void SessionModelView::ModelTree::setActive(bool is_active)
{
    if(is_active) {
        if(m_tree->model()) return;
        m_tree->setModel(m_model);
        setExpanded(true);
    } else {
        if(!m_tree->model()) return;
        m_tree->setModel(0);
    }
}


SessionModelView::SessionModelView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
    , m_toolBar(new QToolBar(this))
    , m_tabs(new QTabWidget(this))
    , m_expandCollapseButton(0)
    , m_delegate(new SessionModelDelegate(this))
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_expandCollapseButton = new QToolButton;
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

    //setViewActive(false);

}

//! Sets given view to enabled/disable state. If disabled, all trees will be disconnected from models
void SessionModelView::setViewActive(bool is_active)
{
    for(int i=0; i<m_content.size(); ++i) {
        m_content[i].setActive(is_active);
    }
}

void SessionModelView::onExpandCollapseTree()
{
    m_content[m_tabs->currentIndex()].toggleExpanded();
}

void SessionModelView::init_tabs()
{
    m_content.clear();
    m_content.push_back(ModelTree(m_mainWindow->instrumentModel(), new QTreeView(this)));
    m_content.push_back(ModelTree(m_mainWindow->sampleModel(), new QTreeView(this)));
    m_content.push_back(ModelTree(m_mainWindow->realDataModel(), new QTreeView(this)));
    m_content.push_back(ModelTree(m_mainWindow->materialModel(), new QTreeView(this)));
    m_content.push_back(ModelTree(m_mainWindow->jobModel(), new QTreeView(this)));
    for(int i=0; i<m_content.size(); ++i) {
        m_tabs->addTab(m_content[i].m_tree, m_content[i].m_model->getModelTag());
        m_content[i].m_tree->setItemDelegate(m_delegate);
    }
}

