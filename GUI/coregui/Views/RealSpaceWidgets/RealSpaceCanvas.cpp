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
#include "SampleModel.h"
#include "RealSpaceView.h"
#include "RealSpaceBuilder.h"
#include "RealSpaceModel.h"
#include <QVBoxLayout>

#include <FilterPropertyProxy.h>

RealSpaceCanvas::RealSpaceCanvas(QWidget* parent)
    : QWidget(parent)
    , m_sampleModel(nullptr)
    , m_view(new RealSpaceView)
    , m_lockView_on(false)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_view);
    setLayout(layout);

    // listening whether lock view in RealSpaceToolBar has been unchecked or not
    connect(this, &RealSpaceCanvas::lockViewUnchecked,
            this, &RealSpaceCanvas::onSelectionChanged);
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
            if(selectionModel != nullptr)
            {
                QModelIndexList indices = m_selectionModel->selection().indexes();
                if(indices.size())
                    m_currentSelection = FilterPropertyProxy::toSourceIndex(indices.back());
            }

            if(m_lockView_on == false)
                updateScene();
        }
    }
}

void RealSpaceCanvas::onSelectionChanged(const QItemSelection &selected /* selected */,
                                         const QItemSelection & /* deselected */)
{
    if(m_lockView_on == false)
    {
        QModelIndexList indices = selected.indexes();
        QModelIndex selectedIndex;

        if(indices.size())
            selectedIndex = FilterPropertyProxy::toSourceIndex(indices.back());
        else
            selectedIndex = m_currentSelection;


        if (!selectedIndex.isValid()) {
            resetScene();

        } else {
            m_currentSelection = selectedIndex;
            updateScene();
        }
    }
}

void RealSpaceCanvas::onDefaultViewAction()
{
    defaultView();
}

void RealSpaceCanvas::onEdgeViewAction()
{
    edgeView();
}

void RealSpaceCanvas::onFaceViewAction()
{
    faceView();
}

void RealSpaceCanvas::onLockViewAction(bool lockView_on)
{
    // if lock view is unchecked, emit a signal to display the current selection on the canvas
    if(m_lockView_on == true && lockView_on == false)
    {
        m_lockView_on = lockView_on;
        emit lockViewUnchecked(m_selectionModel->selection(), m_selectionModel->selection());
    }

    m_lockView_on = lockView_on;
}

void RealSpaceCanvas::updateScene()
{
    if (!m_currentSelection.isValid())
        return;

    m_realSpaceModel.reset(new RealSpaceModel);

    SessionItem* item = m_sampleModel->itemForIndex(m_currentSelection);

    Q_ASSERT(item);
    RealSpaceBuilder::populate(m_realSpaceModel.get(), *item);

    m_view->setModel(m_realSpaceModel.get());
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

void RealSpaceCanvas::edgeView()
{
    m_view->edgeView();
}

void RealSpaceCanvas::faceView()
{
    m_view->faceView();
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
        connect(model, SIGNAL(rowsInserted(QModelIndex, int, int)),
                this, SLOT(updateScene()), Qt::UniqueConnection);
        connect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)),
                this, SLOT(updateScene()), Qt::UniqueConnection);
        connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)),
                this, SLOT(updateScene()), Qt::UniqueConnection);
        connect(model, SIGNAL(modelReset()), this,
                SLOT(resetScene()), Qt::UniqueConnection);
    } else {
        disconnect(model, SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(updateScene()));
        disconnect(model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(updateScene()));
        disconnect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this,
                   SLOT(updateScene()));
        disconnect(model, SIGNAL(modelReset()), this, SLOT(resetScene()));
    }
}
