#include "DesignerScene2.h"
#include "DesignerHelper.h"
#include "SessionModel.h"
#include "SampleViewFactory.h"
#include "SampleViewAligner.h"
#include "IView.h"
#include "ConnectableView.h"
#include "ParameterizedGraphicsItem.h"
#include "NodeEditor.h"
#include <QItemSelection>
#include <QDebug>


DesignerScene2::DesignerScene2(QObject *parent)
    : DesignerSceneInterface(parent)
    , m_sessionModel(0)
    , m_selectionModel(0)
    , m_block_selection(false)
{
    setSceneRect(QRectF(-400, 0, 800, 800));
    setBackgroundBrush(DesignerHelper::getSceneBackground());

    NodeEditor *nodeEditor = new NodeEditor(parent);
    nodeEditor->install(this);

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));

}



void DesignerScene2::setSessionModel(SessionModel *model)
{
    Q_ASSERT(model);

    if(model != m_sessionModel) {

        if(m_sessionModel) {
            // TODO disconnect all
        }

        m_sessionModel = model;

        connect(m_sessionModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));

        connect(m_sessionModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onRowsInserted(QModelIndex, int,int)));
        connect(m_sessionModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
        connect(m_sessionModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onRowsRemoved(QModelIndex, int,int)));


        connect(m_sessionModel, SIGNAL(modelReset()), this, SLOT(updateScene()));


        resetScene();
        updateScene();
    }
}


void DesignerScene2::setSelectionModel(QItemSelectionModel *model)
{
    Q_ASSERT(model);

    if(model != m_selectionModel) {

        if(m_selectionModel) {
            disconnect(m_selectionModel,
                    SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                    this,
                    SLOT(onSessionSelectionChanged(QItemSelection,QItemSelection)) );
        }

        m_selectionModel = model;

        connect(m_selectionModel,
                SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this,
                SLOT(onSessionSelectionChanged(QItemSelection,QItemSelection)) );
    }
}


void DesignerScene2::resetScene()
{
    qDebug() << "DesignerScene2::resetScene()";
    clear();
    m_orderedViews.clear();
    m_ItemToView.clear();
}


void DesignerScene2::updateScene()
{
    qDebug() << "DesignerScene2::updateScene()";
    m_orderedViews.clear();
    updateViews();
    alignViews();

}


void DesignerScene2::onRowsInserted(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    qDebug() << "DesignerScene2::onRowsInserted()" << parent;
    updateScene();
}


void DesignerScene2::onRowsRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    qDebug() << "DesignerScene2::onRowsRemoved()" << parent;
    updateScene();
}


void DesignerScene2::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "DesignerScene2::onRowsAboutToBeRemoved()" << parent << first << last;
    for(int irow = first; irow<=last; ++irow ) {
        QModelIndex itemIndex = m_sessionModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
        removeItemFromScene(m_sessionModel->itemForIndex(itemIndex)); // deleting parent item
    }
    m_block_selection = false;
}


void DesignerScene2::onSessionSelectionChanged(const QItemSelection &selected, const QItemSelection & /* deselected */)
{
    //qDebug() << "DesignerScene2::onSessionSelectionChanged()";

    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        ParameterizedGraphicsItem *item = static_cast<ParameterizedGraphicsItem *>(
                indices.back().internalPointer());
        Q_ASSERT(item);
        IView *view = m_ItemToView[item];
        //Q_ASSERT(view);
        if(view) {
            m_block_selection = true;
            clearSelection();
            view->setSelected(true);
            m_block_selection = false;
        } else {
            qDebug() << "DesignerScene2::onSessionSelectionChanged() -> Error! No such view";
        }
    }

}


void DesignerScene2::onSceneSelectionChanged()
{
    //qDebug() << "DesignerScene2::onSceneSelectionChanged() 1.1";
    if(m_block_selection) return;

    m_selectionModel->clearSelection();

    QList<QGraphicsItem*> selected = selectedItems();
    for(int i=0; i<selected.size(); ++i) {
        IView *view = dynamic_cast<IView *>(selected[i]);
        if(view) {
            ParameterizedItem *sessionItem = view->getSessionItem();
            QModelIndex itemIndex = m_sessionModel->indexOfItem(sessionItem);
            Q_ASSERT(itemIndex.isValid());
            m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
            break; // selection of only one item will be propagated to the model
        }
    }
}


void DesignerScene2::updateViews(const QModelIndex & parentIndex, IView *parentView)
{
    Q_ASSERT(m_sessionModel);

    qDebug() << "DesignerScene2::update()";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    IView *childView(0);
    for( int i_row = 0; i_row < m_sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_sessionModel->itemForIndex(itemIndex)){

                childView = addViewForItem(item);
                m_orderedViews.push_back(childView);
                if(parentView) parentView->addView(childView, i_row);

         } else {
             qDebug() << "not a parameterized graphics item";
         }

         updateViews( itemIndex, childView);
     }
}


IView *DesignerScene2::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "DesignerScene2::addViewForItem() ->";
    Q_ASSERT(item);

    IView *view = m_ItemToView[item];
    if(!view) {
        qDebug() << "Creating view for item" << item->itemName();
        view = SampleViewFactory::createSampleView(item->modelType());
        if(view) {
            m_ItemToView[item] = view;
            view->setSessionItem(item);
            addItem(view);
            return view;
        }
    } else {
        qDebug() << "View for item exists." << item->itemName();

    }
    return view;
}



// aligns SampleView's on graphical canvas
void DesignerScene2::alignViews()
{
    //QList<IView *> views = m_ItemToView.values();
    SampleViewAligner::align(m_orderedViews, QPointF(400,400));
}


void DesignerScene2::deleteViews(const QModelIndex & parentIndex)
{
    qDebug() << "DesignerScene2::deleteViews()" << parentIndex;

    for( int i_row = 0; i_row < m_sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_sessionModel->itemForIndex(itemIndex)){

             removeItemFromScene(item);

         } else {
             qDebug() << "not a parameterized graphics item";
         }
         deleteViews( itemIndex);
     }
}



void DesignerScene2::removeItemFromScene(ParameterizedItem *item)
{
    qDebug() << "DesignerScene2::removeItemFromScene()" << item->modelType();
    for(QMap<ParameterizedItem *, IView *>::iterator it=m_ItemToView.begin(); it!=m_ItemToView.end(); ++it) {
        if(it.key() == item) {
            IView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            emit view->aboutToBeDeleted();
            delete view;
            update();
            break;
        }
    }
}



void DesignerScene2::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "DesignerScene2::mouseMoveEvent()";

    QGraphicsScene::mouseMoveEvent(event);
}



