// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ApplicationModels.h
//! @brief     Declares class holding all application models
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef APPLICATIONMODELS_H
#define APPLICATIONMODELS_H

#include "WinDllMacros.h"
#include <QObject>

class SessionModel;
class DocumentModel;
class MaterialModel;
class MaterialSvc;
class InstrumentModel;
class SampleModel;
class JobModel;
class FitModel;

class BA_CORE_API_ ApplicationModels : public QObject
{
    Q_OBJECT
public:
    ApplicationModels(QObject *parent);
    ~ApplicationModels();

    DocumentModel *documentModel();
    MaterialModel *materialModel();
    InstrumentModel *instrumentModel();
    SampleModel *sampleModel();
    JobModel *jobModel();
    FitModel *fitModel();

    void resetModels();

signals:
    void modelChanged();

private:
    void createModels();
    void createDocumentModel();
    void createMaterialModel();
    void createInstrumentModel();
    void createSampleModel();
    void createJobModel();
    void createFitModel();
    void testGUIObjectBuilder();

    void disconnectModel(SessionModel *model);
    void connectModel(SessionModel *model);

    DocumentModel *m_documentModel;
    MaterialModel *m_materialModel;
    MaterialSvc *m_materialSvc;
    InstrumentModel *m_instrumentModel;
    SampleModel *m_sampleModel;
    JobModel *m_jobModel;
    FitModel *m_fitModel;
};

#endif
