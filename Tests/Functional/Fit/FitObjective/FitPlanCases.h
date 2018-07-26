// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlanCases.h
//! @brief     Defines collection of FitPlanCases classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITPLANCASES_H
#define FITPLANCASES_H

#include "FitPlan.h"

//! Two parameter fit: cylinders in BA with mini GISAS simulation.

class CylindersInBAPlan : public FitPlan
{
public:
    CylindersInBAPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Large tolerance on expected parameter values to help stocastic minimizers to converge fatser.

class CylindersInBAEasyPlan : public FitPlan
{
public:
    CylindersInBAEasyPlan();
};

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Residual like objective function is used

class CylindersInBAResidualPlan : public FitPlan
{
public:
    CylindersInBAResidualPlan();
};

#endif  //  FITPLANCASES_H


