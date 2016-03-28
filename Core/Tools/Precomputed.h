// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Precomputed.h
//! @brief     Defines classes Precomputed, IPrecomputed, providing precomputed constants
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <vector>
#include "ISingleton.h"

class Precomputed
{
public:
    Precomputed();
    std::vector<double> factorial;
};

class IPrecomputed: public ISingleton<Precomputed>
{
};
