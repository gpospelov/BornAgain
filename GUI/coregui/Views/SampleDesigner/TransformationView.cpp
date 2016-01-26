// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/TransformationView.cpp
//! @brief     Implements class TransformationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TransformationView.h"
#include "DesignerHelper.h"
#include "item_constants.h"


TransformationView::TransformationView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::TransformationType);
    setColor(DesignerHelper::getDefaultTransformationColor());
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::TRANSFORMATION);
    m_roundpar = 3;
}
