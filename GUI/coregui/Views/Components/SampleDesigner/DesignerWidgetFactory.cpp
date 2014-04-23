#include "DesignerWidgetFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "ParticleLayoutView.h"
#include "InterferenceFunctionView.h"
#include "SampleBuilderFactory.h"
#include "ISampleToIView.h"


DesignerWidgetFactory *DesignerWidgetFactory::m_instance = 0;


DesignerWidgetFactory::DesignerWidgetFactory()
{
    Q_ASSERT(!m_instance);
    m_instance = this;

   registerItem(
        "Layer",
        IFactoryCreateFunction<LayerView, IView>
    );

   registerItem(
        "MultiLayer",
        IFactoryCreateFunction<MultiLayerView, IView>
    );

//   registerItem(
//        "FormFactorFullSphere",
//        IFactoryCreateFunction<FormFactorFullSphereView, IView>
//    );
//   registerItem(
//        "FormFactorPyramid",
//        IFactoryCreateFunction<FormFactorPyramidView, IView>
//    );
//   registerItem(
//        "FormFactorCylinder",
//        IFactoryCreateFunction<FormFactorCylinderView, IView>
//    );
//   registerItem(
//        "FormFactorPrism3",
//        IFactoryCreateFunction<FormFactorPrism3View, IView>
//    );

//   registerItem(
//        "ParticleLayout",
//        IFactoryCreateFunction<ParticleLayoutView, IView>
//    );

//   registerItem(
//        "InterferenceFunction1DParaCrystal",
//        IFactoryCreateFunction<InterferenceFunction1DParaCrystalView, IView>
//    );

//   registerItem(
//        "HomogeneousMaterial",
//        IFactoryCreateFunction<MaterialView, IView>
//    );

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

IView * DesignerWidgetFactory::createView(const QString &name)
{
    Q_ASSERT(instance());
    return instance()->this_createView(name);
}


QList<QGraphicsItem *> DesignerWidgetFactory::this_createViews(const QString &name)
{
    QList<QGraphicsItem *> result;

    // try create single view from given item name
    try {
        result.append(createItem(name.toStdString()));
    } catch (std::runtime_error& e) { }
    return result;
}


IView *DesignerWidgetFactory::this_createView(const QString &name)
{
    try {
        return createItem(name.toStdString());
    } catch (std::runtime_error& e) { }
    return 0;
}



