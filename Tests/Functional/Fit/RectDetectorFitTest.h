// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/RectDetectorFitTest.h
//! @brief     Defines class RectDetectorFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef RECTDETECTORFITTEST_H
#define RECTDETECTORFITTEST_H

#include "IMinimizerTest.h"


//! @class RectDetectorFitTest
//! @ingroup standard_samples
//! @brief Fit of simulation with rectangular detector. The detector is cropped, masks are applied.

class RectDetectorFitTest : public IMinimizerTest
{
public:
    RectDetectorFitTest();

protected:
    std::unique_ptr<Simulation> createSimulation() override;
    std::unique_ptr<OutputData<double>> createOutputData(const Simulation* simulation) override;
};

#endif // RECTDETECTORFITTEST_H
