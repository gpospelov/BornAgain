// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/MaskWidgets/MaskEditorCanvas.cpp
//! @brief     Implements class MaskEditorCanvas
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MaskEditorCanvas.h"
#include "MaskGraphicsScene.h"
#include "MaskGraphicsView.h"
#include "MaskGraphicsProxy.h"
#include "MaskResultsPresenter.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QModelIndex>
#include <QDebug>


MaskEditorCanvas::MaskEditorCanvas(QWidget *parent)
    : QWidget(parent)
    , m_scene(new MaskGraphicsScene(this))
    , m_view(new MaskGraphicsView(m_scene, this))
    , m_resultsPresenter(new MaskResultsPresenter(this))
    , m_stack(new QStackedWidget(this))
{
    setObjectName(QStringLiteral("MaskEditorCanvas"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_stack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stack->addWidget(m_view);
    m_stack->addWidget(m_resultsPresenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_stack);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

}

void MaskEditorCanvas::setModel(SessionModel *model, const QModelIndex &rootIndex)
{
    m_scene->setModel(model, rootIndex);
    m_resultsPresenter->setModel(model, rootIndex);
}

void MaskEditorCanvas::setSelectionModel(QItemSelectionModel *model)
{
    m_scene->setSelectionModel(model);
}

MaskGraphicsScene *MaskEditorCanvas::getScene()
{
    return m_scene;
}

MaskGraphicsView *MaskEditorCanvas::getView()
{
    return m_view;
}

void MaskEditorCanvas::onShowResultsRequest()
{
    qDebug() << "MaskEditorCanvas::onShowResultsRequest()";
    m_stack->setCurrentIndex(!m_stack->currentIndex());
    if(m_stack->currentIndex() == MaskEditorFlags::MASK_PRESENTER) {
        m_resultsPresenter->updatePresenter();
    }
}
