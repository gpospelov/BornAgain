// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/DecoratedFormFactor/FormFactorDecoratorMultiPositionFactor.h
//! @brief     Defines class FormFactorDecoratorMultiPositionFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORMULTIPOSITIONFACTOR_H
#define FORMFACTORDECORATORMULTIPOSITIONFACTOR_H

#include "IFormFactorDecorator.h"
#include "Vectors3D.h"

//! The formfactor for the same particle at different fixed positions.
//!
//! If several particle components are at the same position, use FormFactorWeighted.
//!
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorMultiPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorMultiPositionFactor(const IFormFactor& form_factor,
                                           const std::vector<kvector_t>& positions);

    FormFactorDecoratorMultiPositionFactor* clone() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    double getVolume() const final;
    double getRadialExtension() const final; //!< throws makes-no-sense exception

    complex_t evaluate(const WavevectorInfo& wavevectors) const final;

#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const final;
#endif

private:
    complex_t getPositionsFactor(const WavevectorInfo& wavevectors) const;
    std::vector<kvector_t> m_positions;
};

#endif // FORMFACTORDECORATORMULTIPOSITIONFACTOR_H
