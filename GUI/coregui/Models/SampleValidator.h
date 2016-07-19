// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SampleValidator.h
//! @brief     Declares class SampleValidator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEVALIDATOR_H
#define SAMPLEVALIDATOR_H

#include <QModelIndex>

class SessionItem;
class MultiLayerItem;

//! Validates SampleModel for MultiLayerItem suitable for simulation
class SampleValidator
{
public:
    SampleValidator();

    bool isValidMultiLayer(const  MultiLayerItem *multilayer);

    QString getValidationMessage() const { return m_validation_message; }

private:
    void initValidator();

    void iterateItems(const SessionItem *parentItem);
    void validateItem(const SessionItem *item);

    QString validateMultiLayerItem(const SessionItem *item);
    QString validateParticleLayoutItem(const SessionItem *item);
    QString validateParticleCoreShellItem(const SessionItem *item);
    QString validateParticleCompositionItem(const SessionItem *item);
    QString validateParticleDistributionItem(const SessionItem *item);

    bool m_valid_sample;
    QString m_validation_message;
};


#endif // SAMPLEVALIDATOR_H
