// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/IsGISAXSDetector.h
//! @brief     Declares class IsGISAXSDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISGISAXSDETECTOR_H_
#define ISGISAXSDETECTOR_H_

#include "SphericalDetector.h"

//! @class IsGISAXSDetector
//! @ingroup simulation
//! @brief A spherical detector used for validation with IsGISAXS results.

class BA_CORE_API_ IsGISAXSDetector : public SphericalDetector
{
public:
    IsGISAXSDetector();
    IsGISAXSDetector(size_t n_phi, double phi_min, double phi_max,
                      size_t n_alpha, double alpha_min, double alpha_max);

    IsGISAXSDetector(const IsGISAXSDetector &other);
    IsGISAXSDetector &operator=(const IsGISAXSDetector &other);

    virtual IsGISAXSDetector* clone() const;

    virtual ~IsGISAXSDetector() {}

protected:
    virtual void print(std::ostream &ostr) const;

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const;
};

#endif /* ISGISAXSDETECTOR_H_ */
