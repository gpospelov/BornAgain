// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IFormFactorPrism.cpp
//! @brief     Implements class IFormFactorPrism.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

//! The mathematics implemented here is described in full detail in a paper
//! by Joachim Wuttke, entitled
//! "Form factor (Fourier shape transform) of polygon and polyhedron."

#include "Core/HardParticle/IFormFactorPrism.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Tools/MathFunctions.h"
#include <iomanip>
#include <stdexcept> // need overlooked by g++ 5.4

namespace
{
const double eps = 2e-16;
} // namespace


IFormFactorPrism::IFormFactorPrism(const NodeMeta& meta,
                                                   const std::vector<double>& PValues)
    : IFormFactorBorn(meta, PValues)
{
}

void IFormFactorPrism::setPrism(bool symmetry_Ci, const std::vector<kvector_t>& vertices)
{
    m_vertices.clear();
    for (const kvector_t& vertex : vertices) {
        m_vertices.push_back(vertex);
        m_vertices.push_back(vertex + kvector_t{0, 0, height()});
    }

    try {
        m_base = std::unique_ptr<PolyhedralFace>(new PolyhedralFace(vertices, symmetry_Ci));
    } catch (std::invalid_argument& e) {
        throw std::invalid_argument("Invalid parameterization of " + getName() + ": " + e.what());
    } catch (std::logic_error& e) {
        throw std::logic_error("Bug in " + getName() + ": " + e.what()
                               + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error("Unexpected exception in " + getName() + ": " + e.what()
                                 + " [please report to the maintainers]");
    }
}

double IFormFactorPrism::bottomZ(const IRotation& rotation) const
{
    return BottomZ(m_vertices, rotation);
}

double IFormFactorPrism::topZ(const IRotation& rotation) const
{
    return TopZ(m_vertices, rotation);
}

//! Returns the volume of this prism.
double IFormFactorPrism::volume() const
{
    return height() * m_base->area();
}

//! Returns the form factor F(q) of this polyhedron, respecting the offset height/2.

complex_t IFormFactorPrism::evaluate_for_q(cvector_t q) const
{
    try {
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.maxOrder = 0;
        diagnosis.nExpandedFaces = 0;
#endif
        cvector_t qxy(q.x(), q.y(), 0.);
        return height() * exp_I(height() / 2 * q.z()) * MathFunctions::sinc(height() / 2 * q.z())
               * m_base->ff_2D(qxy);
    } catch (std::logic_error& e) {
        throw std::logic_error("Bug in " + getName() + ": " + e.what()
                               + " [please report to the maintainers]");
    } catch (std::runtime_error& e) {
        throw std::runtime_error("Numeric computation failed in " + getName() + ": " + e.what()
                                 + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error("Unexpected exception in " + getName() + ": " + e.what()
                                 + " [please report to the maintainers]");
    }
}

//**************************************************************************************************
//  FormFactorPolygonalSurface implementation
//**************************************************************************************************

FormFactorPolygonalSurface::FormFactorPolygonalSurface(const NodeMeta& meta,
                                                       const std::vector<double>& PValues)
    : IFormFactorBorn(meta, PValues)
{
}

complex_t FormFactorPolygonalSurface::evaluate_for_q(cvector_t q) const
{
    try {
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis.maxOrder = 0;
        diagnosis.nExpandedFaces = 0;
#endif
        return m_base->ff(q, false);
    } catch (std::logic_error& e) {
        throw std::logic_error("Bug in " + getName() + ": " + e.what()
                               + " [please report to the maintainers]");
    } catch (std::runtime_error& e) {
        throw std::runtime_error("Numeric computation failed in " + getName() + ": " + e.what()
                                 + " [please report to the maintainers]");
    } catch (std::exception& e) {
        throw std::runtime_error("Unexpected exception in " + getName() + ": " + e.what()
                                 + " [please report to the maintainers]");
    }
}
