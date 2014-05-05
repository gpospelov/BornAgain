#include "SampleViewAligner2.h"
#include "SessionModel.h"
#include "DesignerScene.h"
#include "IView.h"
#include "ConnectableView.h"
#include <QModelIndex>
#include <QDebug>



QMap<QString, int>  initTypeToAreaMap2()
{
    QMap<QString, int> result;
    result["MultiLayer"] = 0;
    result["Layer"] = 0;
    result["ParticleLayout"] = 1;
    result["Particle"] = 2;
    return result;
}

QMap<QString, int> SampleViewAligner2::m_typeToArea = initTypeToAreaMap2();



SampleViewAligner2::SampleViewAligner2(DesignerScene *scene)
    : m_scene(scene)
{

}


void SampleViewAligner2::align()
{

    m_views.clear();
    m_connectedViews.clear();

    updateViews();
    qDebug() << "SampleViewAligner2::align" << m_views.size();

//    for(int i=0; i<100; ++i) {
//        updateForces();
//        advance();
//    }
}


void SampleViewAligner2::updateForces()
{
    m_viewToPos.clear();
    qDebug() << "SampleViewAligner2::updateForces()";
    foreach(ConnectableView *view, m_views) {
        calculateForces(view);
    }
}


void SampleViewAligner2::calculateForces(ConnectableView *view)
{
    qDebug() << "SampleViewAligner2::calculateForces()" << view->getParameterizedItem()->itemName() << view->pos() << "connected items:" << getConnectedViews(view).size();
    qreal xvel = 0;
    qreal yvel = 0;
    QPointF p1 = view->boundingRect().center();

    // repulsive forces (ushing away)

    double C = 0.2;
    foreach(ConnectableView *other, m_views) {
        QPointF vec = view->mapToItem(other, other->boundingRect().center());
        qreal dx = view->boundingRect().center().x() - vec.x();
        qreal dy = view->boundingRect().center().y() - vec.y();
//        QPointF vec = view->mapToItem(other, 0, 0);
//        qreal dx = vec.x();
//        qreal dy = vec.y();

        double l = (dx * dx + dy * dy);
        qDebug() << "    " << view->getParameterizedItem()->itemName() << other->getParameterizedItem()->itemName() << l;
        if (l > 0) {
            xvel -= (dx * 200.0) / l;
            yvel -= (dy * 200.0) / l;
        }
    }
    qDebug() << "pushing: xvel, yvel" << xvel << yvel ;

    // pulling forces (attractive forces)
    double weight(100.0);
    foreach(ConnectableView *other, getConnectedViews(view)) {
        QPointF vec = view->mapToItem(other, other->boundingRect().center());
        qreal dx = view->boundingRect().center().x() - vec.x();
        qreal dy = view->boundingRect().center().y() - vec.y();
//        QPointF vec = view->mapToItem(other, 0, 0);
//        qreal dx = vec.x();
//        qreal dy = vec.y();
        //qreal dx = vec.x();
        //qreal dy = vec.y();
        double l = (dx * dx + dy * dy);
//        xvel += dx / weight;
//        yvel += dy / weight;
        xvel += dx/weight;
        yvel += dy/weight;
        qDebug() << "     pull_forces" << view->getParameterizedItem()->itemName() << other->getParameterizedItem()->itemName() << vec.x() << vec.y();
    }
    qDebug() << "       pulling (attracting): xvel, yvel" << xvel << yvel;

    QPointF newPos = view->pos() + QPointF(xvel, yvel);
    qDebug() << "       newPos" << newPos;
    m_viewToPos[view] = newPos;
}


void SampleViewAligner2::advance()
{
    foreach(ConnectableView *view, m_views) {
        view->setPos(m_viewToPos[view]);
    }
}


void SampleViewAligner2::updateViews(const QModelIndex & parentIndex, QPointF reference)
{
    Q_ASSERT(m_scene);
    SessionModel *sessionModel = m_scene->getSessionModel();

    qDebug() << "DesignerScene::align()";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    //QPointF reference(0,200);
    QPointF new_reference;

    for( int i_row = 0; i_row < sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = sessionModel->itemForIndex(itemIndex)){
             qDebug() << "     " << i_row << item->itemName() << item->modelType() << item->childItemCount() <<  "reference: " << reference;

            IView *view = m_scene->getViewForItem(item);

            if(view) {
                qDebug() << " view->pos() " << view->pos();

                if(reference.isNull()) reference = view->pos();

                Q_ASSERT(dynamic_cast<ConnectableView *>(view));
                //int level = m_typeToArea[item->modelType()];

                m_views.append(dynamic_cast<ConnectableView *>(view));

                //if(view->pos().isNull()) {
                if(!view->parentObject()) {
                    view->setPos(reference + QPointF(-140, 150*i_row));
                }
                new_reference = view->mapToScene(view->pos());
                qDebug() << "   reference" << reference << new_reference;

            }

         } else {
             qDebug() << "not a parameterized graphics item";
         }

         updateViews( itemIndex, new_reference);
     }
}



void SampleViewAligner2::alignSample(ParameterizedItem *item, QPointF reference)
{

}



QList<ConnectableView *> SampleViewAligner2::getConnectedViews(ConnectableView *view)
{

    QList<ConnectableView *> result;

    ParameterizedItem *itemOfView = view->getParameterizedItem();
    //qDebug() << "SampleViewAligner2::getConnectedViews" << itemOfView->itemName() << " parent:" << itemOfView->parent();

    QList<ParameterizedItem *> connected_items;

    if(itemOfView->parent()->modelType() == "Layer") {
        connected_items.append(itemOfView->parent()->parent()); // use MultiLayer instead
    } else {
        connected_items.append(itemOfView->parent());
    }


    if(itemOfView->modelType() == "MultiLayer") {
        foreach(ParameterizedItem *child,  itemOfView->childItems()) {
            connected_items.append(child->childItems());
        }
    } else {
        connected_items.append(itemOfView->childItems());

    }

    foreach(ParameterizedItem *item, connected_items) {
        IView *view = m_scene->getViewForItem(item);
        //qDebug() << item->itemName() << item->modelType();
        if(view) {
            Q_ASSERT(dynamic_cast<ConnectableView *>(view));
            result.append(dynamic_cast<ConnectableView *>(view));
        }

    }

    return result;
}

