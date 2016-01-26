// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/InterferenceFunctionViews.cpp
//! @brief     Implements classes InterferenceFunctionViews
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "InterferenceFunctionViews.h"
#include "DesignerHelper.h"
#include "item_constants.h"


InterferenceFunctionRadialParaCrystalView::InterferenceFunctionRadialParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunctionRadialParaCrystalType);
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction2DParaCrystalView::InterferenceFunction2DParaCrystalView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction2DParaCrystalType);
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction1DLatticeView::InterferenceFunction1DLatticeView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction1DLatticeType);
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction2DLatticeView::InterferenceFunction2DLatticeView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::InterferenceFunction2DLatticeType);
    setColor(QColor(255, 236, 139));
    setRectangle( DesignerHelper::getDefaultBoundingRect(getName()) );
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}
