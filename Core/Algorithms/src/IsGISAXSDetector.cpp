// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/src/IsGISAXSDetector.cpp
//! @brief     Implements class IsGISAXSDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IsGISAXSDetector.h"
#include "CustomBinAxis.h"


IsGISAXSDetector::IsGISAXSDetector()
{
    setName("IsGISAXSDetector");
    init_parameters();
}

IsGISAXSDetector::IsGISAXSDetector(const IsGISAXSDetector &other)
    : SphericalDetector(other)
{
    setName("IsGISAXSDetector");
    init_parameters();
}

IsGISAXSDetector &IsGISAXSDetector::operator=(const IsGISAXSDetector &other)
{
    if (this != &other) {
        IsGISAXSDetector tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

IsGISAXSDetector *IsGISAXSDetector::clone() const
{
    return new IsGISAXSDetector(*this);
}

void IsGISAXSDetector::print(std::ostream &ostr) const
{
    ostr << "IsGISAXSDetector: '" << getName() << "' " << m_parameters;
    for (size_t i = 0; i < m_axes.size(); ++i) {
        ostr << "    IAxis:" << *m_axes[i] << std::endl;
    }
}

IAxis *IsGISAXSDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min) {
        throw LogicErrorException(
            "IsGISAXSDetector::createAxis() -> Error! max <= min");
    }
    if (n_bins == 0) {
        throw LogicErrorException(
            "IsGISAXSDetector::createAxis() -> Error! Number n_bins can't be zero.");
    }    return new CustomBinAxis(getAxisName(index), n_bins, min, max);
}
