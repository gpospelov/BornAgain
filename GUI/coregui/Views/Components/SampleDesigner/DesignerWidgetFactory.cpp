#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "ParticleDecorationView.h"
#include "InterferenceFunctionView.h"
#include "MaterialView.h"


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
        "FormFactorFullSphere",
        IFactoryCreateFunction<FormFactorFullSphereView, ISampleView>
    );
   registerItem(
        "FormFactorPyramid",
        IFactoryCreateFunction<FormFactorPyramidView, ISampleView>
    );

   registerItem(
        "ParticleDecoration",
        IFactoryCreateFunction<ParticleDecorationView, ISampleView>
    );

   registerItem(
        "InterferenceFunction1DParaCrystal",
        IFactoryCreateFunction<InterferenceFunction1DParaCrystalView, ISampleView>
    );

   registerItem(
        "HomogeneousMaterial",
        IFactoryCreateFunction<MaterialView, ISampleView>
    );

}


ISampleView *DesignerWidgetFactory::createView(const QString &name)
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


