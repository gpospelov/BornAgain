// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/ParticleCollectionView.cpp
//! @brief     Implements class ParticleCollectionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleCollectionView.h"
#include "ParameterizedItem.h"
#include <QDebug>


ParticleCollectionView::ParticleCollectionView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleCollectionType);
    setLabel("Particle\ncollection");
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleCoreShellType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR);
    addPort("particles", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR);
    m_roundpar = 5;
    m_label_vspace = 45;
}


void ParticleCollectionView::addView(IView *childView, int /* row */)
{
    int index = childView->getParameterizedItem()->getRegisteredProperty(ParameterizedItem::P_PORT).toInt();
    qDebug() << "ParticleCollectionView::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);

}
