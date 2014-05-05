#include "SampleViewAligner2.h"
#include "SessionModel.h"
#include "DesignerScene.h"
#include <QModelIndex>
#include <QDebug>



SampleViewAligner2::SampleViewAligner2()
    : m_scene(0)
{

}


void SampleViewAligner2::align(DesignerScene *scene)
{
    m_scene = scene;

    updateViews();
}



void SampleViewAligner2::updateViews(const QModelIndex & parentIndex)
{
    Q_ASSERT(m_scene);
    SessionModel *sessionModel = m_scene->getSessionModel();

    qDebug() << "DesignerScene::align()";

    if(!parentIndex.isValid()) {
        qDebug() << "Dumping model";

    }

    for( int i_row = 0; i_row < sessionModel->rowCount( parentIndex ); ++i_row) {
         QModelIndex itemIndex = sessionModel->index( i_row, 0, parentIndex );

         if (ParameterizedItem *item = sessionModel->itemForIndex(itemIndex)){
            qDebug() << "     " << i_row << item->itemName() << item->modelType() << item->childItemCount();


         } else {
             qDebug() << "not a parameterized graphics item";
         }

         updateViews( itemIndex);
     }
}
