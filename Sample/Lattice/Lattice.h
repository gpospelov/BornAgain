// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Lattice/Lattice.h
//! @brief     Defines class Lattice.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_SAMPLE_LATTICE_LATTICE_H
#define BORNAGAIN_SAMPLE_LATTICE_LATTICE_H

#include "Param/Node/INode.h"
#include <memory>
#include <vector>

class ISelectionRule;
class Transform3D;

//! A Bravais lattice, characterized by three basis vectors, and optionally an ISelectionRule.

//! @ingroup samples

class Lattice : public INode
{
public:
    Lattice();
    Lattice(const kvector_t a1, const kvector_t a2, const kvector_t a3);
    Lattice(const Lattice& lattice);
    ~Lattice() override;
    Lattice& operator=(const Lattice&) = delete;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Creates transformed lattice
    Lattice transformed(const Transform3D& transform) const;

    //! Initializes cached data
    void initialize();

    //! Returns basis vector a
    kvector_t getBasisVectorA() const { return m_a; }

    //! Returns basis vector b
    kvector_t getBasisVectorB() const { return m_b; }

    //! Returns basis vector c
    kvector_t getBasisVectorC() const { return m_c; }

    //! Returns normalized direction corresponding to the given Miller indices
    kvector_t getMillerDirection(double h, double k, double l) const;

    //! Returns the volume of the unit cell
    double volume() const;

    //! Returns the reciprocal basis vectors
    void getReciprocalLatticeBasis(kvector_t& b1, kvector_t& b2, kvector_t& b3) const;

    //! Returns the nearest reciprocal lattice point from a given vector
    ivector_t getNearestReciprocalLatticeVectorCoordinates(const kvector_t vector_in) const;

    //! Computes a list of reciprocal lattice vectors within a specified distance of a given vector
    std::vector<kvector_t> reciprocalLatticeVectorsWithinRadius(const kvector_t input_vector,
                                                                double radius) const;

    //! Sets a selection rule for the reciprocal vectors
    void setSelectionRule(const ISelectionRule& p_selection_rule);


private:
    void onChange() override;

    void computeReciprocalVectors() const;

    kvector_t m_a, m_b, m_c;            //!< Basis vectors in real space
    std::unique_ptr<ISelectionRule> m_selection_rule;

    mutable kvector_t m_ra, m_rb, m_rc; //!< Cache of basis vectors in reciprocal space
};

#endif // BORNAGAIN_SAMPLE_LATTICE_LATTICE_H
