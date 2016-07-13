// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/MatrixSpecularInfoMap.h
//! @brief     Declares class MatrixSpecularInfoMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATRIXSPECULARINFOMAP_H
#define MATRIXSPECULARINFOMAP_H

#include "ISpecularInfoMap.h"
#include "MatrixRTCoefficients.h"
#include "MultiLayer.h"
#include "Utils.h"

#include <memory>


//! @class MatrixSpecularInfoMap
//! @ingroup algorithms_internal
//! @brief Implementation of ISpecularInfoMap for matrix valued reflection/
//! transmission coefficients

class BA_CORE_API_ MatrixSpecularInfoMap : public ISpecularInfoMap
{
public:
    MatrixSpecularInfoMap(const MultiLayer *multilayer, int layer);
    virtual ~MatrixSpecularInfoMap() {}

    virtual MatrixSpecularInfoMap* clone() const;

    //! Retrieves the amplitude coefficients for the given angles
    virtual const MatrixRTCoefficients *getOutCoefficients(double alpha_f, double phi_f,
                                                           double wavelength) const;

    //! Retrieves the amplitude coefficients for the given angles
    virtual const MatrixRTCoefficients *getInCoefficients(double alpha_i, double phi_i,
                                                          double wavelength) const;
private:
    std::unique_ptr<MultiLayer> mP_multilayer;
    std::unique_ptr<MultiLayer> mP_inverted_multilayer;
    const int m_layer;
};


#endif // MATRIXSPECULARINFOMAP_H
