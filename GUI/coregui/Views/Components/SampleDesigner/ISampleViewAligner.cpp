#include "ISampleViewAligner.h"
#include "ConnectableView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleDecorationView.h"
#include <iostream>


//! makes alignment of MultiLayer wil all nodes connected
//!
//! we run over all items to know which item is located at which level
//! here level 0 - is MultiLayer, level 1 - Layers, level 2 - decorations,
//! level 3 - formfactors and interference etc...
void ISampleViewAligner::makeAlign(MultiLayerView *multi_layer)
{
    // run over all items to know which item is located at which level
    multi_layer->accept(this);

    QPointF start(multi_layer->pos().x(), multi_layer->pos().y());
    for(int i_level = 2; i_level <= getMaximumLevelNumber(); ++i_level) {
        QList<IView *> items = m_views.values(i_level);
        start = placeItems(items, start);
    }
}


int ISampleViewAligner::getMaximumLevelNumber()
{
    QList<int> keys = m_views.keys();
    qSort(keys.begin(), keys.end(), qGreater<int>());
    return keys[0];
}


//! place given items using given reference point
QPointF ISampleViewAligner::placeItems(const QList<IView *> &items, QPointF reference)
{
    const double size_factor = 1.5;
    qreal dy = size_factor*getTotalVerticalSpace(items);
    qreal dx = size_factor*getMaximumHorizontalSpace(items);
    reference.setX(reference.x() - dx );
    for(int i=0; i<items.size(); ++i) {
        QPointF pos = reference;
        pos.setY(pos.y() - i*dy/items.size());
        items.at(i)->setPos(pos);
    }
    return reference;
}


qreal ISampleViewAligner::getTotalVerticalSpace(const QList<IView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        result += items.at(i)->boundingRect().height();
    }
    return result;
}


qreal ISampleViewAligner::getMaximumHorizontalSpace(const QList<IView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        qreal width = items.at(i)->boundingRect().width();
        if(width > result) result = width;
    }
    return result;
}


void ISampleViewAligner::visit(IView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(ISampleView ) " << m_level << " " << view->type() << " " << std::endl;
}


void ISampleViewAligner::visit(ConnectableView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(ISampleRectView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
}


void ISampleViewAligner::visit(LayerView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(LayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ConnectableView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();
}


void ISampleViewAligner::visit(MultiLayerView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(MultiLayerView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(QGraphicsItem *item, view->childItems()) {
        IView *layer = dynamic_cast<IView *>(item);
        if(layer) layer->accept(this);
    }
    goBack();
}


void ISampleViewAligner::visit(FormFactorView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(FormFactorView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorFullSphereView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(FormFactorFullSphereView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorPyramidView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(FormFactorPyramidView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorPrism3View *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(FormFactorPrism3View ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(FormFactorCylinderView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(FormFactorCylinderView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(InterferenceFunctionView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(InterferenceFunctionView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(InterferenceFunction1DParaCrystalView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(InterferenceFunction1DParaCrystalView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewAligner::visit(ParticleDecorationView *view)
{
    Q_ASSERT(view);
    //std::cout << get_indent() << "ViewAligner(ParticleDecorationView ) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;

    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ConnectableView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();
}

