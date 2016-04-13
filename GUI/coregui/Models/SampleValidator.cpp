// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SampleValidator.cpp
//! @brief     Implements class SampleValidator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "SampleValidator.h"
#include "MultiLayerItem.h"
#include "LayerItem.h"
#include "ParticleLayoutItem.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleDistributionItem.h"
#include "SessionModel.h"
#include "SampleModel.h"
#include <QDebug>

SampleValidator::SampleValidator()
    : m_valid_sample(true)
{

}

void SampleValidator::initValidator()
{
    m_validation_message.clear();
    m_valid_sample = true;
}

void SampleValidator::iterateItems(const SessionItem *parentItem)
{
    foreach(const SessionItem *child, parentItem->childItems()) {
        validateItem(child);
        iterateItems(child);
    }
}

void SampleValidator::validateItem(const SessionItem *item)
{
    if(!item) return;

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

    else if(item->modelType() == Constants::ParticleCompositionType) {
        diagnosis = validateParticleCompositionItem(item);
    }

    else if(item->modelType() == Constants::ParticleCompositionType) {
        diagnosis = validateParticleCompositionItem(item);
    }

    else if(item->modelType() == Constants::ParticleDistributionType) {
        diagnosis = validateParticleDistributionItem(item);
    }

    if(!diagnosis.isEmpty()) {
        m_valid_sample = false;
        m_validation_message += QString("* ") + diagnosis + QString("\n");
    }
}

QString SampleValidator::validateMultiLayerItem(const SessionItem *item)
{
    QString result;

    QVector<SessionItem *> layers = item->getItems(MultiLayerItem::T_LAYERS);

    if(layers.isEmpty()) {
        result = QStringLiteral("MultiLayer should contain at least one layer.");
    }

    else if(layers.size() == 1) {
        if(layers.front()->getItems(LayerItem::T_LAYOUTS).isEmpty()) {
            result = QStringLiteral(
                        "The single layer in your MultiLayer should contain ParticleLayout.");
        }
    }
    return result;
}


QString SampleValidator::validateParticleLayoutItem(const SessionItem *item)
{
    QString result;

    QVector<SessionItem *> particles = item->getItems(ParticleLayoutItem::T_PARTICLES);
    if(particles.isEmpty())
        result = QStringLiteral("ParticleLayout doesn't contain any particles.");

    return result;
}

QString SampleValidator::validateParticleCoreShellItem(const SessionItem *item)
{
    QString result;

    const SessionItem *core = item->getItem(ParticleCoreShellItem::T_CORE);
    const SessionItem *shell = item->getItem(ParticleCoreShellItem::T_SHELL);

    if(core == nullptr || shell == nullptr)
        result = QStringLiteral("ParticleCoreShell doesn't have either core or shell defined.");

    return result;
}

QString SampleValidator::validateParticleCompositionItem(const SessionItem *item)
{
    QString result;
    if (item->getItems(ParticleCompositionItem::T_PARTICLES).isEmpty())
        result = QStringLiteral("ParticleComposition doesn't have any particles.");

    return result;
}

QString SampleValidator::validateParticleDistributionItem(const SessionItem *item)
{
    QString result;
    if (item->getItems(ParticleDistributionItem::T_PARTICLES).isEmpty())
        result = QStringLiteral("ParticleDistribution doesn't have any particle.");

    return result;

}

bool SampleValidator::isValidMultiLayer(const MultiLayerItem *multilayer)
{
    initValidator();

    validateItem(multilayer);
    iterateItems(multilayer);

    if(!m_valid_sample) {
        m_validation_message = QStringLiteral(
                    "Can't setup DWBA simulation for given MultiLayer.\n") + m_validation_message;
    }

    return m_valid_sample;
}

