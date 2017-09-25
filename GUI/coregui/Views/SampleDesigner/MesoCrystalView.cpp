// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/MesoCrystalView.cpp
//! @brief     Implements class MesoCrystalView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "MesoCrystalView.h"
#include "MesoCrystalItem.h"
#include "ParticleItem.h"
#include "SessionItem.h"

MesoCrystalView::MesoCrystalView(QGraphicsItem *parent) : ConnectableView(parent)
{
    setName(Constants::MesoCrystalType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleCoreShellType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect to the ParticleLayout"));
    addPort("basis", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect basis particles"));
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip(QStringLiteral("Connect rotation to this port, if necessary"));
    m_roundpar = 5;
    m_label_vspace = 45;
}

void MesoCrystalView::addView(IView *childView, int /* row */)
{
    int index = 0;
    if (this->getItem()->tagFromItem(childView->getItem()) == MesoCrystalItem::T_TRANSFORMATION)
        index = 1;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
