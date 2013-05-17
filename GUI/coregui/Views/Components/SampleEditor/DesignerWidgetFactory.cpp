#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"


DesignerWidgetFactory::DesignerWidgetFactory()
{
   registerItem(
        "Layer",
        IFactoryCreateFunction<LayerView, ISampleView>
    );

   registerItem(
        "MultiLayer",
        IFactoryCreateFunction<MultiLayerView, ISampleView>
    );

   registerItem(
        "FormFactor",
        IFactoryCreateFunction<FormFactorView, ISampleView>
    );

   std::cout << "DesignerWidgetFactory::DesignerWidgetFactory() " << std::endl;
}


ISampleView *DesignerWidgetFactory::create(const QString &name)
{
    ISampleView *result(0);
    try {
        std::cout << "DesignerWidgetFactory::create() XXX 1.1" << std::endl;
        result = createItem(name.toStdString());
        std::cout << "DesignerWidgetFactory::create() XXX 1.2" << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        std::cout << "TestFactory::execute() -> Warning. No test with name '"
                  << name.toStdString() << "' is defined." << std::endl;
    }

    if( !result ) result = new ISampleDefaultView();

    return result;
}


