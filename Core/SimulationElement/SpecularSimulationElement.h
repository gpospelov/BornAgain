// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SimulationElement/SpecularSimulationElement.h
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
#include "Vectors3D.h"
#include "PolarizationHandler.h"
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

    //! Assigns PolarizationHandler.
    void setPolarizationHandler(const PolarizationHandler& handler)
    {
        m_polarization = handler;
    }

    //! Returns assigned PolarizationHandler.
    const PolarizationHandler& polarizationHandler() const
    {
        return m_polarization;
    }

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

    PolarizationHandler m_polarization;
    double m_wavelength, m_alpha_i;  //!< the wavelength and the incident angle of the beam
    double m_intensity;                      //!< simulated intensity for detector cell

    // this unique_ptr is also used as a flag to indicate if this is the specular pixel
    // TODO: remove this when we have a simulation type that generates intensity as a function
    //       of depth and inclination angle (it becomes a bool flag then)
    std::unique_ptr<SpecularData> m_specular_data;
};

#endif /* SPECULARSIMULATIONELEMENT_H_ */
