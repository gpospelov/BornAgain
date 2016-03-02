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
#include "BeamItem.h"
#include "InstrumentItem.h"
#include "ComponentEditor.h"
#include "item_constants.h"
#include "MultiLayerItem.h"
#include "SampleBuilderFactory.h"
#include "GUIObjectBuilder.h"
#include "InstrumentModel.h"
#include "SessionProxyModels.h"
#include <QItemSelectionModel>
#include <QHBoxLayout>
#include <QTreeView>
#include <QDebug>

TestComponentView::TestComponentView(MainWindow *mainWindow)
    : QWidget(mainWindow)
    , m_mainWindow(mainWindow)
    , m_model(new SampleModel(this))
    , m_treeView(new QTreeView)
    , m_treeView2(new QTreeView)
    , m_editor1(new ComponentEditor)
    , m_editor2(new ComponentEditor)
//    , m_editor2(0)
//    , m_editor3(0)
    , m_editor3(new ComponentEditor)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_treeView);
    hlayout->addWidget(m_editor1);

    QVBoxLayout *rightPanel = new QVBoxLayout;
    rightPanel->addWidget(m_editor2);
    rightPanel->addWidget(m_editor3);
//    rightPanel->addWidget(m_treeView2);

    hlayout->addLayout(rightPanel);

    mainLayout->addLayout(hlayout);
    setLayout(mainLayout);

    init_editors();
}

void TestComponentView::onSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    qDebug() << "TestComponentView::onSelectionChanged" << selected;

    QModelIndexList indices = selected.indexes();

    if(indices.isEmpty()) {
//        m_editor2->setItem(0);
//        m_editor3->setItem(0);
    } else {
        if(ParameterizedItem *item = m_model->itemForIndex(indices.at(0))) {
//            m_editor2->setItem(item);
//            m_editor2->addItem(item);
//            m_editor3->setItem(item);
        }
    }

}

void TestComponentView::init_editors()
{
    // sample model
//    SampleBuilderFactory factory;
//    boost::scoped_ptr<ISample> P_sample(factory.createSample("CylindersInDWBABuilder"));

//    GUIObjectBuilder guiBuilder;
//    guiBuilder.populateSampleModel(m_model, *P_sample);

    m_model->insertNewItem(Constants::ParticleType);

    // tree view
    m_treeView->setModel(m_model);
    m_treeView->expandAll();


//    SessionCompactModel *compactModel = new SessionCompactModel();
//    SessionTestModel *compactModel = new SessionTestModel();
//    compactModel->setSourceModel(m_model);

//    m_treeView2->setModel(compactModel);
//    m_treeView2->expandAll();

    connect(m_treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection, QItemSelection)));


    // editors
//    m_editor1->setPresentationType(ComponentEditorFlags::SHOW_DETAILED | ComponentEditorFlags::BROWSER_TABLE);
//    m_editor2->setFlat();
//    m_editor2->setPresentationType(ComponentEditorFlags::SHOW_CONDENSED | ComponentEditorFlags::BROWSER_TABLE);
//    m_editor3->setPresentationType(ComponentEditorFlags::SHOW_CONDENSED | ComponentEditorFlags::BROWSER_GROUPBOX);

    m_editor1->setItem(m_model->getTopItem());

//    InstrumentModel *model = m_mainWindow->getInstrumentModel();
//    InstrumentItem *instrument = model->getInstrumentItem();
//    Q_ASSERT(instrument);

//    m_editor1->setItem(instrument);

//    BeamItem *beamItem = instrument->getBeamItem();
//    Q_ASSERT(beamItem);

//    m_editor2->setItem(beamItem->getGroupItem(BeamItem::P_WAVELENGTH));
//    m_editor3->setItem(beamItem->getGroupItem(BeamItem::P_WAVELENGTH));
}



