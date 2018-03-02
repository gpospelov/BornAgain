// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/AnisoPyramid.h
//! @brief     Defines class AnisoPyramid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ANISOPYRAMID_H
#define ANISOPYRAMID_H

#include "IShape.h"

class AnisoPyramid : public IShape
{
public:
    AnisoPyramid(double length, double width, double height, double alpha);
    ~AnisoPyramid();
};

#endif // ANISOPYRAMID_H
