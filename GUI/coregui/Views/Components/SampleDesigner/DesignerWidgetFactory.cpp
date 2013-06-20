#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "ParticleDecorationView.h"
#include "InterferenceFunctionView.h"
#include "MaterialView.h"
#include "SampleBuilderFactory.h"
#include "ISampleToScene.h"


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
        "FormFactorCylinder",
        IFactoryCreateFunction<FormFactorCylinderView, ISampleView>
    );
   registerItem(
        "FormFactorPrism3",
        IFactoryCreateFunction<FormFactorPrism3View, ISampleView>
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


QList<QGraphicsItem *> DesignerWidgetFactory::createViews(const QString &name)
{
    Q_ASSERT(instance());
    return instance()->this_createViews(name);
}


// TODO Here we use factory from inside another factory. Isn't that full of beauty?
QList<QGraphicsItem *> DesignerWidgetFactory::this_createViews(const QString &name)
{
    QList<QGraphicsItem *> result;

    // try create single view from given item name
    try {
        result.append(createItem(name.toStdString()));
    } catch (std::runtime_error& e) { }

    // try to create the whole sample from item name
    if(result.empty()) {
        SampleBuilderFactory factory;
        ISample *sample(0);
        try {
            sample = factory.createSample(name.toStdString());
        } catch (std::runtime_error& e) {}
        if(sample) {
            ISampleToScene visitor;
            sample->accept(&visitor);
            result = visitor.getItems();
        }
    }

    if( result.empty() ) {
        std::cout << "DesignerWidgetFactory::create() -> Warning. No widget with name '"
                  << name.toStdString() << "' is defined." << std::endl;
        result.append(new ISampleDefaultView());
    }

    return result;
}


