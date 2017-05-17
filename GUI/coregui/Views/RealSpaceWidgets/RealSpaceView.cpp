// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpaceView.cpp
//! @brief     Implements class RealSpaceView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "RealSpaceView.h"
#include "RealSpaceModel.h"
#include <ba3d/widget.h>
#include <QVBoxLayout>

RealSpaceView::RealSpaceView(QWidget* parent)
    : QWidget(parent)
    , m_3dview(new ba3d::Widget3D)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_3dview);
    setLayout(layout);
}

void RealSpaceView::setModel(RealSpaceModel* model)
{
    m_3dview->setModel(model);
}
