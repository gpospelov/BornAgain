// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleCoreShellView.cpp
//! @brief     Implements class ParticleCoreShellView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "ParticleCoreShellView.h"
#include "ParticleCoreShellItem.h"
#include "SessionItem.h"

ParticleCoreShellView::ParticleCoreShellView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleCoreShellType);
    setColor(DesignerHelper::getDefaultParticleColor());
    setRectangle(DesignerHelper::getDefaultBoundingRect(Constants::ParticleCoreShellType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect to the ParticleLayout"));
    addPort("core", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect particle which will play the role of core."));
    addPort("shell", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect particle which will play the role of shell."));
    addPort("transformation", NodeEditorPort::INPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip(QStringLiteral("Connect particle rotation to this port, if necessary"));

    m_roundpar = 5;
    m_label_vspace = 45;
}

void ParticleCoreShellView::addView(IView *childView, int /* row */)
{
    int index = 0;
    if (this->getItem()->tagFromItem(childView->getItem()) == ParticleCoreShellItem::T_CORE) {
        index = 0;
    } else if (this->getItem()->tagFromItem(childView->getItem()) == ParticleCoreShellItem::T_SHELL) {
        index = 1;
    } else {
        index = 2;
    }
    connectInputPort(dynamic_cast<ConnectableView *>(childView), index);
}
