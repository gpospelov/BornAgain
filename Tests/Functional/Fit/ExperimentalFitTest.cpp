// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/ExperimentalFitTest.cpp
//! @brief     Implements class ExperimentalFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ExperimentalFitTest.h"
#include "GISASSimulation.h"
#include "Histogram2D.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "Units.h"

ExperimentalFitTest::ExperimentalFitTest()
    : IMinimizerTest("Minuit2", "Migrad")
{
}
