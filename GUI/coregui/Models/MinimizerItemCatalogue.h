// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItemCatalogue.h
//! @brief     Declares MinimizerItemCatalogue class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERITEMCATALOGUE_H
#define MINIMIZERITEMCATALOGUE_H

#include "WinDllMacros.h"
#include "MinimizerLibrary.h"
#include "ComboProperty.h"
#include <QStringList>

class MinimizerItem;

//! The MinimizerItemCatalogue class is a static class to provide MinimizerItem
//! with the list of available minimizers/algorithms. It is a bridge class which
//! extract all necessary information from Core's MinimizerLibrary.

// --------------------------------------------------------------------------------
// FIXME, TODO class will be refactored simultaneosly with the MinimizerFactory and
// MinimizerLibrary from the domain (in Sprint32).
// --------------------------------------------------------------------------------

class BA_CORE_API_ MinimizerItemCatalogue {
public:
    static ComboProperty getAlgorithmCombo(const QString &minimizerType);

    static void domainMinimizerNames(const MinimizerItem *minimizer, std::string &domainName, std::string &domainAlgo);

private:
    static MinimizerLibrary::Catalogue m_catalogue;
};

#endif // MINIMIZERITEMCATALOGUE_H
