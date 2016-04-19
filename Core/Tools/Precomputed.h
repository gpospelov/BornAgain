// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/Precomputed.h
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

//! This class contains precomputed constants.

//! So far, the only contents is factorial, used in the polyhedral form factor.

class Precomputed
{
public:
    Precomputed(); //!< Constructor, precomputes everything.
    std::vector<double> factorial; //!< factorial[k] = k! for k=0,1,...,170 (for IEEE double).
};

//! This singleton interface class gives access to the precomputed constants.

class IPrecomputed: public ISingleton<Precomputed>
{
};
