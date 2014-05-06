#include "DesignerScene.h"
#include "DesignerHelper.h"
#include "SessionModel.h"
#include "SampleViewFactory.h"
#include "SampleViewAligner.h"
#include "IView.h"
#include "LayerView.h"
#include "ConnectableView.h"
#include "ItemFactory.h"
#include "ParameterizedGraphicsItem.h"
#include "NodeEditor.h"
#include "NodeEditorConnection.h"
#include "DesignerMimeData.h"
#include "SampleBuilderFactory.h"
#include "GUIExamplesFactory.h"
#include <QItemSelection>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <boost/scoped_ptr.hpp>


DesignerScene::DesignerScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_sessionModel(0)
    , m_selectionModel(0)
    , m_block_selection(false)
    , m_aligner(new SampleViewAligner(this))
{
    setSceneRect(QRectF(-400, 0, 800, 800));
    setBackgroundBrush(DesignerHelper::getSceneBackground());

    NodeEditor *nodeEditor = new NodeEditor(parent);
    nodeEditor->install(this);
    connect(nodeEditor, SIGNAL(connectionIsEstablished(NodeEditorConnection*)), this, SLOT(onEstablishedConnection(NodeEditorConnection*)));

    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
}


DesignerScene::~DesignerScene()
{
    delete m_aligner;
}


void DesignerScene::setSessionModel(SessionModel *model)
{
    Q_ASSERT(model);

    if(model != m_sessionModel) {

        if(m_sessionModel) {
            disconnect(m_sessionModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            disconnect(m_sessionModel, SIGNAL(rowsInserted(QModelIndex, int,int)), this, SLOT(onRowsInserted(QModelIndex, int,int)));
            disconnect(m_sessionModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int,int)), this, SLOT(onRowsAboutToBeRemoved(QModelIndex,int,int)));
            disconnect(m_sessionModel, SIGNAL(rowsRemoved(QModelIndex, int,int)), this, SLOT(onRowsRemoved(QModelIndex, int,int)));
            disconnect(m_sessionModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
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


void DesignerScene::setSelectionModel(QItemSelectionModel *model)
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


void DesignerScene::resetScene()
{
    qDebug() << "DesignerScene::resetScene()";
    clear();
    m_ItemToView.clear();
    m_layer_interface_line = QLineF();
}


void DesignerScene::updateScene()
{
    qDebug() << "DesignerScene::updateScene()";
    updateViews();
    alignViews();
}


void DesignerScene::onRowsInserted(const QModelIndex &/* parent */, int /* first */, int /* last */ )
{
    updateScene();
}


void DesignerScene::onRowsRemoved(const QModelIndex &/* parent */, int /* first */, int /* last */)
{
    updateScene();
}


void DesignerScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    qDebug() << "DesignerScene::onRowsAboutToBeRemoved()" << parent << first << last;
    for(int irow = first; irow<=last; ++irow ) {
        QModelIndex itemIndex = m_sessionModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
        //removeItemFromScene(m_sessionModel->itemForIndex(itemIndex)); // deleting parent item
    }
    m_block_selection = false;
}


//! propagate selection from model to scene
void DesignerScene::onSessionSelectionChanged(const QItemSelection &selected, const QItemSelection & /* deselected */)
{
    //qDebug() << "DesignerScene::onSessionSelectionChanged()";

    QModelIndexList indices = selected.indexes();
    if(indices.size()) {
        ParameterizedItem *item = m_sessionModel->itemForIndex(indices.back());
        Q_ASSERT(item);
        IView *view = m_ItemToView[item];
        //Q_ASSERT(view);
        if(view) {
            m_block_selection = true;
            clearSelection();
            view->setSelected(true);
            m_block_selection = false;
        } else {
            qDebug() << "DesignerScene::onSessionSelectionChanged() -> Error! No such view";
        }
    }

}


//! propagate selection from scene to model
void DesignerScene::onSceneSelectionChanged()
{
    //qDebug() << "DesignerScene::onSceneSelectionChanged() 1.1";
    if(m_block_selection) return;

    m_selectionModel->clearSelection();

    QList<QGraphicsItem*> selected = selectedItems();
    for(int i=0; i<selected.size(); ++i) {
        IView *view = dynamic_cast<IView *>(selected[i]);
        if(view) {
            ParameterizedItem *sessionItem = view->getParameterizedItem();
            QModelIndex itemIndex = m_sessionModel->indexOfItem(sessionItem);
            Q_ASSERT(itemIndex.isValid());
            m_selectionModel->select(itemIndex, QItemSelectionModel::Select);
            break; // selection of only one item will be propagated to the model
        }
    }
}


//! runs through all items recursively and updates corresponding views
void DesignerScene::updateViews(const QModelIndex & parentIndex, IView *parentView)
{
    Q_ASSERT(m_sessionModel);

    qDebug() << "DesignerScene::updateVIews()";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";
    }

    IView *childView(0);
    for( int i_row = 0; i_row < m_sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_sessionModel->itemForIndex(itemIndex)){

                childView = addViewForItem(item);
                if(childView) {
                    if(parentView) parentView->addView(childView, i_row);
                }

         } else {
             qDebug() << "not a parameterized graphics item";
         }

         updateViews( itemIndex, childView);
     }
}


//! adds view for item, if it dosn't exists
IView *DesignerScene::addViewForItem(ParameterizedItem *item)
{
    qDebug() << "DesignerScene::addViewForItem() ->";
    Q_ASSERT(item);

    IView *view = m_ItemToView[item];
    if(!view) {
        qDebug() << "Creating view for item" << item->itemName();
        view = SampleViewFactory::createSampleView(item->modelType());
        if(view) {
            m_ItemToView[item] = view;
            view->setParameterizedItem(item);
            addItem(view);
            return view;
        }
    } else {
        qDebug() << "View for item exists." << item->itemName();

    }
    return view;
}



//! aligns SampleView's on graphical canvas
void DesignerScene::alignViews()
{
    m_aligner->alignSample(QModelIndex(), QPointF(200,200));
}


//! runs recursively through model's item and schedules view removal
void DesignerScene::deleteViews(const QModelIndex & parentIndex)
{
    qDebug() << "DesignerScene::deleteViews()" << parentIndex;

    for( int i_row = 0; i_row < m_sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = m_sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = m_sessionModel->itemForIndex(itemIndex)){

             removeItemViewFromScene(item);

         } else {
             qDebug() << "not a parameterized graphics item";
         }
         deleteViews( itemIndex);
     }
    removeItemViewFromScene(m_sessionModel->itemForIndex(parentIndex)); // deleting parent item
}


//! removes view from scene corresponding to given item
void DesignerScene::removeItemViewFromScene(ParameterizedItem *item)
{
    qDebug() << "DesignerScene::removeItemFromScene()" << item->modelType();
    for(QMap<ParameterizedItem *, IView *>::iterator it=m_ItemToView.begin(); it!=m_ItemToView.end(); ++it) {
        if(it.key() == item) {
            IView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            emit view->aboutToBeDeleted();
            view->deleteLater();
            update();
            break;
        }
    }
}


//! propagates deletion of views on the scene to the model
void DesignerScene::deleteSelectedItems()
{
    qDebug() << "DesignerScene::deleteSelectedItems()" << selectedItems().size();
    // FIXME handle multiple selection
    foreach(QGraphicsItem *graphicsItem, selectedItems()) {
        if(IView *view = dynamic_cast<IView *>(graphicsItem)) {
            qDebug() << "xxx";
            ParameterizedItem *item = view->getParameterizedItem();
            Q_ASSERT(item);
            m_sessionModel->removeRows(m_sessionModel->indexOfItem(item).row(), 1, m_sessionModel->indexOfItem(item->parent()));
        } else if(NodeEditorConnection *connection = dynamic_cast<NodeEditorConnection *>(graphicsItem)) {
            removeConnection(connection);
        }
    }
}


//! shows appropriate layer interface to drop while moving ILayerView
void DesignerScene::drawForeground(QPainter* painter, const QRectF& /* rect */)
{
    ILayerView *layer = dynamic_cast<ILayerView *>(mouseGrabberItem());
    if(layer && !m_layer_interface_line.isNull()) {
        painter->setPen(QPen(Qt::darkBlue, 2, Qt::DashLine));
        painter->drawLine(m_layer_interface_line);
        invalidate();
    }
}


//! propagates connection established by NodeEditor to the model
void DesignerScene::onEstablishedConnection(NodeEditorConnection *connection)
{
    qDebug() << "DesignerScene::onEstablishedConnection()";
    IView *parentView = dynamic_cast<IView *>(connection->getInputPort()->parentItem());
    IView *childView = dynamic_cast<IView *>(connection->getOutputPort()->parentItem());
    Q_ASSERT(parentView);
    Q_ASSERT(childView);
    delete connection; // deleting just created connection because it will be recreated from the model
    m_sessionModel->moveParameterizedItem(childView->getParameterizedItem(), parentView->getParameterizedItem());
}


//! propagates break of connection between views on scene to the model
void DesignerScene::removeConnection(NodeEditorConnection *connection)
{
    qDebug() << "DesignerScene::removeConnection()";
    IView *childView = dynamic_cast<IView *>(connection->getOutputPort()->parentItem());
    m_sessionModel->moveParameterizedItem(childView->getParameterizedItem(), 0);
}


//! handles drag event
//! LayerView can be dragged only over MultiLayerView
//! MultiLayerView can be dragged both, over the scene and over another MultiLayerView
void DesignerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "DesignerScene::dragMoveEvent()";
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if(mimeData) {
        // Layer can be droped only on MultiLayer
        if(mimeData->getClassName() == QString("Layer")) {
            QGraphicsScene::dragMoveEvent(event);
        }

        // MultiLayer can be droped on another MultiLayer if there is one nearby
        if(mimeData->getClassName() == QString("MultiLayer")
                && isMultiLayerNearby(event)) {
            QGraphicsScene::dragMoveEvent(event);
        }
    }
}


//! Hadles drop event
//! LayerView can be dropped on MultiLayerView only
//! MultiLayerView can be droped on the scene or another MultiLayerView
void DesignerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    qDebug() << "DesignerScene::dropEvent()" << mimeData;
    if (mimeData) {

        // layer can be dropped on MultiLayer only
        if(mimeData->getClassName() == "Layer") {
            qDebug() << "DesignerScene::dropEvent() dont want to drop" << mimeData;
            QGraphicsScene::dropEvent(event);

        // MultiLayer can be droped on another MultiLayer if there is one nearby
        } else if(mimeData->getClassName() == "MultiLayer" && isMultiLayerNearby(event)) {
            QGraphicsScene::dropEvent(event);

        // other views can be droped on canvas anywhere
        } else {
            qDebug() << "DesignerScene::dropEvent() -> about to drop";
            if(SampleViewFactory::isValidItemName(mimeData->getClassName())) {

                ParameterizedItem *new_item(0);
                if(mimeData->getClassName().startsWith("FormFactor")) {
                    new_item = m_sessionModel->insertNewItem("Particle");
                    QString ffName = mimeData->getClassName();
                    ffName.remove("FormFactor");
                    new_item->addFormFactorProperty("Form Factor", ffName);

                } else {
                    new_item = m_sessionModel->insertNewItem(mimeData->getClassName());
                }

                // propagating drop coordinates to ParameterizedItem
                QRectF boundingRect = DesignerHelper::getDefaultBoundingRect(new_item->modelType());
                new_item->setProperty("xpos", event->scenePos().x()-boundingRect.width()/2);
                new_item->setProperty("ypos", event->scenePos().y()-boundingRect.height()/2);

            } else if(GUIExamplesFactory::isValidExampleName(mimeData->getClassName())) {
                ParameterizedItem *topItem = GUIExamplesFactory::createItems(mimeData->getClassName(), m_sessionModel);
                //ParameterizedItem *topItem = dropCompleteSample(mimeData->getClassName());
                QRectF boundingRect = DesignerHelper::getDefaultBoundingRect(topItem->modelType());
                //qDebug() << ">>>>>>>>>>>>>>>> xxx " << topItem->modelType();
                //topItem->setProperty("xpos", event->scenePos().x()-boundingRect.width()/2);
                //topItem->setProperty("ypos", event->scenePos().y()-boundingRect.height()/2);
                QPointF reference(event->scenePos().x()-boundingRect.width()/2, event->scenePos().y()-boundingRect.height()/2);
                m_aligner->alignSample(topItem, reference, true);
            }
        }
    }
}


//! returns proper MimeData if the object can be hadled by graphics scene
const DesignerMimeData *DesignerScene::checkDragEvent(QGraphicsSceneDragDropEvent * event)
{
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
    }
    event->setAccepted(true);
    return mimeData;
}


//! Returns true if there is MultiLayerView nearby during drag event.
bool DesignerScene::isMultiLayerNearby(QGraphicsSceneDragDropEvent *event)
{
    QRectF rect = DesignerHelper::getDefaultMultiLayerRect();
    rect.moveCenter(event->scenePos());
    foreach(QGraphicsItem *item, items(rect)) {
        if(item->type() == DesignerHelper::MultiLayerType) return true;
    }
    return false;
}


//! create complete sample from domain's standard sample
//ParameterizedItem *DesignerScene::dropCompleteSample(const QString &name)
//{
//    qDebug() << "DesignerScene::dropCompleteSample()" << name;
//    if( !name.startsWith("Example_") ) return 0;

//    QString exampleName = name;
//    exampleName.remove("Example_");

//    SampleBuilderFactory factory;
//    boost::scoped_ptr<ISample> sample(factory.createSample(exampleName.toAscii().data()));
//    //sample->printSampleTree();

//    GUIObjectBuilder guiBuilder;
//    guiBuilder.populateModel(m_sessionModel, sample.get());

//    return guiBuilder.getTopItem();
//}


void DesignerScene::onSmartAlign()
{
    m_aligner->smartAlign();
}
