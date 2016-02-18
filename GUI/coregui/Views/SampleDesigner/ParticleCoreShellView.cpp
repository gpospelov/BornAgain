// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ParticleCoreShellView.cpp
//! @brief     Implements class ParticleCoreShellView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCoreShellView.h"
#include "ParameterizedItem.h"
#include <QDebug>


ParticleCoreShellView::ParticleCoreShellView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleCoreShellType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleCoreShellType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR);
    addPort("core", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    addPort("shell", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION);

    m_roundpar = 5;
    m_label_vspace = 45;
}

void ParticleCoreShellView::addView(IView *childView, int /* row */)
{
    int index = childView->getParameterizedItem()
                    ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT)
                    .toInt();
    qDebug() << "ParticleCoreShellView::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
