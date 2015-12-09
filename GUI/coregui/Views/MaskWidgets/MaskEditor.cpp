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
#include "MaskEditorActions.h"
#include "MaskEditorCanvas.h"
#include "MaskEditorPropertyPanel.h"
#include "MaskEditorToolBar.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include <QBoxLayout>
#include <QSplitter>
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>

#include "SimulationRegistry.h"
#include <boost/scoped_ptr.hpp>
#include "SampleBuilderFactory.h"
#include "IntensityDataItem.h"
#include "SessionModel.h"
#include "MaskItems.h"


MaskEditor::MaskEditor(QWidget *parent)
    : QMainWindow(parent)
    , m_itemActions(new MaskEditorActions(this))
    , m_toolBar(new MaskEditorToolBar(m_itemActions, this))
    , m_editorPropertyPanel(new MaskEditorPropertyPanel(this))
    , m_editorCanvas(new MaskEditorCanvas(this))
    , m_splitter(new QSplitter(this))
{
    setObjectName(QStringLiteral("IntensityDataPlotWidget"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_splitter->addWidget(m_editorCanvas);
    m_splitter->addWidget(m_editorPropertyPanel);

    addToolBar(m_toolBar);

    setCentralWidget(m_splitter);

    setup_connections();
}

void MaskEditor::setModel(SessionModel *model, const QModelIndex &rootIndex)
{
    QModelIndex intensityItemIndex = rootIndex;
    if(!intensityItemIndex.isValid()) {
        if(ParameterizedItem *intensityItem = model->getTopItem(Constants::IntensityDataType)) {
            intensityItemIndex = model->indexOfItem(intensityItem);
        }
    }
    Q_ASSERT(intensityItemIndex.isValid());

    m_editorPropertyPanel->setModel(model, intensityItemIndex);

    m_editorCanvas->setModel(model, intensityItemIndex);
    m_editorCanvas->setSelectionModel(m_editorPropertyPanel->selectionModel());

    m_itemActions->setModel(model, intensityItemIndex);
    m_itemActions->setSelectionModel(m_editorPropertyPanel->selectionModel());
}

//! shows/hides right panel with properties
void MaskEditor::onPropertyPanelRequest()
{
    m_editorPropertyPanel->setPanelHidden(!m_editorPropertyPanel->isHidden());
}

//! Context menu reimplemented to supress default menu
void MaskEditor::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);
}

void MaskEditor::init_test_model()
{
    SessionModel *maskModel = new SessionModel(SessionXML::MaskModelTag, this);

    SimulationRegistry simRegistry;
    boost::scoped_ptr<GISASSimulation> simulation(simRegistry.createSimulation("BasicGISAS"));

    SampleBuilderFactory sampleFactory;
    boost::scoped_ptr<ISample> sample(sampleFactory.createSample("CylindersAndPrismsBuilder"));

    simulation->setSample(*sample.get());
    simulation->runSimulation();

    IntensityDataItem *item = dynamic_cast<IntensityDataItem *>(maskModel->insertNewItem(Constants::IntensityDataType));
    Q_ASSERT(item);
    item->setOutputData(simulation->getOutputData()->clone());
    qDebug() << item->getXmin() << item->getXmax() << item->getYmin() << item->getYmax();

    // Rectangle

//    RectangleItem *rect = dynamic_cast<RectangleItem *>(m_maskModel->insertNewItem(Constants::RectangleMaskType, m_maskModel->indexOfItem(item)));
//    Q_ASSERT(rect);
//    rect->setRegisteredProperty(RectangleItem::P_POSX, 0.6);
//    rect->setRegisteredProperty(RectangleItem::P_POSY, 1.5);
//    rect->setRegisteredProperty(RectangleItem::P_WIDTH, 0.3);
//    rect->setRegisteredProperty(RectangleItem::P_HEIGHT, 0.2);

    // Polygon
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

    // Lines
//   ParameterizedItem *line = m_maskModel->insertNewItem(Constants::VerticalLineMaskType, m_maskModel->indexOfItem(item));
//   line->setRegisteredProperty(VerticalLineItem::P_POSX, 0.6);

//   ParameterizedItem *line = m_maskModel->insertNewItem(Constants::HorizontalLineMaskType, m_maskModel->indexOfItem(item));
//   line->setRegisteredProperty(HorizontalLineItem::P_POSY, 1.0);

    // Ellipse
//    EllipseItem *rect = dynamic_cast<EllipseItem *>(m_maskModel->insertNewItem(Constants::EllipseMaskType, m_maskModel->indexOfItem(item)));
//    Q_ASSERT(rect);
//    rect->setRegisteredProperty(EllipseItem::P_POSX, 1.0);
//    rect->setRegisteredProperty(EllipseItem::P_POSY, 1.0);
//    rect->setRegisteredProperty(EllipseItem::P_WIDTH, 0.3);
//    rect->setRegisteredProperty(EllipseItem::P_HEIGHT, 0.2);

//    MaskAllItem *rect = dynamic_cast<MaskAllItem *>(m_maskModel->insertNewItem(Constants::MaskAllType, m_maskModel->indexOfItem(item)));

//    setModel(maskModel, maskModel->indexOfItem(item));
    setModel(maskModel);
}

void MaskEditor::setup_connections()
{
    // selection/drawing activity is propagated from ToolBar to graphics scene
    connect(m_toolBar,
            SIGNAL(activityModeChanged(MaskEditorFlags::Activity)),
            m_editorCanvas->getScene(),
            SLOT(onActivityModeChanged(MaskEditorFlags::Activity))
            );

    // mask value is propagated from ToolBar to graphics scene
    connect(m_toolBar,
            SIGNAL(maskValueChanged(MaskEditorFlags::MaskValue)),
            m_editorCanvas->getScene(),
            SLOT(onMaskValueChanged(MaskEditorFlags::MaskValue))
            );

    // tool panel request is propagated from ToolBar to this MaskEditor
    connect(m_toolBar,
            SIGNAL(propertyPanelRequest()),
            this,
            SLOT(onPropertyPanelRequest())
            );

    // show results request is propagated from ToolBar to Canvas
    connect(m_toolBar,
            SIGNAL(presentationTypeRequest(MaskEditorFlags::PresentationType)),
            m_editorCanvas,
            SLOT(onPresentationTypeRequest(MaskEditorFlags::PresentationType))
            );

    // reset view request is propagated from ToolBar to graphics view
    connect(m_toolBar,
            SIGNAL(resetViewRequest()),
            m_editorCanvas->getView(),
            SLOT(onResetViewRequest())
            );

    // space bar push (request for zoom mode) is propagated from graphics view to ToolBar
    connect(m_editorCanvas->getView(),
            SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)),
            m_toolBar,
            SLOT(onChangeActivityRequest(MaskEditorFlags::Activity))
            );

    // context menu request is propagated from graphics scene to MaskEditorActions
    connect(m_editorCanvas->getScene(),
            SIGNAL(itemContextMenuRequest(QPoint)),
            m_itemActions,
            SLOT(onItemContextMenuRequest(QPoint))
            );

    // context menu request is propagated from PropertyPanel to MaskEditorActions
    connect(m_editorPropertyPanel,
            SIGNAL(itemContextMenuRequest(QPoint)),
            m_itemActions,
            SLOT(onItemContextMenuRequest(QPoint))
            );

}
