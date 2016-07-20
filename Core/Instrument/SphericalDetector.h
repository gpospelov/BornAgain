// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SphericalDetector.h
//! @brief     Declares class SphericalDetector.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SPHERICALDETECTOR_H
#define SPHERICALDETECTOR_H

#include "IDetector2D.h" // inheriting from
#include "IPixelMap.h" // inheriting from

//! @class SphericalDetector
//! @ingroup simulation
//! @brief A spherical detector with axes and resolution function.

class BA_CORE_API_ SphericalDetector : public IDetector2D
{
public:
    SphericalDetector();

    //! Spherical detector constructor using angle ranges
    //! @param n_phi number of phi-axis bins
    //! @param phi_min low edge of first phi-bin
    //! @param phi_max upper edge of last phi-bin
    //! @param n_alpha number of alpha-axis bins
    //! @param alpha_min low edge of first alpha-bin
    //! @param alpha_max upper edge of last alpha-bin
    SphericalDetector(size_t n_phi, double phi_min, double phi_max,
                      size_t n_alpha, double alpha_min, double alpha_max);

    SphericalDetector(const SphericalDetector &other);
    SphericalDetector &operator=(const SphericalDetector &other);

    virtual SphericalDetector* clone() const;

    virtual ~SphericalDetector() {}

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool* external_pool,
                                                    int copy_number = -1) const;

    //! Returns detector map in given axes units
    virtual OutputData<double> *createDetectorMap(const Beam& beam, EAxesUnits units_type) const;

    //! returns vector of valid axes units
    virtual std::vector<EAxesUnits> getValidAxesUnits() const;

    //! return default axes units
    virtual EAxesUnits getDefaultAxesUnits() const;

protected:
    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const;

    virtual void print(std::ostream& ostr) const;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const;

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const;
};

class AngularPixelMap : public IPixelMap
{
public:
    AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin);
    virtual ~AngularPixelMap() {}

    virtual AngularPixelMap* clone() const;
    virtual AngularPixelMap* createZeroSizeMap(double x, double y) const;
    virtual kvector_t getK(double x, double y, double wavelength) const;
    virtual double getIntegrationFactor(double x, double y) const;
    virtual double getSolidAngle() const;
private:
    double m_alpha, m_phi;
    double m_dalpha, m_dphi;
    double m_solid_angle;
};

#endif // SPHERICALDETECTOR_H
