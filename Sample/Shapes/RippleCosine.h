//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Sample/Shapes/RippleCosine.h
//! @brief     Defines class RippleCosine.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SHAPES_RIPPLECOSINE_H
#define BORNAGAIN_SAMPLE_SHAPES_RIPPLECOSINE_H

#include "Sample/Shapes/IShape3D.h"

class RippleCosine : public IShape3D {
public:
    RippleCosine(double length, double width, double height);
    ~RippleCosine();
};

#endif // BORNAGAIN_SAMPLE_SHAPES_RIPPLECOSINE_H
#endif // USER_API
