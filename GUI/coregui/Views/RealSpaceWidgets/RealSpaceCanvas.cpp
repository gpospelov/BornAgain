// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceScene.cpp
//! @brief     Implements class RealSpaceScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RealSpaceCanvas.h"
#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include "RealSpaceView.h"
#include "SampleModel.h"
#include "SessionGraphicsItem.h"
#include "WarningSign.h"
#include <FilterPropertyProxy.h>
#include <QApplication>
#include <QVBoxLayout>

RealSpaceCanvas::RealSpaceCanvas(QWidget* parent)
    : QWidget(parent), m_sampleModel(nullptr), m_view(new RealSpaceView), m_view_locked(false),
      m_sceneGeometry(new SceneGeometry), m_warningSign(new WarningSign(this))
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_view);
    setLayout(layout);

    // listening whether Lock View box in RealSpaceToolBar has been unchecked or not
    // in order to display the current selection as soon as the box is unchecked
    connect(this, &RealSpaceCanvas::lockViewUnchecked, this, &RealSpaceCanvas::updateToSelection);
}

RealSpaceCanvas::~RealSpaceCanvas()
{
}

void RealSpaceCanvas::setModel(SampleModel* sampleModel, QItemSelectionModel* selectionModel)
{
    if (sampleModel != m_sampleModel) {

        if (m_sampleModel)
            setConnected(m_sampleModel, false);

        m_sampleModel = sampleModel;

        m_selectionModel = selectionModel;

        if (m_sampleModel && !isHidden()) {
            setConnected(m_sampleModel, true);
            if (selectionModel != nullptr) {
                QModelIndexList indices = m_selectionModel->selection().indexes();
                if (indices.size())
                    m_currentSelection = FilterPropertyProxy::toSourceIndex(indices.back());
            }

            if (!m_view_locked)
                updateScene();
        }
    }
}

void RealSpaceCanvas::onSelectionChanged(const QItemSelection& selection /* selection */,
                                         const QItemSelection& /* deselection */)
{
    // propagate selection from selectionChanged() signal to updateToSelection() method
    updateToSelection(selection);
}

void RealSpaceCanvas::updateToSelection(const QItemSelection& selection)
{
    if (!m_view_locked) {
        QModelIndexList indices = selection.indexes();

        if (indices.size())
            m_currentSelection = FilterPropertyProxy::toSourceIndex(indices.back());
        else
            m_currentSelection = QModelIndex();
        // if no object is selected then display nothing on canvas

        updateScene();
    }
}

void RealSpaceCanvas::onDefaultViewAction()
{
    defaultView();
}

void RealSpaceCanvas::onSideViewAction()
{
    sideView();
}

void RealSpaceCanvas::onTopViewAction()
{
    topView();
}

void RealSpaceCanvas::onLockViewAction(bool view_locked)
{
    // if Lock View box is unchecked i.e. previously it was checked (true) and now it's
    // unchecked (false), then emit a signal to display the current selection on the canvas
    if (m_view_locked && !view_locked) {
        m_view_locked = view_locked;
        emit lockViewUnchecked(m_selectionModel->selection());
    } else
        m_view_locked = view_locked;
}

void RealSpaceCanvas::onChangeLayerSizeAction(double layerSizeChangeScale)
{
    // when no object is selected --> take no action
    if (m_currentSelection == QModelIndex())
        return;

    m_sceneGeometry->set_layer_size(m_sceneGeometry->layer_size() * layerSizeChangeScale);
    updateScene();
}

void RealSpaceCanvas::onDataChanged(const QModelIndex& index)
{
    auto item = m_sampleModel->itemForIndex(index);
    if (!item)
        return;

    if (!(item->modelType() == Constants::PropertyType
          && (item->displayName() == SessionGraphicsItem::P_XPOS
              || item->displayName() == SessionGraphicsItem::P_YPOS)))
        updateScene();
}

void RealSpaceCanvas::updateScene()
{
    // TODO: Fix m_currentSelection when model is about to die
//    if (!m_currentSelection.isValid())
//        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    m_realSpaceModel.reset(new RealSpaceModel);

    SessionItem* item = m_sampleModel->itemForIndex(m_currentSelection);

    Q_ASSERT(item);

    RealSpaceBuilder builder3D;

    try {
        m_warningSign->clear();
        // if the view is locked, keep the current orientation of the camera
        if (m_view_locked)
            builder3D.populate(m_realSpaceModel.get(), *item, *m_sceneGeometry,
                               m_view->getCamera().getPos());
        // otherwise use default orientation of camera
        else {
            builder3D.populate(m_realSpaceModel.get(), *item, *m_sceneGeometry);
            defaultView(); // Enforces default view and also sets the zoomLevel to default i.e. 0
        }
    } catch (const std::exception& ex) {
        m_warningSign->setWarningMessage(ex.what());
    } catch (...) {
        // ignore other exceptions thrown
    }
    m_view->setModel(m_realSpaceModel.get());

    QApplication::restoreOverrideCursor();
}

void RealSpaceCanvas::resetScene()
{
    m_realSpaceModel.reset();
    m_view->setModel(nullptr);
    m_currentSelection = QModelIndex();
}

void RealSpaceCanvas::defaultView()
{
    m_view->defaultView();
}

void RealSpaceCanvas::sideView()
{
    m_view->sideView();
}

void RealSpaceCanvas::topView()
{
    m_view->topView();
}

void RealSpaceCanvas::showEvent(QShowEvent*)
{
    setConnected(m_sampleModel, true);
    updateScene();
}

void RealSpaceCanvas::hideEvent(QHideEvent*)
{
    setConnected(m_sampleModel, false);
}

void RealSpaceCanvas::setConnected(SampleModel* model, bool makeConnected)
{
    if (!model)
        return;

    if (makeConnected) {
        connect(model, &SampleModel::rowsInserted, this, &RealSpaceCanvas::updateScene,
                Qt::UniqueConnection);
        connect(model, &SampleModel::rowsRemoved, this, &RealSpaceCanvas::updateScene,
                Qt::UniqueConnection);
        connect(model, &SampleModel::dataChanged, this, &RealSpaceCanvas::onDataChanged,
                Qt::UniqueConnection);
        connect(model, &SampleModel::modelReset, this, &RealSpaceCanvas::resetScene,
                Qt::UniqueConnection);
        connect(model, &SampleModel::modelAboutToBeReset, this, [&](){ m_currentSelection = QModelIndex();},
                Qt::UniqueConnection);

    } else {
        disconnect(model, &SampleModel::rowsInserted, this, &RealSpaceCanvas::updateScene);
        disconnect(model, &SampleModel::rowsRemoved, this, &RealSpaceCanvas::updateScene);
        disconnect(model, &SampleModel::dataChanged, this, &RealSpaceCanvas::onDataChanged);
        disconnect(model, &SampleModel::modelReset, this, &RealSpaceCanvas::resetScene);
    }
}
