#include "ISampleViewLayoutVisitor.h"
#include "ISampleView.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "FormFactorView.h"
#include "InterferenceFunctionView.h"
#include "ParticleDecorationView.h"
#include <iostream>

ISampleViewLayoutVisitor::ISampleViewLayoutVisitor() : m_level(0)
{

}


void ISampleViewLayoutVisitor::makeLayout(MultiLayerView *multi_layer)
{
    multi_layer->accept(this);

//    for(int i=0; i<m_views.size(); ++i) {
//        std::cout << i << " " << m_views.at(i) << std::endl;
//    }
    for(QMap<int, ISampleView * >::iterator it = m_views.begin(); it!= m_views.end(); ++it) {
        std::cout << "XXX " << it.value() << " " << it.key() << std::endl;
    }

    QList<int> keys = m_views.keys();
    qSort(keys.begin(), keys.end(), qGreater<int>());
    int max_level = keys[0];
    std::cout << "Maximum level " << keys[0];

    for(int i=0; i<keys.size(); ++i) {
        std::cout << "XXXXXX " << i << std::endl;
    }

    QPointF start(multi_layer->pos().x(), multi_layer->pos().y());
    for(int i_level = 2; i_level <= max_level; ++i_level) {
        QList<ISampleView *> items = m_views.values(i_level);
        std::cout << "QQQ " << i_level << " " << items.size() << " " << getTotalVerticalSpace(items) << std::endl;
        start = placeItems(items, start);


    }
}


QPointF ISampleViewLayoutVisitor::placeItems(const QList<ISampleView *> &items, QPointF start)
{
    qreal dy = 1.2*getTotalVerticalSpace(items);
    qreal dx = 1.2*getMaximumHorizontalSpace(items);
    start.setX(start.x() - dx );
    for(int i=0; i<items.size(); ++i) {
        std::cout << "PPP dx: " << dx << "x() " << start.x() << " y() " << start.y() << std::endl;
        QPointF pos = start;
        pos.setY(pos.y() - i*dy/items.size());
        items.at(i)->setPos(pos);
    }
    return start;
}


qreal ISampleViewLayoutVisitor::getTotalVerticalSpace(const QList<ISampleView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        result += items.at(i)->boundingRect().height();
    }
    return result;
}

qreal ISampleViewLayoutVisitor::getMaximumHorizontalSpace(const QList<ISampleView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        qreal width = items.at(i)->boundingRect().width();
        if(width > result) result = width;
    }
    return result;
}



bool ISampleViewLayoutVisitor::goForward()
{
    ++m_level;
    return true;
}


bool ISampleViewLayoutVisitor::goBack()
{
    --m_level;
    return true;
}


std::string ISampleViewLayoutVisitor::get_indent()
{
    std::string result;
    result.resize(m_level*4, '.');
    return result;
}


//void ISampleViewLayoutVisitor::addView(int level, ISampleView *view)
//{
//    if(map.contains)
//}


void ISampleViewLayoutVisitor::visit(ISampleView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(ISampleView) " << m_level << " " << view->type() << " " << std::endl;
}

void ISampleViewLayoutVisitor::visit(ISampleRectView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(ISampleRectView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
}

void ISampleViewLayoutVisitor::visit(LayerView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(LayerView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
        std::cout << "Layer children xxx " << item->type() << std::endl;
        item->accept(this);
    }
    goBack();

}

void ISampleViewLayoutVisitor::visit(MultiLayerView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(MultiLayerView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);

    goForward();
    foreach(QGraphicsItem *item, view->childItems()) {
        ISampleView *layer = dynamic_cast<ISampleView *>(item);
//        LayerView *layer = dynamic_cast<LayerView *>(item);
        if(layer) {
            layer->accept(this);
        }
    }
    goBack();
}

void ISampleViewLayoutVisitor::visit(FormFactorView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(FormFactorView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}

void ISampleViewLayoutVisitor::visit(FormFactorFullSphereView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(FormFactorFullSphereView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}

void ISampleViewLayoutVisitor::visit(FormFactorPyramidView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(FormFactorPyramidView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}

void ISampleViewLayoutVisitor::visit(FormFactorPrism3View *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(FormFactorPrism3View) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}

void ISampleViewLayoutVisitor::visit(FormFactorCylinderView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(FormFactorCylinderView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}


void ISampleViewLayoutVisitor::visit(InterferenceFunctionView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(InterferenceFunctionView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}

void ISampleViewLayoutVisitor::visit(InterferenceFunction1DParaCrystalView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(InterferenceFunction1DParaCrystalView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;
    m_views.insertMulti(m_level, view);
}

void ISampleViewLayoutVisitor::visit(ParticleDecorationView *view)
{
    std::cout << get_indent() << "ViewLayoutVisitor(ParticleDecorationView) " << m_level << " " << view->type() << " " << view->getName().toStdString() << std::endl;

    m_views.insertMulti(m_level, view);

    goForward();
    foreach(ISampleRectView *item, view->getConnectedInputItems()) {
        item->accept(this);
    }
    goBack();

}

