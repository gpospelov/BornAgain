// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/TestView.cpp
//! @brief     Implements class TestView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //
#include "TestComponentView.h"
#include "mainwindow.h"
#include "SampleModel.h"
#include "ComponentEditor.h"
#include "item_constants.h"
#include "MultiLayerItem.h"
#include "SampleBuilderFactory.h"
#include "GUIObjectBuilder.h"
#include <QItemSelectionModel>
#include <QHBoxLayout>
#include <QTreeView>
#include <QDebug>

TestComponentView::TestComponentView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
    , m_model(new SampleModel(this))
    , m_treeView(new QTreeView)
    , m_editor1(new ComponentEditor)
    , m_editor2(new ComponentEditor)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_treeView);
    hlayout->addWidget(m_editor1);
    hlayout->addWidget(m_editor2);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

    init_editors();
}

void TestComponentView::onSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    qDebug() << "TestComponentView::onSelectionChanged" << selected;

    QModelIndexList indices = selected.indexes();

    if(indices.isEmpty()) {
        m_editor2->setItem(0);
    } else {
        if(ParameterizedItem *item = m_model->itemForIndex(indices.at(0))) {
            m_editor2->setItem(item);
        }
    }

}

void TestComponentView::init_editors()
{
    // sample model
    SampleBuilderFactory factory;
    boost::scoped_ptr<ISample> P_sample(factory.createSample("CylindersInDWBABuilder"));

    GUIObjectBuilder guiBuilder;
    guiBuilder.populateSampleModel(m_model, *P_sample);

//    m_model->insertNewItem(Constants::ParticleType);

    // tree view
    m_treeView->setModel(m_model);
    m_treeView->expandAll();
    connect(m_treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));


    // editors
    m_editor1->setPresentationType(ComponentEditorFlags::SHOW_DETAILED | ComponentEditorFlags::BROWSER_TABLE);
//    m_editor2->setPresentationType(ComponentEditor::SHOW_CONDENSED);

//    m_editor1->setItem(m_model->getMultiLayerItem());
    m_editor1->setItem(m_model->getTopItem());
}



