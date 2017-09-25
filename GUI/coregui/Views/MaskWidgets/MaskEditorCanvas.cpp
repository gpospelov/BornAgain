// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/MaskEditorCanvas.cpp
//! @brief     Implements class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIHelpers.h"
#include "MaskEditorCanvas.h"
#include "MaskGraphicsProxy.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskResultsPresenter.h"
#include "SessionModel.h"
#include "ColorMapLabel.h"
#include "SavePlotAssistant.h"
#include "AppSvc.h"
#include "projectmanager.h"
#include "ColorMap.h"
#include "IntensityDataItem.h"
#include "RealDataItem.h"
#include "IntensityDataFunctions.h"
#include "MaskItems.h"
#include <QGraphicsRectItem>
#include <QModelIndex>
#include <QVBoxLayout>

namespace {
inline bool getRotateWarningCallback(QWidget* parent) {
    const QString title("Rotate data");

    const QString message("Rotation will break the link between the data and the instrument. "
                          "Detector masks, if exist, will be removed.");

    return GUIHelpers::question(parent, title, message, "Do you wish to roate the data?",
        "Yes, please rotate", "No, cancel data rotation");
}
}


MaskEditorCanvas::MaskEditorCanvas(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene))
    , m_intensityDataItem(0)
    , m_statusLabel(new ColorMapLabel(0, this))
    , m_resultsPresenter(new MaskResultsPresenter(this))
{
    setObjectName(QStringLiteral("MaskEditorCanvas"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_view);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    connect(m_view, SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)),
            this, SIGNAL(changeActivityRequest(MaskEditorFlags::Activity)));
    connect(m_view, SIGNAL(deleteSelectedRequest()),
            this, SIGNAL(deleteSelectedRequest()));
}

void MaskEditorCanvas::setMaskContext(SessionModel *model, const QModelIndex &maskContainerIndex,
                                      IntensityDataItem *intensityItem)
{
    m_intensityDataItem = intensityItem;

    m_scene->setMaskContext(model, maskContainerIndex, intensityItem);
    m_resultsPresenter->setMaskContext(model, maskContainerIndex, intensityItem);
    m_view->updateSize(m_view->size());
    m_statusLabel->addColorMap(m_scene->colorMap());
}

void MaskEditorCanvas::setSelectionModel(QItemSelectionModel *model)
{
    m_scene->setSelectionModel(model);
}

MaskGraphicsScene *MaskEditorCanvas::getScene()
{
    return m_scene;
}

void MaskEditorCanvas::onPresentationTypeRequest(MaskEditorFlags::PresentationType presentationType)
{
    m_resultsPresenter->updatePresenter(presentationType);

    if(auto container = m_intensityDataItem->maskContainerItem()) {
        bool isVisible = presentationType.testFlag(MaskEditorFlags::MASK_EDITOR);
        for(auto mask : container->getItems())
            mask->setItemValue(MaskItem::P_IS_VISIBLE, isVisible);
    }
}

//! Saves plot into project directory.

void MaskEditorCanvas::onSavePlotRequest()
{
    QString dirname = AppSvc::projectManager()->userExportDir();

    SavePlotAssistant saveAssistant;
    saveAssistant.savePlot(dirname, m_scene->colorMap()->customPlot(), m_intensityDataItem);
}

void MaskEditorCanvas::onResetViewRequest()
{
    m_view->onResetViewRequest();

    if(isAxisRangeMatchData()) {
        setZoomToROI();
    } else {
        m_intensityDataItem->resetView();
    }
}


void MaskEditorCanvas::onRotateDataRequest()
{
    Q_ASSERT(m_intensityDataItem);

    auto data_parent = m_intensityDataItem->parent();
    if (data_parent->getItemValue(RealDataItem::P_INSTRUMENT_ID).toBool()) {
        if (!getRotateWarningCallback(this))
            return;
        data_parent->setItemValue(RealDataItem::P_INSTRUMENT_ID, QString());
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    const auto input = m_intensityDataItem->getOutputData();
    m_intensityDataItem->setOutputData(
        IntensityDataFunctions::createRearrangedDataSet(*input, 1).release());
    m_intensityDataItem->setAxesRangeToData();
    QApplication::restoreOverrideCursor();
}

//! Returns true if IntensityData is currently at 100% zoom level

bool MaskEditorCanvas::isAxisRangeMatchData() const
{
    Q_ASSERT(m_intensityDataItem);

    if(m_intensityDataItem->getLowerX() != m_intensityDataItem->getXmin()) return false;
    if(m_intensityDataItem->getUpperX() != m_intensityDataItem->getXmax()) return false;
    if(m_intensityDataItem->getLowerY() != m_intensityDataItem->getYmin()) return false;
    if(m_intensityDataItem->getUpperY() != m_intensityDataItem->getYmax()) return false;
    return true;
}

void MaskEditorCanvas::setZoomToROI()
{
    if(MaskContainerItem *maskContainer = m_intensityDataItem->maskContainerItem()) {
        if(SessionItem *roiItem = maskContainer->getChildOfType(Constants::RegionOfInterestType)) {
            m_intensityDataItem->setLowerX(roiItem->getItemValue(RectangleItem::P_XLOW).toDouble());
            m_intensityDataItem->setUpperX(roiItem->getItemValue(RectangleItem::P_XUP).toDouble());
            m_intensityDataItem->setLowerY(roiItem->getItemValue(RectangleItem::P_YLOW).toDouble());
            m_intensityDataItem->setUpperY(roiItem->getItemValue(RectangleItem::P_YUP).toDouble());
        }
    }
}
