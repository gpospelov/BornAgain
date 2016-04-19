// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/PyGenTools.h
//! @brief     Defines PyGenTools namespace.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYSCRIPTTOOLS_H
#define PYSCRIPTTOOLS_H

#include "PyGenVisitor.h"
#include "Types.h"

class IDistribution1D;
class GISASSimulation;

namespace Geometry {
class IShape2D;
}

namespace PyGenTools {
    BA_CORE_API_ std::string genPyScript(GISASSimulation *simulation);
    BA_CORE_API_ std::string printBool(double value);
    BA_CORE_API_ std::string printDouble(double input);
    BA_CORE_API_ std::string printNm(double input);
    BA_CORE_API_ std::string printScientificDouble(double input);
    BA_CORE_API_ std::string printDegrees(double input);
    BA_CORE_API_ bool isSquare(double length1, double length2, double angle);
    BA_CORE_API_ bool isHexagonal(double length1, double length2, double angle);
    BA_CORE_API_ bool testPyScript(GISASSimulation *simulation);
    BA_CORE_API_ std::string getRepresentation(const IDistribution1D *distribution);
    BA_CORE_API_ std::string getRepresentation(const std::string &indent, const Geometry::IShape2D *ishape, bool mask_value);
    BA_CORE_API_ std::string printKvector(const kvector_t value);

    BA_CORE_API_ bool isDefaultDirection(const kvector_t direction);


}

#endif // PYSCRIPTTOOLS_H
