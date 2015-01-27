// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/PyGenTools.h
//! @brief     Defines PyGenTools namespace.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSCRIPTTOOLS_H
#define PYSCRIPTTOOLS_H
#include "Simulation.h"
#include "PyGenVisitor.h"


namespace PyGenTools {
    BA_CORE_API_ std::string genPyScript(Simulation *simulation);
    BA_CORE_API_ std::string printDouble(double input);
    BA_CORE_API_ bool isSquare(double length1, double length2, double angle);
    BA_CORE_API_ bool isHexagonal(double length1, double length2, double angle);
    BA_CORE_API_ bool testPyScript(Simulation *simulation);
}

#endif // PYSCRIPTTOOLS_H
