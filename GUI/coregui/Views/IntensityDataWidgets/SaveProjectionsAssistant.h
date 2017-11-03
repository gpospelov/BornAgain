// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/IntensityDataWidgets/SaveProjectionsAssistant.h
//! @brief     Defines class SaveProjectionsAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef SAVEPROJECTIONSASSISTANT_H
#define SAVEPROJECTIONSASSISTANT_H

#include "WinDllMacros.h"
#include <QString>

class IntensityDataItem;

//! Assistant class which save all projections of IndensityDataItem into ASCII file.

class BA_CORE_API_ SaveProjectionsAssistant
{
public:
    void saveProjections(IntensityDataItem* item);
};

#endif  // SAVEPROJECTIONSASSISTANT_H
