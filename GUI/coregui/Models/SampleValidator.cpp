// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SampleValidator.cpp
//! @brief     Implements class SampleValidator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

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
                diagnosis = validateMultiLayerItem(item);
            }
            else if(item->modelType() == Constants::ParticleLayoutType) {
                diagnosis = validateParticleLayoutItem(item);
            }
            else if(item->modelType() == Constants::ParticleCoreShellType) {
                diagnosis = validateParticleCoreShellItem(item);
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
    QVector<ParameterizedItem *> children = item->childItems();
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType() == Constants::ParticleType
            || children[i]->modelType() == Constants::ParticleCoreShellType
            || children[i]->modelType() == Constants::ParticleCompositionType
            || children[i]->modelType() == Constants::ParticleDistributionType) {
            particles_found = true;
        }
    }
    if(!particles_found) {
        result = QString("ParticleLayout doesn't contain any particles.");
    }
    return result;
}

QString SampleValidator::validateParticleCoreShellItem(ParameterizedItem *item)
{
    QString result;
    int number_of_subparticles = 0;
    QVector<ParameterizedItem*> children = item->childItems();
    for (int i=0; i<children.size(); ++i) {
        if (children[i]->modelType()==Constants::ParticleType) {
            number_of_subparticles++;
        }
    }
    if(number_of_subparticles != 2) {
        result = QString("ParticleCoreShell doesn't have either core or shell defined.");
    }
    return result;
}



bool SampleValidator::isValidSampleModel(SampleModel *sampleModel)
{
    m_validation_message.clear();

    iterateSampleModel(sampleModel);

    if(!m_valid_sample) {
        m_validation_message = QString("Can't setup DWBA simulation for given MultiLayer.\n") + m_validation_message;
    }

    return m_valid_sample;
}

