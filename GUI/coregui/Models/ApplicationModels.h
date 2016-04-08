// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/ApplicationModels.h
//! @brief     Defines class holding all application models
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

    MaterialModel *materialModel() { return m_materialModel; }
    InstrumentModel *instrumentModel() { return m_instrumentModel; }
    SampleModel *sampleModel() { return m_sampleModel; }
    JobModel *jobModel() { return m_jobModel; }
    FitModel *fitModel() { return m_fitModel; }

    void resetModels();

private:
    void createModels();
    void createMaterialModel();
    void createInstrumentModel();
    void createSampleModel();
    void createJobModel();
    void createFitModel();
    void testGUIObjectBuilder();

    MaterialModel *m_materialModel;
    MaterialSvc *m_materialEditor;
    InstrumentModel *m_instrumentModel;
    SampleModel *m_sampleModel;
    JobModel *m_jobModel;
    FitModel *m_fitModel;
};



#endif
