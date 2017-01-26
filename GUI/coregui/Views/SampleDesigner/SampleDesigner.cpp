// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleDesigner.cpp
//! @brief     Implements class SampleDesigner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "FilterPropertyProxy.h"
#include "ISample.h"
#include "MultiLayerView.h"
#include <QDebug>

SampleDesigner::SampleDesigner(QWidget *parent)
    : SampleDesignerInterface(parent)
    , m_designerScene(0)
    , m_designerView(0)
{
    m_designerScene = new DesignerScene(parent);
    m_designerView = new DesignerView(m_designerScene, parent);
}


SampleDesigner::~SampleDesigner()
{
}


void SampleDesigner::setSampleModel(SampleModel *sampleModel)
{
    if(sampleModel) m_designerScene->setSampleModel(sampleModel);
}

void SampleDesigner::setInstrumentModel(InstrumentModel *instrumentModel)
{
    if(instrumentModel) m_designerScene->setInstrumentModel(instrumentModel);
}


void SampleDesigner::setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy)
{
    if(model) m_designerScene->setSelectionModel(model, proxy);
}


void SampleDesigner::onSmartAlign()
{
    m_designerScene->onSmartAlign();
}
