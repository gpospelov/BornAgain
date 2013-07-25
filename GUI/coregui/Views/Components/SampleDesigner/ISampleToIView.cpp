#include "LayerView.h"
#include "MultiLayerView.h"
#include "ISampleToIView.h"
#include "ISample.h"
#include "MultiLayer.h"
#include "LayerDecorator.h"
#include "ParticleDecoration.h"
#include "ParticleDecorationView.h"
#include "FormFactorView.h"
#include "Particle.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionView.h"
#include <iostream>


//! return created views and they connections to the scene
//! only items which do not have parent will be returned (MultiLayers, FormFactor's, Decorations, NodeEditorConnections)
QList<QGraphicsItem *> ISampleToIView::getItems()
{
    QSet<QGraphicsItem *> parentViews;
    for(QMap<const ISample *, ConnectableView *>::iterator it = m_sample_to_view.begin();
        it!= m_sample_to_view.end(); ++it) {
        Q_ASSERT(it.key());
        if( it.value() && !it.value()->parentItem() ) {
            parentViews.insert(it.value());
        }
    }

    QList<QGraphicsItem *> result = parentViews.toList() + m_connections;
    return result;
}



//! creates ISampleView
void ISampleToIView::visit(const ISample *sample)
{
    Q_ASSERT(sample);
    std::cout << get_indent() << "ISampleToIView_ISample " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;
}


//! creates view of MultiLayer, goes deeper to access LayerViews and then adds
//! it to MultiLayerView
void ISampleToIView::visit(const MultiLayer *sample)
{
    Q_ASSERT(sample);
    std::cout << get_indent() << "ISampleToIView_MultiLayer " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    m_multiLayer = MultiLayerView::createTopMultiLayer();

    goForward();
    for(size_t i_layer=0; i_layer < sample->getNumberOfLayers(); ++i_layer) {
        const Layer *layer = sample->getLayer(i_layer);
        layer->accept(this);
        if(i_layer < sample->getNumberOfInterfaces()) {
            const LayerInterface *interface = sample->getLayerInterface(i_layer);
            interface->accept(this);
        }
    }
    goBack();

    m_sample_to_view[sample] = m_multiLayer;

}


//! creates view of Layer, adds them to the MultiLayerView
void ISampleToIView::visit(const Layer *sample)
{
    Q_ASSERT(sample);
    std::cout << get_indent() << "ISampleToIView_Layer " << sample->getName()
              << " " << sample
              << " " << sample->getMaterial()->getName()
              << " " << sample->getRefractiveIndex()
              << " " << (*sample->getParameterPool())
              << std::endl;

    LayerView *layerView = new LayerView();
    layerView->setThickness(sample->getThickness());
    layerView->setName(sample->getName().c_str());
    m_multiLayer->addBottomLayer(layerView);
    m_sample_to_view[sample] = layerView;
}


//! should create view of LayerDecorator, but since LayerDecorator doesn't have
//! own graphical representation, the method goes deeper in ISample hierarchy, and
//! on the way back connects layer and it's decoration
void ISampleToIView::visit(const LayerDecorator *sample)
{
    Q_ASSERT(sample);
    std::cout << get_indent() << "ISampleToIView_LayerDecorator " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    const Layer *layer = sample->getDecoratedLayer();
    layer->accept(this);

    const IDecoration *decoration = sample->getDecoration();
    decoration->accept(this);

    goBack();

    Q_ASSERT(m_sample_to_view[layer]);
    Q_ASSERT(m_sample_to_view[decoration]);
    m_connections += m_sample_to_view[layer]->connectInputPort(m_sample_to_view[decoration]);
}


//! creates view of LayerInterface
void ISampleToIView::visit(const LayerInterface *sample)
{
    Q_ASSERT(sample);
    std::cout << get_indent() << "ISampleToIView_LayerInterface " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;
}


//! creates view of ParticleDecoration and connect it with form factors and
//! interference functions views
void ISampleToIView::visit(const ParticleDecoration *sample)
{
    Q_ASSERT(sample);
    std::cout << get_indent() << "ISampleToIView_ParticleDecoration " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    ParticleDecorationView *decorationView = new ParticleDecorationView();
    m_sample_to_view[sample] = decorationView;

    goForward();
    for(size_t i_info=0; i_info < sample->getNumberOfParticles(); ++i_info) {
        const ParticleInfo *info = sample->getParticleInfo(i_info);
        info->accept(this);
        Q_ASSERT(m_sample_to_view[info]);
        m_connections += decorationView->connectInputPort(m_sample_to_view[info]);
    }

    for(size_t i_func=0; i_func < sample->getNumberOfInterferenceFunctions(); ++i_func) {
        const IInterferenceFunction *func = sample->getInterferenceFunction(i_func);
        func->accept(this);
        // InterferenceFunctionNone doesn't have view, so m_object_to_view[func] can be 0
        if(m_sample_to_view[func]) m_connections += decorationView->connectInputPort(m_sample_to_view[func]);
    }
    goBack();
}


//! Should create ParticleInfo view, but since ParticleInfo doesn't have own graphical
//! representation, method just goes deeper in ISample hierarchy
void ISampleToIView::visit(const ParticleInfo *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_ParticleInfo " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    goForward();

    sample->getParticle()->accept(this);

    goBack();

    // ParticleInfo doesn't have own view and will be represented by the Particle view
    m_sample_to_view[sample] = m_sample_to_view[sample->getParticle()];
}


//! Should create Particle view, but since Particle doesn't have own graphical
//! representation, method just goes deeper in ISample hierarchy
void ISampleToIView::visit(const Particle *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_Particle " << sample->getName()
              << " " << sample
              << " Index:" << sample->getRefractiveIndex()
              << std::endl;

    goForward();

    sample->getSimpleFormFactor()->accept(this);

    goBack();

    // Particle doesn't have own view and will be represented by the form factor view
    m_sample_to_view[sample] = m_sample_to_view[sample->getSimpleFormFactor()];
}


void ISampleToIView::visit(const IFormFactor *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_IFormFactor " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

}


//! creates view of FormFactorFullSphere
void ISampleToIView::visit(const FormFactorFullSphere *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_FormFactorFullSphere " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorFullSphereView *view = new FormFactorFullSphereView();
    view->setFormFactor(sample->clone());
    m_sample_to_view[sample] = view;
}


//! creates view of FormFactorCylinder
void ISampleToIView::visit(const FormFactorCylinder *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_FormFactorCylinder " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorCylinderView *view = new FormFactorCylinderView();
    view->setFormFactor(sample->clone());
    m_sample_to_view[sample] = view;
}


//! creates view of FormFactorPyramid
void ISampleToIView::visit(const FormFactorPyramid *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_FormFactorPyramid " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorPyramidView *view = new FormFactorPyramidView();
    view->setFormFactor(sample->clone());
    m_sample_to_view[sample] = view;
}


//! creates view of FormFactorPrism3
void ISampleToIView::visit(const FormFactorPrism3 *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_FormFactorPrism3 " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    FormFactorPrism3View *view = new FormFactorPrism3View();
    view->setFormFactor(sample->clone());
    m_sample_to_view[sample] = view;
}


//! creates view of IInterferenceFunction
void ISampleToIView::visit(const IInterferenceFunction *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_IInterferenceFunction " << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;
}


//! creates view of InterferenceFunction1DParaCrystal
void ISampleToIView::visit(const InterferenceFunction1DParaCrystal *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_InterferenceFunction1DParaCrystal" << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;

    InterferenceFunction1DParaCrystalView *view = new InterferenceFunction1DParaCrystalView();
    m_sample_to_view[sample] = view;
}


//! creates view of InterferenceFunction2DParaCrystal
void ISampleToIView::visit(const InterferenceFunction2DParaCrystal *sample)
{
    Q_ASSERT(sample);

    std::cout << get_indent() << "ISampleToIView_InterferenceFunction2DParaCrystal" << sample->getName()
              << " " << sample
              << " " << (*sample->getParameterPool())
              << std::endl;
}

