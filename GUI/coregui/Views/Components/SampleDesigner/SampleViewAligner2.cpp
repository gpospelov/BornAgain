#include "SampleViewAligner2.h"
#include "SessionModel.h"
#include "DesignerScene.h"
#include "IView.h"
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
    Q_ASSERT(m_scene);
}


void SampleViewAligner2::smartAlign()
{
    m_views.clear();

    updateViews();
    updateForces();
    advance();
}


void SampleViewAligner2::updateViews(const QModelIndex & parentIndex)
{
    SessionModel *sessionModel = m_scene->getSessionModel();

    qDebug() << "DesignerScene::updateViews()";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    for( int i_row = 0; i_row < sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = sessionModel->itemForIndex(itemIndex)){
             qDebug() << "     " << i_row << item->itemName() << item->modelType() << item->childItemCount();

            IView *view = m_scene->getViewForItem(item);

            if(view && !view->parentObject()) {
                m_views.append(view);
            }

         } else {
             qDebug() << "not a parameterized graphics item";
         }

         updateViews( itemIndex);
     }
}


void SampleViewAligner2::updateForces()
{
    m_viewToPos.clear();
    qDebug() << "SampleViewAligner2::updateForces()";
    foreach(IView *view, m_views) {
        calculateForces(view);
    }
}


void SampleViewAligner2::calculateForces(IView *view)
{
    qDebug() << "SampleViewAligner2::calculateForces()" << view->getParameterizedItem()->itemName() << view->pos() << "connected items:" << getConnectedViews(view).size();
    qreal xvel = 0;
    qreal yvel = 0;
    QPointF p1 = view->boundingRect().center();

    // repulsive forces (ushing away)

    double C = 0.2;
    foreach(IView *other, m_views) {
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
    foreach(IView *other, getConnectedViews(view)) {
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
    foreach(IView *view, m_views) {
        view->setPos(m_viewToPos[view]);
    }
}




void SampleViewAligner2::alignSample(ParameterizedItem *item, QPointF reference, bool force_alignment)
{
    Q_ASSERT(item);
    alignSample(m_scene->getSessionModel()->indexOfItem(item), reference, force_alignment);
}


//! Aligns sample starting from reference point.
//! If force_alignment=false, view position will be changed only if it has Null coordinate,
//! if force_alignment=true the position will be changed anyway.
//! Position of View which has parent item (like Layer) will remain unchainged.
void SampleViewAligner2::alignSample(const QModelIndex & parentIndex, QPointF reference, bool force_alignment)
{
    SessionModel *sessionModel = m_scene->getSessionModel();

    IView *view = getViewForIndex(parentIndex);
    if(view)
        qDebug() << "SampleViewAligner2::alignSample" << view->getParameterizedItem()->modelType() << reference
                 << view->pos() << view->mapToScene(view->pos());

    if(view) {
        if( (force_alignment || view->pos().isNull()) && !view->parentObject())
            view->setPos(reference);

        if(view->parentObject()) {
            reference = view->mapToScene(view->pos());
        } else {
            reference = view->pos();
        }
    }

    qDebug() << "   new_pos:" << reference;

    for( int i_row = 0; i_row < sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = sessionModel->index( i_row, 0, parentIndex );
         QPointF child_reference = reference + QPointF(-150, 150*i_row);
         qDebug() << "   child_reference:" << child_reference;
         alignSample(itemIndex, child_reference, force_alignment);
    }
}


IView *SampleViewAligner2::getViewForIndex(const QModelIndex &index)
{
    SessionModel *sessionModel = m_scene->getSessionModel();
    ParameterizedItem *item = sessionModel->itemForIndex(index);
    if(IView *view = m_scene->getViewForItem(item)) {
        return view;
    }
    return 0;
}


QList<IView *> SampleViewAligner2::getConnectedViews(IView *view)
{

    QList<IView *> result;

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
        if(view) {
            result.append(view);
        }

    }

    return result;
}

