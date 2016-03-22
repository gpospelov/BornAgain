// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Models/GUIExamplesFactory.h
//! @brief     Defines class GUIExamplesFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GUIEXAMPLESFACTORY_H
#define GUIEXAMPLESFACTORY_H

#include "WinDllMacros.h"
#include <QMap>
#include <QString>

class SessionItem;
class InstrumentModel;
class SampleModel;

//! Class that generates GUI model from
class BA_CORE_API_ GUIExamplesFactory
{
public:
    static bool isValidExampleName(const QString &name);

    static SessionItem *createSampleItems(const QString &name, SampleModel *sampleModel);
//    static SessionItem *createInstrumentItems(const QString &name, InstrumentModel *instrumentModel);

private:
    static QMap<QString, QString> m_name_to_registry;
    //!< correspondance of GUI example name and name from StandardSamples registry
};


#endif

