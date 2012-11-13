#ifndef DWBADIFFUSEREFLECTION_H
#define DWBADIFFUSEREFLECTION_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DWBADiffuseReflection.h
//! @brief  Definition of DWBADiffuseReflection class for multi-layers
//! @author Scientific Computing Group at FRM II
//! @date   02.05.2012

#include "ISimulation.h"
#include "Units.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"


//- -------------------------------------------------------------------
//! @class DWBADiffuseReflection
//! @brief Calculation of diffuse (aka off-specular) reflection from multilayers.
//- -------------------------------------------------------------------
class DWBADiffuseReflection : public ISimulation
{
public:
    DWBADiffuseReflection();

    void execute(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf);

    void setSample(const MultiLayer &sample) {m_sample = &sample; }

    double getDiffuseAutocorr() const { return m_diffuse_autocorr; }

    double getDiffuseCrosscorr() const { return m_diffuse_crosscorr; }

    void setKvectors(const kvector_t &ki, const kvector_t &kf);
private:
    void diffuse_autocorr();

    void diffuse_crosscorr();

    complex_t get_refractive_term(int ilayer);

    complex_t get_sum4terms(int ilayer);

    const MultiLayer *m_sample;
    OpticalFresnel::MultiLayerCoeff_t m_fcoeff_i;
    OpticalFresnel::MultiLayerCoeff_t m_fcoeff_f;
    double m_diffuse_autocorr;
    double m_diffuse_crosscorr;

    kvector_t m_ki;
    kvector_t m_kf;
    kvector_t m_q;
    double m_qz1;
    double m_qz2;
    double m_qz3;
    double m_qz4;
};

#endif // DWBADIFFUSEREFLECTION_H
