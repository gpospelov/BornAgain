// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceWidget.cpp
//! @brief     Implements class RealSpaceWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpaceWidget.h"
#include "RealSpaceToolBar.h"
#include "RealSpaceCanvas.h"
#include "RealSpaceActions.h"
#include "RealSpacePanel.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

RealSpaceWidget::RealSpaceWidget(QWidget* parent)
    : QWidget(parent)
    , m_actions(new RealSpaceActions)
    , m_toolBar(new RealSpaceToolBar)
    , m_canvas(new RealSpaceCanvas)
    , m_panel(new RealSpacePanel)
{
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->setContentsMargins(0, 0, 0, 0);
    hlayout->addWidget(m_canvas);
    hlayout->addWidget(m_panel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addLayout(hlayout);

    setLayout(mainLayout);

    connect(m_panel, SIGNAL(selectionChanged(QModelIndex)),
            m_canvas, SLOT(onSelectionChanged(QModelIndex)));
}

void RealSpaceWidget::setModel(SampleModel* model)
{
    m_panel->setModel(model);
    m_canvas->setModel(model);
}
