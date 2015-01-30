// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/inc/TestPolarizedDWBATerms.h
//! @brief     Defines class TestPolarizedDWBATerms.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef TESTPOLARIZEDDWBATERMS_H_
#define TESTPOLARIZEDDWBATERMS_H_

#include "IApplicationTest.h"
#include "OutputData.h"

#include <MultiLayer.h>

class FormFactorDWBAPol;
class FormFactorDWBA;
class LayerSpecularInfo;

//! TestPolarizedDWBATerms: compare the different terms in a matrix DWBA
//! calculation (without magnetic field) to the ones in a scalar DWBA
//! calculation.

class TestPolarizedDWBATerms : public IApplicationTest
{
public:
    TestPolarizedDWBATerms();
    virtual ~TestPolarizedDWBATerms() {
        delete mp_multilayer;
    }
    virtual void execute();
private:
    void initWavevectors();
    void initSpecularInfo();
    MultiLayer *mp_multilayer;
    FormFactorDWBAPol *mp_matrix_ff;
    FormFactorDWBA *mp_scalar_ff;
    cvector_t m_ki;
    Bin1DCVector m_kf_bin;
    LayerSpecularInfo *mp_specular_info;
    double m_alpha_i;
    double m_alpha_f;
};

#endif /* TESTPOLARIZEDDWBATERMS_H_ */
