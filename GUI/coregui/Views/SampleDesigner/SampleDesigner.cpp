// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/SampleDesigner/SampleDesigner.cpp
//! @brief     Implements class SampleDesigner
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "MultiLayerView.h"
#include "SampleViewProxyModel.h"
#include "ISample.h"
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


void SampleDesigner::setSelectionModel(QItemSelectionModel *model, SampleViewProxyModel *proxy)
{
    if(model) m_designerScene->setSelectionModel(model, proxy);
}


void SampleDesigner::onSmartAlign()
{
    qDebug() << "SampleDesigner::onSmartAlign()";
    m_designerScene->onSmartAlign();
}
