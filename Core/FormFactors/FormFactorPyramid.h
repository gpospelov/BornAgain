// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/FormFactorPyramid.h
//! @brief     Declares class FormFactorPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPYRAMID_H
#define FORMFACTORPYRAMID_H

#include "FormFactorPolyhedron.h"

//! @class FormFactorPyramid
//! @ingroup formfactors
//! @brief The formfactor of a cone6.
class BA_CORE_API_ FormFactorPyramid : public FormFactorPolyhedron
{
public:
    //! @brief Pyramid constructor
    //! @param length of one side of Pyramid's square base
    //! @param height of Pyramid
    //! @param angle in radians between base and facet
    FormFactorPyramid(double length, double height, double alpha);

    static std::vector<PolyhedralFace> polyhedral_faces(
        double length, double height,  double alpha);

    virtual FormFactorPyramid* clone() const final;
    virtual void accept(ISampleVisitor *visitor) const final;

    double getHeight() const { return m_height; }
    double getLength() const { return m_length; }
    double getAlpha() const { return m_alpha; }

private:
    virtual bool check_initialization() const final;
    virtual void init_parameters() final;

    double m_length;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORPYRAMID_H
