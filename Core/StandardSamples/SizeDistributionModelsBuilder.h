// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SizeDistributionModelsBuilder.h
//! @brief     Declares various sample builder classes to test DA, LMA, SSCA approximations
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIZEDISTRIBUTIONMODELSBUILDER_H
#define SIZEDISTRIBUTIONMODELSBUILDER_H

#include "ISampleBuilder.h"

//! @class SizeDistributionDAModelBuilder
//! @ingroup standard_samples
//! @brief Creates the sample demonstrating size distribution model in decoupling approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationDA.py

class BA_CORE_API_ SizeDistributionDAModelBuilder : public ISampleBuilder
{
public:
    SizeDistributionDAModelBuilder(){}
    ISample *buildSample() const;
};

//! @class SizeDistributionLMAModelBuilder
//! @ingroup standard_samples
//! @brief Creates the sample demonstrating size distribution model in local monodisperse
//! approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py

class BA_CORE_API_ SizeDistributionLMAModelBuilder : public ISampleBuilder
{
public:
    SizeDistributionLMAModelBuilder(){}
    ISample *buildSample() const;
};

//! @class SizeDistributionSSCAModelBuilder
//! @ingroup standard_samples
//! @brief Creates the sample demonstrating size distribution model in size space coupling
//! approximation.
//! Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py

class BA_CORE_API_ SizeDistributionSSCAModelBuilder : public ISampleBuilder
{
public:
    SizeDistributionSSCAModelBuilder(){}
    ISample *buildSample() const;
};

//! @class CylindersInSSCABuilder
//! @ingroup standard_samples
//! @brief Builds sample: size spacing correlation approximation
//! (IsGISAXS example #15)

class BA_CORE_API_ CylindersInSSCABuilder : public ISampleBuilder
{
public:
    CylindersInSSCABuilder(){}
    ISample *buildSample() const;
};


#endif // SIZEDISTRIBUTIONMODELSBUILDER_H
