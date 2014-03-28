#include "SampleDesigner.h"
#include "DesignerScene.h"
#include "DesignerView.h"
#include "DesignerWidgetFactory.h"
#include "IViewToISample.h"
#include "MultiLayerView.h"
#include "ISample.h"

#include "SamplePrintVisitor.h"

SampleDesigner::SampleDesigner(QWidget *parent)
    : SampleDesignerInterface(parent)
    , m_widgetFactory(new DesignerWidgetFactory())
    , m_designerScene(0)
    , m_designerView(0)
{
    m_designerScene = new DesignerScene2(parent);
    m_designerView = new DesignerView(parent, m_designerScene);
}


SampleDesigner::~SampleDesigner()
{
    delete m_widgetFactory;
}


void SampleDesigner::setModel(SessionModel *model)
{
    if(model) m_designerScene->setModel(model);
}


void SampleDesigner::setSelectionModel(QItemSelectionModel *model)
{
    if(model) m_designerScene->setSelectionModel(model);
}



void SampleDesigner::sceneToISample()
{
//    SamplePrintVisitor print_visitor;

//    MultiLayerView *view = getScene()->getMultiLayerView();
//    std::cout << "SampleDesigner::sceneToISample() -> " << view<< std::endl;

//    std::cout << "XXX --------" << std::endl;
//    IViewToISample maker;
//    ISample *isample = maker.makeISample(view);
//    std::cout << "isample " << isample << std::endl;
////    view->accept(&visitor);
//    if(isample) {
//        std::cout << "___________>>>" << std::endl;
//        isample->accept(&print_visitor);
//    }
}
