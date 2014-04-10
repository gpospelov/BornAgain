#include "SampleViewAligner.h"
#include "IView.h"
#include "ParameterizedItem.h"
#include <QDebug>


//! Initialises correspondance between ParameterizedItem's type and area on
//! the screen.
//!
//! Area #0 correspond to the items located on the right side  of graphics
//! scene (MultiLayer, Layer), area #1 corresponds to the items closer to the
//! center (ParticleLayout), area #2 is reserved for FormFactors and
//! interference functions, area #3 for transformations.
QMap<QString, int>  initTypeToAreaMap()
{
    QMap<QString, int> result;
    result["MultiLayer"] = 0;
    result["Layer"] = 0;
    result["ParticleLayout"] = 1;
    result["FormFactorSphere"] = 2;
    return result;
}


QMap<QString, int> SampleViewAligner::m_typeToArea = initTypeToAreaMap();


//! aligns Views according to predefined areas
void SampleViewAligner::align(QList<IView *> views, QPointF reference)
{
    //qDebug() << "---------------------------------------";
    //qDebug() << "SampleViewAligner::align()" << reference;
    QMap<int, IView *> areaToView;
    foreach(IView *view, views) {
        int area = m_typeToArea[view->getParameterizedItem()->modelType()];
        //qDebug() << "area" << area << view->getSessionItem()->modelType();
        if(!view->parentObject())
            areaToView.insertMulti(area, view);
    }

    for(int i_level = 0; i_level <= getMaximumAreaNumber(); ++i_level) {
        QList<IView *> items = areaToView.values(i_level);
        //qDebug() << "SampleViewAligner::align() i_level" << i_level << "size" << items.size();
        reference = placeItems(items, reference);
    }
}


QPointF SampleViewAligner::placeItems(const QList<IView *> &items,
                                      QPointF reference)
{
    const double size_factor = 1.5;
    const double vertical_gap(50);
    qreal dy = getTotalVerticalSpace(items) + (items.size()-1)*vertical_gap;
    qreal dx = size_factor*getMaximumHorizontalSpace(items);
    reference.setX(reference.x() - dx );
    //qDebug() << "SampleViewAligner::placeItems() dy:" << dy << " dx:" << dx << " reference:" << reference;
    for(int i=0; i<items.size(); ++i) {
        IView *view = items[i];
        //qDebug() << "SampleViewAligner::placeItems()" << view->getSessionItem()->modelType() << view->parentObject();
        QPointF pos = reference;
        //qDebug() << "xxx " << view->x() << view->y() << (pos.y() - i*dy/items.size());
        pos.setY(pos.y() - i*dy/items.size());
        if(view->pos().isNull())
            view->setPos(pos);
    }
    return reference;
}


qreal SampleViewAligner::getTotalVerticalSpace(const QList<IView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        result += items.at(i)->boundingRect().height();
    }
    return result;
}


qreal SampleViewAligner::getMaximumHorizontalSpace(const QList<IView *> &items)
{
    qreal result = 0;
    for(int i=0; i<items.size(); ++i) {
        qreal width = items.at(i)->boundingRect().width();
        if(width > result) result = width;
    }
    return result;
}
