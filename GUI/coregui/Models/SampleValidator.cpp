#include "SampleValidator.h"
#include "MultiLayerItem.h"
#include "SampleModel.h"
#include <QDebug>

SampleValidator::SampleValidator()
    : m_valid_sample(true)
{

}


void SampleValidator::iterateSampleModel(SampleModel *sampleModel, const QModelIndex &parentIndex)
{
    for( int i_row = 0; i_row < sampleModel->rowCount( parentIndex ); ++i_row) {
        QModelIndex itemIndex = sampleModel->index( i_row, 0, parentIndex );

        if (ParameterizedItem *item = sampleModel->itemForIndex(itemIndex)){
            qDebug() << item->modelType();
            QString diagnosis;
            if(item->modelType() == Constants::MultiLayerType) {
                diagnosis = validateMultiLayerItem(item) ;
            }
            else if(item->modelType() == Constants::ParticleLayoutType) {
                diagnosis = validateParticleLayoutItem(item) ;
            }

            if(!diagnosis.isEmpty()) {
                m_valid_sample = false;
                m_validation_message += QString("* ") + diagnosis + QString("\n");
            }
        }

        iterateSampleModel(sampleModel, itemIndex);
    }
}


QString SampleValidator::validateMultiLayerItem(ParameterizedItem *item)
{
    QString result;
    if(!item->childItems().size()) {
        result = QString("MultiLayer should contain at least one layer.");
    }else if(item->childItems().size() == 1) {
        if(item->childAt(0)->childItems().size() == 0) {
            result = QString("The single layer in your MultiLayer should contain ParticleLayout.");
        }
    }
    return result;
}


QString SampleValidator::validateParticleLayoutItem(ParameterizedItem *item)
{
    QString result;
    bool particles_found(false);
    QList<ParameterizedItem *> children = item->childItems();
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleType) {
            particles_found = true;
        }
    }
    if(!particles_found) {
        result = QString("ParticleLayout doesn't contain any particles.");
    }
    return result;
}



bool SampleValidator::isVaildSampleModel(SampleModel *sampleModel)
{
    m_validation_message.clear();

    iterateSampleModel(sampleModel);

    if(!m_valid_sample) {
        m_validation_message = QString("Can't setup DWBA simulation for given MultiLayer.\n") + m_validation_message;
    }

    return m_valid_sample;
}

