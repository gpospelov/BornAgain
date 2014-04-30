#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "MultiLayerView.h"
#include "ISample.h"

#include "SamplePrintVisitor.h"

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


void SampleDesigner::setSessionModel(SessionModel *model)
{
    if(model) m_designerScene->setSessionModel(model);
}


void SampleDesigner::setSelectionModel(QItemSelectionModel *model)
{
    if(model) m_designerScene->setSelectionModel(model);
}

