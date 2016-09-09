// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MinimizerItemCatalogue.h
//! @brief     Defines MinimizerItemCatalogue class
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

#include "ComboProperty.h"

class MinimizerItem;

//! The MinimizerItemCatalogue class is a static class to provide MinimizerItem
//! with the list of available minimizers/algorithms.

class BA_CORE_API_ MinimizerItemCatalogue {
public:
    static ComboProperty algorithmCombo(const QString &minimizerType);

private:
    static QStringList algorithmNames(const QString &minimizerType);
    static QStringList algorithmDescriptions(const QString &minimizerType);
};

#endif // MINIMIZERITEMCATALOGUE_H
