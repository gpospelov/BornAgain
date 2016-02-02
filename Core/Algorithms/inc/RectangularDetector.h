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

    enum EDetectorArrangement {
        GENERIC,
        PERPENDICULAR_TO_SAMPLE,
        PERPENDICULAR_TO_DIRECT_BEAM,
        PERPENDICULAR_TO_REFLECTED_BEAM,
        PERPENDICULAR_TO_REFLECTED_BEAM_DPOS
    };

    //! Rectangular detector constructor
    //! @param nxbins Number of bins (pixels) in x-direction
    //! @param width Width of the detector in mm along x-direction
    //! @param nybins Number of bins (pixels) in y-direction
    //! @param height Height of the detector in mm along y-direction
    RectangularDetector(int nxbins, double width, int nybins, double height);

    RectangularDetector(const RectangularDetector &other);
    RectangularDetector &operator=(const RectangularDetector &other);

    virtual RectangularDetector* clone() const;

    virtual ~RectangularDetector() {}

    void init(const GISASSimulation *simulation);

    void setPosition(const kvector_t &normal_to_detector, double u0, double v0,
                     const kvector_t &direction = kvector_t(0.0, -1.0, 0.0));

    void setPerpendicularToSampleX(double distance, double u0, double v0);

    void setPerpendicularToDirectBeam(double distance, double u0, double v0);
    void setPerpendicularToReflectedBeam(double distance, double u0 = 0.0, double v0 = 0.0);
    void setDirectBeamPosition(double u0, double v0);

    //! Adds parameters from local pool to external pool and recursively calls its direct children.
    virtual std::string addParametersToExternalPool(std::string path, ParameterPool *external_pool,
                                                    int copy_number = -1) const;

    double getWidth() const;
    double getHeight() const;
    size_t getNbinsX() const;
    size_t getNbinsY() const;
    kvector_t getNormalVector() const;
    double getU0() const;
    double getV0() const;
    kvector_t getDirectionVector() const;
    double getDistance() const;
    double getDirectBeamU0() const;
    double getDirectBeamV0() const;
    EDetectorArrangement getDetectorArrangment() const;

    //! Returns detector map in given axes units
    virtual OutputData<double> *createDetectorMap(const Beam& beam, EAxesUnits units_type) const;

protected:
    //! Create an IPixelMap for the given OutputData object and index
    virtual IPixelMap* createPixelMap(size_t index) const;

    virtual void print(std::ostream &ostr) const;

    //! Registers some class members for later access via parameter pool.
    virtual void init_parameters() {}

    //! Generates an axis with correct name and default binning for given index
    virtual IAxis* createAxis(size_t index, size_t n_bins, double min, double max) const;

    //! Returns the name for the axis with given index
    virtual std::string getAxisName(size_t index) const;

    //! swap function
    void swapContent(RectangularDetector &other);
private:
    void setDistanceAndOffset(double distance, double u0, double v0);
    void initNormalVector(const kvector_t &central_k);
    void initUandV(double alpha_i);

    kvector_t m_normal_to_detector;
    double m_u0, m_v0; //!< position of normal vector hitting point in detector coordinates
    kvector_t m_direction; //!< direction vector of detector coordinate system
    double m_distance; //!< distance from sample origin to the detector plane
    double m_dbeam_u0, m_dbeam_v0; //!< position of direct beam in detector coordinates
    EDetectorArrangement m_detector_arrangement;
    kvector_t m_u_unit;
    kvector_t m_v_unit;
};

class RectPixelMap : public IPixelMap
{
public:
    RectPixelMap(kvector_t corner_pos, kvector_t width, kvector_t height);
    virtual ~RectPixelMap() {}

    virtual RectPixelMap* clone() const;
    virtual RectPixelMap* createZeroSizeMap(double x, double y) const;
    virtual kvector_t getK(double x, double y, double wavelength) const;
    virtual double getIntegrationFactor(double x, double y) const;
    virtual double getSolidAngle() const;
private:
    kvector_t normalizeLength(const kvector_t& direction, double length) const;
    double calculateSolidAngle() const;
    kvector_t m_corner_pos;
    kvector_t m_width;
    kvector_t m_height;
    double m_solid_angle;
    kvector_t m_normal;
};

#endif /* RECTANGULARDETECTOR_H_ */
