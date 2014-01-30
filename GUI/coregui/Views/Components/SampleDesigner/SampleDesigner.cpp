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
//    , m_editorStack(0)
{
    m_designerScene = new DesignerScene(parent);
    m_designerView = new DesignerView(parent, m_designerScene);
//    m_editorStack = new QStackedWidget(parent);
//    m_editorStack->addWidget(m_designerView);
}


SampleDesigner::~SampleDesigner()
{
    delete m_widgetFactory;
}


// XXX will be replaced
void SampleDesigner::sceneToISample()
{
    SamplePrintVisitor print_visitor;

    MultiLayerView *view = getScene()->getMultiLayerView();
    std::cout << "SampleDesigner::sceneToISample() -> " << view<< std::endl;

    std::cout << "XXX --------" << std::endl;
    IViewToISample maker;
    ISample *isample = maker.makeISample(view);
    std::cout << "isample " << isample << std::endl;
//    view->accept(&visitor);
    if(isample) {
        std::cout << "___________>>>" << std::endl;
        isample->accept(&print_visitor);
    }
}
