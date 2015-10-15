// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/RectangularDetector.h
//! @brief     Defines class RectangularDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGULARDETECTOR_H_
#define RECTANGULARDETECTOR_H_

#include "IDetector2D.h"
#include "IDetectorResolution.h"
#include "SafePointerVector.h"
#include "EigenCore.h"
#include "DetectorMask.h"
#include "SimulationElement.h"
#include "Beam.h"
#include "IPixelMap.h"

class RectPixelMap;

//! @class RectangularDetector
//! @ingroup simulation
//! @brief A rectangular plane detector with axes and resolution function.

class BA_CORE_API_ RectangularDetector : public IDetector2D
{
public:
    RectangularDetector();
    RectangularDetector(const RectangularDetector &other);
    RectangularDetector &operator=(const RectangularDetector &other);

    virtual RectangularDetector* clone() const;

    virtual ~RectangularDetector() {}

    //! Adds parameters from local pool to external pool and call recursion over direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

protected:
    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const;

    virtual void print(std::ostream &ostr) const;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}
};

class RectPixelMap : public IPixelMap
{
public:
    RectPixelMap(Bin1D alpha_bin, Bin1D phi_bin);
    virtual ~RectPixelMap() {}

    virtual RectPixelMap* clone() const;
    virtual RectPixelMap* createZeroSizeMap(double x, double y) const;
    virtual kvector_t getK(double x, double y, double wavelength) const;
    virtual double getIntegrationFactor(double x, double y) const;
    virtual double getSolidAngle() const;
private:
    double m_alpha, m_phi;
    double m_dalpha, m_dphi;
    double m_solid_angle;
};

#endif /* RECTANGULARDETECTOR_H_ */
