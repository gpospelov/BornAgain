#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "MultiLayerView.h"
#include "ISample.h"
#include <QDebug>

SampleDesigner::SampleDesigner(QWidget *parent)
    : SampleDesignerInterface(parent)
    , m_designerScene(0)
    , m_designerView(0)
{
    m_designerScene = new DesignerScene(parent);
    m_designerView = new DesignerView(parent, m_designerScene);
}


SampleDesigner::~SampleDesigner()
{
}


void SampleDesigner::setSampleModel(SessionModel *sampleModel)
{
    if(sampleModel) m_designerScene->setSampleModel(sampleModel);
}

void SampleDesigner::setInstrumentModel(SessionModel *instrumentModel)
{
    if(instrumentModel) m_designerScene->setInstrumentModel(instrumentModel);
}


void SampleDesigner::setSelectionModel(QItemSelectionModel *model)
{
    if(model) m_designerScene->setSelectionModel(model);
}


void SampleDesigner::onSmartAlign()
{
    m_designerScene->onSmartAlign();
}
