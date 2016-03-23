// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/SampleValidator.h
//! @brief     Defines class SampleValidator
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAMPLE_VALIDATOR
#define SAMPLE_VALIDATOR

#include <QString>
#include <QModelIndex>

class SampleModel;
class SessionItem;

//! Validates SampleModel for MultiLayerItem suitable for simulation
class SampleValidator
{
public:
    SampleValidator();

    bool isValidSampleModel(SampleModel *sampleModel);

    QString getValidationMessage() const { return m_validation_message; }

private:
    void iterateSampleModel(SampleModel *sampleModel, const QModelIndex &parentIndex = QModelIndex());

    QString validateMultiLayerItem(SessionItem *item);
    QString validateParticleLayoutItem(SessionItem *item);
    QString validateParticleCoreShellItem(SessionItem *item);
    QString validateParticleCompositionItem(SessionItem *item);

    bool m_valid_sample;
    QString m_validation_message;
};


#endif
