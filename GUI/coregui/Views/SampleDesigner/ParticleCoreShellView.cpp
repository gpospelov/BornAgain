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
#include "SessionItem.h"
#include "ParticleCoreShellItem.h"
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
    // TODO restore logic
//    int index = 0;//int(childView->getParameterizedItem()->port());
//                    ->getRegisteredProperty(ParameterizedItem::OBSOLETE_P_PORT)
//                    .toInt();
    int index = 0;
    if (this->getParameterizedItem()->tagFromItem(childView->getParameterizedItem()) == ParticleCoreShellItem::T_CORE) {
        index = 0;
    } else if (this->getParameterizedItem()->tagFromItem(childView->getParameterizedItem()) == ParticleCoreShellItem::T_SHELL) {
        index = 1;
    } else {
        index = 2;
    }
    qDebug() << "ParticleCoreShellView::addView()" << index;
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
