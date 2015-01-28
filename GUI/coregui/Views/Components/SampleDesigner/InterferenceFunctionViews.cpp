// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/Components/SampleDesigner/InterferenceFunctionViews.cpp
//! @brief     Implements classes InterferenceFunctionViews
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunctionViews.h"
#include "DesignerHelper.h"
#include "item_constants.h"


InterferenceFunctionRadialParaCrystalView::InterferenceFunctionRadialParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunctionRadialParaCrystalType);
    setLabel("Interference \nRadial paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}


InterferenceFunction2DParaCrystalView::InterferenceFunction2DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction2DParaCrystalType);
    setLabel("Interference \n2D paracrystal");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}


InterferenceFunction2DLatticeView::InterferenceFunction2DLatticeView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction2DLatticeType);
    setLabel("Interference \n2D lattice");
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}
