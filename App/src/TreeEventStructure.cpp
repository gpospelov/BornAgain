// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TreeEventStructure.cpp
//! @brief     Implements TreeEventOutputData.clear(), TreeEventFitData.clear().
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TreeEventStructure.h"

//! Clear arrays and set parameters to zero.

void TreeEventOutputData::clear()
{
    nframe = 0;
    alpha_i = 0;
    phi_i = 0;
    nphi_f = 0;
    phi_f_min = 0;
    phi_f_max = 0;
    nalpha_f = 0;
    alpha_f_min = 0;
    alpha_f_max = 0;
    malpha = 0;
    mphi = 0;
    npR = 0;
    valpha_f.clear();
    vphi_f.clear();
    vi.clear();
}

//! Clear arrays and set parameters to zero.

void TreeEventFitData::clear()
{
    niter = 0;
    nstrategy = 0;
    real_data.clear();
    fit_data.clear();
    //diff.clear();
    axis0.clear();
    axis1.clear();
    chi2=0;
    parvalues.clear();
    parnames.clear();
    parfixed.clear();
}


