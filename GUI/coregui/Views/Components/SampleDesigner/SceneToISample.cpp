#include "SceneToISample.h"

#include "ISampleView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleDecorationView.h"
#include <iostream>


void SceneToISample::visit(ISampleView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ISampleView ) " << m_level << " " << view->type() << " " << std::endl;
}


void SceneToISample::visit(ISampleRectView *view)
{
    std::cout << get_indent() << "ViewVisitor(ISampleRectView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
}


void SceneToISample::visit(LayerView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(LayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();
}


void SceneToISample::visit(MultiLayerView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(MultiLayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(QGraphicsItem *item, view->childItems()) {
        ISampleView *layer = dynamic_cast<ISampleView *>(item);
        if(layer) layer->accept(this);
    }
    goBack();
}


void SceneToISample::visit(FormFactorView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(FormFactorFullSphereView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorFullSphereView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(FormFactorPyramidView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPyramidView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(FormFactorPrism3View *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorPrism3View ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(FormFactorCylinderView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(FormFactorCylinderView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(InterferenceFunctionView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunctionView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(InterferenceFunction1DParaCrystalView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(InterferenceFunction1DParaCrystalView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void SceneToISample::visit(ParticleDecorationView *view)
{
    Q_ASSERT(view);
    std::cout << get_indent() << "ViewVisitor(ParticleDecorationView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;

    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();
}


