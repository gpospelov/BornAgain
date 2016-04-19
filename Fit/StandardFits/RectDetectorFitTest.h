// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardFits/RectDetectorFitTest.h
//! @brief     Declares class RectDetectorFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTDETECTORFITTEST_H
#define RECTDETECTORFITTEST_H

#include "IMinimizerFunctionalTest.h"
#include "OutputData.h"
#include <vector>

class IMinimizer;
class FitSuite;
class ISample;
class GISASSimulation;

//! @class RectDetectorFitTest
//! @ingroup standard_samples
//! @brief Fit of simulation with rectangular detector. The detector is cropped, masks are applied.

class BA_CORE_API_ RectDetectorFitTest : public IMinimizerFunctionalTest
{
public:
    RectDetectorFitTest();

protected:
    virtual std::unique_ptr<GISASSimulation> createSimulation();
    virtual std::unique_ptr<OutputData<double> > createOutputData(const GISASSimulation *simulation);

};

#endif
