#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "ParticleDecorationView.h"


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

   registerItem(
        "ParticleDecoration",
        IFactoryCreateFunction<ParticleDecorationView, ISampleView>
    );

}


ISampleView *DesignerWidgetFactory::create(const QString &name)
{
    ISampleView *result(0);
    try {
        result = createItem(name.toStdString());
    } catch (std::runtime_error& e) {
        std::cout << "DesignerWidgetFactory::create() -> Warning. No widget with name '"
                  << name.toStdString() << "' is defined." << std::endl;
    }

    if( !result ) result = new ISampleDefaultView();

    return result;
}


