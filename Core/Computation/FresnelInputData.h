// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/FresnelInputData.h
//! @brief     Defines class FresnelInputData.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FRESNELINPUTDATA_H
#define FRESNELINPUTDATA_H

class MultiLayer;
class SimulationOptions;

//! Data structure that contains all the necessary data for calculating the Fresnel coefficients.
//!
//! @ingroup algorithms_internal

class FresnelInputData
{
public:
    FresnelInputData(const MultiLayer& sample, const SimulationOptions& options);
    ~FresnelInputData();

private:
};

#endif // FRESNELINPUTDATA_H
