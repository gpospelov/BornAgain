// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditor.cpp
//! @brief     Implements class MaskEditor
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditor.h"
#include "MaskEditorCanvas.h"
#include "MaskEditorToolPanel.h"
#include "MaskEditorToolBar.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QDebug>

#include "SimulationRegistry.h"
#include <boost/scoped_ptr.hpp>
#include "SampleBuilderFactory.h"
#include "IntensityDataItem.h"
#include "MaskModel.h"
#include "MaskItems.h"


MaskEditor::MaskEditor(QWidget *parent)
    : QMainWindow(parent)
    , m_toolBar(new MaskEditorToolBar)
    , m_editorCanvas(new MaskEditorCanvas(this))
    , m_editorToolPanel(new MaskEditorToolPanel(this))
    , m_splitter(new QSplitter(this))
    , m_maskModel(0)
{
    setObjectName(QStringLiteral("IntensityDataPlotWidget"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_splitter->addWidget(m_editorCanvas);
    m_splitter->addWidget(m_editorToolPanel);

//    QVBoxLayout *mainLayout = new QVBoxLayout(this);
//    mainLayout->setMargin(0);
//    mainLayout->setSpacing(0);
//    mainLayout->addWidget(m_splitter);
//    setLayout(mainLayout);

//    QWidget *widget = new QWidget;
//    widget->setLayout(mainLayout);

    addToolBar(m_toolBar);

    setCentralWidget(m_splitter);

    init_test_model();

    setup_connections();
}

void MaskEditor::onToolPanelRequest()
{
    qDebug() << "MaskEditor::onToolPanelRequest()";
    m_editorToolPanel->setHidden(!m_editorToolPanel->isHidden());
}

void MaskEditor::init_test_model()
{
    m_maskModel = new MaskModel();

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    SampleBuilderFactory sampleFactory;
    boost::scoped_ptr<ISample> sample(sampleFactory.createSample("CylindersAndPrismsBuilder"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    IntensityDataItem *item = dynamic_cast<IntensityDataItem *>(m_maskModel->insertNewItem(Constants::IntensityDataType));
    Q_ASSERT(item);
    item->setOutputData(simulation->getOutputData()->clone());
    qDebug() << item->getXmin() << item->getXmax() << item->getYmin() << item->getYmax();

//    RectangleItem *rect = dynamic_cast<RectangleItem *>(m_maskModel->insertNewItem(Constants::RectangleMaskType, m_maskModel->indexOfItem(item)));
//    Q_ASSERT(rect);
//    rect->setRegisteredProperty(RectangleItem::P_POSX, 0.6);
//    rect->setRegisteredProperty(RectangleItem::P_POSY, 1.5);
//    rect->setRegisteredProperty(RectangleItem::P_WIDTH, 0.3);
//    rect->setRegisteredProperty(RectangleItem::P_HEIGHT, 0.2);

//    ParameterizedItem *poly = m_maskModel->insertNewItem(Constants::PolygonMaskType, m_maskModel->indexOfItem(item));

//    ParameterizedItem *p1 = m_maskModel->insertNewItem(Constants::PolygonPointType, m_maskModel->indexOfItem(poly));
//    p1->setRegisteredProperty(PolygonPointItem::P_POSX, 0.6);
//    p1->setRegisteredProperty(PolygonPointItem::P_POSY, 1.5);
//    ParameterizedItem *p2 = m_maskModel->insertNewItem(Constants::PolygonPointType, m_maskModel->indexOfItem(poly));
//    p2->setRegisteredProperty(PolygonPointItem::P_POSX, 1.0);
//    p2->setRegisteredProperty(PolygonPointItem::P_POSY, 1.5);
//    ParameterizedItem *p3 = m_maskModel->insertNewItem(Constants::PolygonPointType, m_maskModel->indexOfItem(poly));
//    p3->setRegisteredProperty(PolygonPointItem::P_POSX, 1.0);
//    p3->setRegisteredProperty(PolygonPointItem::P_POSY, 0.6);



    m_editorCanvas->setModel(m_maskModel, m_maskModel->indexOfItem(item));
    m_editorToolPanel->setModel(m_maskModel, m_maskModel->indexOfItem(item));
    m_editorCanvas->setSelectionModel(m_editorToolPanel->selectionModel());


}

void MaskEditor::setup_connections()
{
    // selection/drawing activity is propagated from tool bar to graphics scene
    connect(m_toolBar,
            SIGNAL(activityModeChanged(MaskEditorActivity::Flags)),
            m_editorCanvas->getScene(),
            SLOT(onActivityModeChanged(MaskEditorActivity::Flags))
            );

    // tool panel request is propagated from tool bar to this MaskEditor
    connect(m_toolBar,
            SIGNAL(toolPanelRequest()),
            this,
            SLOT(onToolPanelRequest())
            );

    // mask stacking order change request is propagated from tool bar to graphics scene
    connect(m_toolBar,
            SIGNAL(changeStackingOrderRequest(MaskEditorActivity::EMoveType)),
            m_editorCanvas->getScene(),
            SLOT(onMaskStackingOrderRequest(MaskEditorActivity::EMoveType))
            );

    // space bar push (request for zoom mode) is propagated from graphics view to tool bar
    connect(m_editorCanvas->getView(),
            SIGNAL(changeActivityRequest(MaskEditorActivity::Flags)),
            m_toolBar,
            SLOT(onChangeActivityRequest(MaskEditorActivity::Flags))
            );
}
