// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/GUIObjectBuilder.h
//! @brief     Defines class GUIObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef GUIOBJECTBUILDER_H
#define GUIOBJECTBUILDER_H

#include "INodeVisitor.h"
#include <QMap>
#include <QString>

class Material;
class InstrumentModel;
class SampleModel;
class SessionItem;
class MaterialModel;
class DocumentModel;
class Simulation;
class ExternalProperty;

//! Class to build SampleModel and InstrumentModel from domain's ISample
class BA_CORE_API_ GUIObjectBuilder
{
public:
    GUIObjectBuilder() {}

    SessionItem* populateSampleModel(SampleModel* sampleModel, MaterialModel* materialModel,
                                     const Simulation& simulation,
                                     const QString& sample_name = QString());

    SessionItem* populateSampleModel(SampleModel* sampleModel, MaterialModel* materialModel,
                                     const MultiLayer& sample, const QString& sample_name = QString());

    SessionItem* populateInstrumentModel(InstrumentModel* p_instrument_model,
                                         const Simulation& simulation,
                                         const QString& instrument_name = QString());

    SessionItem* populateDocumentModel(DocumentModel* p_documentModel,
                                       const Simulation& simulation);
};

#endif // GUIOBJECTBUILDER_H
