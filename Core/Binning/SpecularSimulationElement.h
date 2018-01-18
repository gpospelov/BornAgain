// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/SpecularSimulationElement.h
//! @brief     Defines class SpecularSimulationElement.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARSIMULATIONELEMENT_H_
#define SPECULARSIMULATIONELEMENT_H_

#include "Complex.h"
#include "EigenCore.h"
#include "Vectors3D.h"
#include <memory>

class SpecularData;

//! Data stucture containing both input and output of a single image pixel
//! for specular simulation.
//! @ingroup simulation

class BA_CORE_API_ SpecularSimulationElement
{
public:
    SpecularSimulationElement(double wavelength, double alpha_i);
    SpecularSimulationElement(const SpecularSimulationElement& other);
    SpecularSimulationElement& operator=(const SpecularSimulationElement& other);

    SpecularSimulationElement(SpecularSimulationElement&& other) noexcept;

    ~SpecularSimulationElement();

#ifndef SWIG
    //! Sets the polarization density matrix (in spin basis along z-axis)
    void setPolarization(const Eigen::Matrix2cd& polarization) { m_polarization = polarization; }

    //! Gets the polarization density matrix (in spin basis along z-axis)
    Eigen::Matrix2cd getPolarization() const { return m_polarization; }

    //! Sets the polarization analyzer operator (in spin basis along z-axis)
    void setAnalyzerOperator(const Eigen::Matrix2cd& polarization_operator) {
        m_analyzer_operator = polarization_operator; }

    //! Gets the polarization analyzer operator (in spin basis along z-axis)
    Eigen::Matrix2cd getAnalyzerOperator() const { return m_analyzer_operator; }
#endif

    double getWavelength() const { return m_wavelength; }
    double getAlphaI() const { return m_alpha_i; }
    kvector_t getKi() const;
    void setIntensity(double intensity) { m_intensity = intensity; }
    void addIntensity(double intensity) { m_intensity += intensity; }
    double getIntensity() const { return m_intensity; }

    //! check if element corresponds to specular peak
    SpecularData* specularData() const { return m_specular_data.get(); }

    //! Turn on specular data
    void setSpecular(std::unique_ptr<SpecularData> specular_data);

private:
    void swapContent(SpecularSimulationElement& other);
    void initPolarization();

    double m_wavelength, m_alpha_i;  //!< the wavelength and the incident angle of the beam
    double m_intensity;                      //!< simulated intensity for detector cell
    Eigen::Matrix2cd m_polarization;         //!< polarization density matrix
    Eigen::Matrix2cd m_analyzer_operator;    //!< polarization analyzer operator

    // this unique_ptr is also used as a flag to indicate if this is the specular pixel
    // TODO: remove this when we have a simulation type that generates intensity as a function
    //       of depth and inclination angle (it becomes a bool flag then)
    std::unique_ptr<SpecularData> m_specular_data;
};

#endif /* SPECULARSIMULATIONELEMENT_H_ */
