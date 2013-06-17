#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "ParticleDecorationView.h"
#include "InterferenceFunctionView.h"
#include "MaterialView.h"


DesignerWidgetFactory *DesignerWidgetFactory::m_instance = 0;


DesignerWidgetFactory::DesignerWidgetFactory()
{
    Q_ASSERT(!m_instance);
    m_instance = this;

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


DesignerWidgetFactory::~DesignerWidgetFactory()
{
    m_instance = 0;
}


DesignerWidgetFactory *DesignerWidgetFactory::instance()
{
    return m_instance;
}


ISampleView *DesignerWidgetFactory::createView(const QString &name)
{
    Q_ASSERT(instance());
    return instance()->this_createView(name);
}


ISampleView *DesignerWidgetFactory::this_createView(const QString &name)
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


