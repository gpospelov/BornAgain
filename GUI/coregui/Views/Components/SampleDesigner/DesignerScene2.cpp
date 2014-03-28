#include "DesignerScene2.h"
#include "DesignerHelper.h"
#include "SessionModel.h"
#include "SampleViewFactory.h"
#include "IView.h"
#include "ConnectableView.h"
#include "ParameterizedGraphicsItem.h"
#include <QItemSelection>
#include <QDebug>


DesignerScene2::DesignerScene2(QObject *parent)
    : DesignerSceneInterface(parent)
    , m_sessionModel(0)
    , m_selectionModel(0)
    , m_block_selection(false)
{
    setSceneRect(QRectF(-500, -200, 800, 800));
    setBackgroundBrush(DesignerHelper::getSceneBackground());


    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));

}



void DesignerScene2::setModel(SessionModel *model)
{
    Q_ASSERT(model);

    if(model != m_sessionModel) {

        m_sessionModel = model;

        clear();
        update();
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


void DesignerScene2::onSessionSelectionChanged(const QItemSelection &selected, const QItemSelection & /* deselected */)
{
    qDebug() << "DesignerScene2::onSessionSelectionChanged()";

    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        ParameterizedGraphicsItem *item = static_cast<ParameterizedGraphicsItem *>(
                indices.back().internalPointer());
        Q_ASSERT(item);
        IView *view = m_ItemToView[item];
        Q_ASSERT(view);
        m_block_selection = true;
        clearSelection();
        view->setSelected(true);
        m_block_selection = false;
    }

}

void DesignerScene2::onSceneSelectionChanged()
{
    qDebug() << "DesignerScene2::onSceneSelectionChanged() 1.1";
    if(m_block_selection) return;
    qDebug() << "DesignerScene2::onSceneSelectionChanged() 1.2";

    m_selectionModel->clearSelection();

    QList<QGraphicsItem*> selected = selectedItems();
    for(int i=0; i<selected.size(); ++i) {
        IView *view = dynamic_cast<IView *>(selected[i]);
        if(view) {
            ParameterizedGraphicsItem *sessionItem = view->getSessionItem();
            QModelIndex itemIndex = m_sessionModel->indexOfItem(sessionItem);
            m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
            break; // selection of only one item will be propagated to the model
        }
    }
}




void DesignerScene2::update(const QModelIndex & parentIndex)
{
    Q_ASSERT(m_sessionModel);

    qDebug() << "DesignerScene2::update()";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    for( int i_row = 0; i_row < m_sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = static_cast<ParameterizedItem *>(
                     itemIndex.internalPointer())){

                addViewForItem(item);

         } else {
             qDebug() << "not a parameterized graphics item";
         }

         update( itemIndex);
     }


}


void DesignerScene2::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "DesignerScene2::addViewForItem() ->";
    Q_ASSERT(item);

    if( !SampleViewFactory::isValidName(item->modelType()) ) return;

    ParameterizedGraphicsItem *graphicsItem = static_cast<ParameterizedGraphicsItem *>(item);

    IView *view = m_ItemToView[graphicsItem];
    if(!view) {
        qDebug() << "Creating view for item" << graphicsItem->itemName();
        view = SampleViewFactory::createSampleView(graphicsItem->modelType());
        if(view) {
            m_ItemToView[graphicsItem] = view;
            view->setSessionItem(static_cast<ParameterizedGraphicsItem *>(graphicsItem));
            addItem(view);
        }
    } else {
        qDebug() << "View for item exists." << item->itemName();

    }

}







