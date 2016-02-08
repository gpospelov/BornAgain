// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SimulationElement.h
//! @brief     Defines class SimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONELEMENT_H_
#define SIMULATIONELEMENT_H_

#include "Types.h"
#include "IParameterized.h"
#include "EigenCore.h"
#include "IPixelMap.h"

#include <boost/scoped_ptr.hpp>

//! @class SimulationElement
//! @ingroup simulation
//! @brief Data stucture containing both input and output of a single detector cell.

class BA_CORE_API_ SimulationElement
{
public:
    SimulationElement(double wavelength, double alpha_i, double phi_i,
                      const IPixelMap* pixelmap);
    SimulationElement(const SimulationElement &other);
    SimulationElement &operator=(const SimulationElement &other);

    //! Construct SimulationElement from other element and restrict k_f to specific value in
    //! the original detector pixel
    SimulationElement(const SimulationElement &other, double x, double y);

    ~SimulationElement() {}

#ifndef GCCXML_SKIP_THIS
    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd& polarization);

    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const;

    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& polarization_operator);

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const;
#endif

    double getWavelength() const;
    double getAlphaI() const;
    double getPhiI() const;
    double getAlphaMean() const;
    double getPhiMean() const;
    void setIntensity(double intensity);
    void addIntensity(double intensity);
    double getIntensity() const;
    kvector_t getKI() const;
    kvector_t getMeanKF() const;
    kvector_t getMeanQ() const;
    kvector_t getQ(double x, double y) const;

    kvector_t getK(double x, double y) const;

    double getIntegrationFactor(double x, double y) const;

    double getSolidAngle() const;

    //! get alpha for given detector pixel coordinates
    double getAlpha(double x, double y) const;

    //! get phi for given detector pixel coordinates
    double getPhi(double x, double y) const;

private:
    //! swap function
    void swapContent(SimulationElement &other);

    //! initialize polarization matrices
    void initPolarization();

    double m_wavelength, m_alpha_i, m_phi_i;             //!< wavelength and angles of beam
    double m_intensity;  //!< simulated intensity for detector cell
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_polarization;      //!< polarization density matrix
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
    boost::scoped_ptr<IPixelMap> mP_pixel_map;
};

#ifndef GCCXML_SKIP_THIS
inline void SimulationElement::setPolarization(const Eigen::Matrix2cd &polarization)
{
    m_polarization = polarization;
}

inline Eigen::Matrix2cd SimulationElement::getPolarization() const
{
    return m_polarization;
}

inline void SimulationElement::setAnalyzerOperator(const Eigen::Matrix2cd &polarization_operator)
{
    m_analyzer_operator = polarization_operator;
}

inline Eigen::Matrix2cd SimulationElement::getAnalyzerOperator() const
{
    return m_analyzer_operator;
}
#endif

inline double SimulationElement::getWavelength() const
{
    return m_wavelength;
}

inline double SimulationElement::getAlphaI() const
{
    return m_alpha_i;
}

inline double SimulationElement::getPhiI() const
{
    return m_phi_i;
}

inline double SimulationElement::getAlphaMean() const
{
    return getAlpha(0.5, 0.5);
}

inline double SimulationElement::getPhiMean() const
{
    return getPhi(0.5, 0.5);
}

inline void SimulationElement::setIntensity(double intensity)
{
    m_intensity = intensity;
}

inline void SimulationElement::addIntensity(double intensity)
{
    m_intensity += intensity;
}

inline double SimulationElement::getIntensity() const
{
    return m_intensity;
}

inline kvector_t SimulationElement::getK(double x, double y) const {
    return mP_pixel_map->getK(x, y, m_wavelength);
}

inline double SimulationElement::getIntegrationFactor(double x, double y) const {
    return mP_pixel_map->getIntegrationFactor(x, y);
}

inline double SimulationElement::getSolidAngle() const {
    return mP_pixel_map->getSolidAngle();
}

//! Add element vector to element vector with weight
void AddElementsWithWeight(std::vector<SimulationElement>::const_iterator first,
                           std::vector<SimulationElement>::const_iterator last,
                           std::vector<SimulationElement>::iterator result,
                           double weight);

//! Set all element intensities to given value
void setAllElementIntensities(std::vector<SimulationElement>::iterator first,
                              std::vector<SimulationElement>::iterator last, double intensity);



#endif /* SIMULATIONELEMENT_H_ */
