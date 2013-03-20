// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/OpticalFresnel.h
//! @brief     Defines class OpticalFresnel.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef OPTICALFRESNEL_H
#define OPTICALFRESNEL_H

#include <vector>
#include "Types.h"
#include "ISimulation.h"
#include "MultiLayer.h"

//! Optical fresnel coefficients.

class OpticalFresnel : public ISimulation
{
public:
    OpticalFresnel();

    //! reflection/transmission fresnel coefficients
    class FresnelCoeff {
    public:
        FresnelCoeff() : kz(0), r(0), t(0), rb(0), tb(0), X(0), R(0), T(0) {}
        ~FresnelCoeff() {}
        // A - amplitude of initial wave, R, T - amplitudes of reflected and transmitted waves
        complex_t kz; // z-component of the wavevector in given layer
        complex_t r;  // r = R/A - Fresnel reflection coefficient
        complex_t t;  // t = T/A - Fresnel transmission coefficient
        complex_t rb;  // r = R/A - Fresnel reflection coefficient
        complex_t tb;  // t = T/A - Fresnel transmission coefficient
        complex_t X; //  ratio of amplitudes R/T of the outgoing to the incoming waves in layer
        complex_t R; //  amplitude of the reflected wave in layer
        complex_t T; //  amplitude of the transmitted wave in layer

        //! operator is necessary to make pyplusplus/boost happy during exposing of FresnelCoeff to python using boost::vector_indexing_suite
        bool operator==(FresnelCoeff const &other) const;
    };

    //! collection of fresnel coefficients for multi layer
    class MultiLayerCoeff
    {
    public:
        inline FresnelCoeff &operator[](size_t i) { return m_data[i]; }
        inline const FresnelCoeff &operator[](size_t i) const { return m_data[i]; }
        inline size_t size() const { return m_data.size(); }
        inline void clear() { m_data.clear(); }
        inline void resize(size_t size) { m_data.resize(size); }
    private:
        std::vector<FresnelCoeff > m_data;
    };

    //typedef std::vector<FresnelCoeff > MultiLayerCoeff_t; // set of Fresnel coefficients for set of layers, [nlayer]
    typedef MultiLayerCoeff MultiLayerCoeff_t; // set of Fresnel coefficients for set of layers, [nlayer]

    //! calculate fresnel coefficients for given multi layer and kvector
    void execute(const MultiLayer &sample, const kvector_t &k, MultiLayerCoeff_t &coeff);

private:
    bool m_use_roughness;

    void calculateKZ(const MultiLayer &sample, const kvector_t &k, MultiLayerCoeff_t &coeff) const;
    void calculateFresnelCoefficients(MultiLayerCoeff_t &coeff) const;
    void calculateFresnelCoefficientsWithRoughness(const MultiLayer &sample, MultiLayerCoeff_t &coeff) const;
    void calculateX(const MultiLayer &sample, MultiLayerCoeff_t &coeff) const;
    void calculateX2(const MultiLayer &sample, MultiLayerCoeff_t &coeff) const;
    void calculateRT(const MultiLayer &sample, MultiLayerCoeff_t &coeff) const;
    void calculateRT2(const MultiLayer &sample, MultiLayerCoeff_t &coeff) const;
};

#endif // OPTICALFRESNEL_H
