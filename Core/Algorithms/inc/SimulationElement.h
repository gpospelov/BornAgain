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

//! @class SimulationElement
//! @ingroup simulation
//! @brief Data stucture containing both input and output of a single detector cell.

class BA_CORE_API_ SimulationElement
{
public:
    SimulationElement();
    SimulationElement(double wavelength, double alpha_i, double phi_i, double alpha_min,
                      double alpha_max, double phi_min, double phi_max);
    SimulationElement(const SimulationElement &other);
    SimulationElement &operator=(const SimulationElement &other);

    ~SimulationElement()
    {
    }

#ifndef GCCXML_SKIP_THIS
    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd& polarization)
    {
        m_polarization = polarization;
    }

    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const
    {
        return m_polarization;
    }

    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& polarization_operator)
    {
        m_analyzer_operator = polarization_operator;
    }

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const
    {
        return m_analyzer_operator;
    }
#endif

    double getWavelength() const
    {
        return m_wavelength;
    }
    double getAlphaI() const
    {
        return m_alpha_i;
    }
    double getPhiI() const
    {
        return m_phi_i;
    }
    double getAlphaMin() const
    {
        return m_alpha_min;
    }
    double getAlphaMax() const
    {
        return m_alpha_max;
    }
    double getAlphaMean() const
    {
        return (m_alpha_min + m_alpha_max)/2.0;
    }
    double getPhiMin() const
    {
        return m_phi_min;
    }
    double getPhiMax() const
    {
        return m_phi_max;
    }
    double getPhiMean() const
    {
        return (m_phi_min + m_phi_max)/2.0;
    }
    void setIntensity(double intensity)
    {
        m_intensity = intensity;
    }
    void addIntensity(double intensity)
    {
        m_intensity += intensity;
    }
    double getIntensity() const
    {
        return m_intensity;
    }
    kvector_t getKI() const;
    kvector_t getMeanKF() const;
    cvector_t getMeanQ() const;

private:
    //! swap function
    void swapContent(SimulationElement &other);

    //! initialize polarization matrices
    void initPolarization();

    double m_wavelength, m_alpha_i, m_phi_i;             //!< wavelength and angles of beam
    double m_alpha_min, m_alpha_max, m_phi_min, m_phi_max; //!< detector cell angles
    double m_intensity;  //!< simulated intensity for detector cell
#ifndef GCCXML_SKIP_THIS
    Eigen::Matrix2cd m_polarization;      //!< polarization density matrix
    Eigen::Matrix2cd m_analyzer_operator; //!< polarization analyzer operator
#endif
};

//! Add element vector to element vector with weight
void AddElementsWithWeight(std::vector<SimulationElement>::const_iterator first,
                           std::vector<SimulationElement>::const_iterator last,
                           std::vector<SimulationElement>::iterator result,
                           double weight);

//! Set all element intensities to given value
void setAllElementIntensities(std::vector<SimulationElement>::iterator first,
                              std::vector<SimulationElement>::iterator last, double intensity);



#endif /* SIMULATIONELEMENT_H_ */
