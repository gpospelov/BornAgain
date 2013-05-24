#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
//#include "FormFactorFullSphereView.h"
//#include "FormFactorPyramidView.h"
#include "ParticleDecorationView.h"
#include "InterferenceFunction1DParaCrystalView.h"


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


