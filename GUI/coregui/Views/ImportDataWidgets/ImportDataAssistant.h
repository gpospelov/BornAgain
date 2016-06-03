// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/Views/ImportDataWidgets/ImportDataAssistant.h
//! @brief     Declares class ImportDataAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef IMPORTDATAASSISTANT_H
#define IMPORTDATAASSISTANT_H

#include "WinDllMacros.h"

template <class T> class OutputData;

//! The ImportDataAssistant class provides utility methods to import data files.

class BA_CORE_API_ ImportDataAssistant {
public:

    OutputData<double> *importData(class QString &baseNameOfLoadedFile);


};

#endif
