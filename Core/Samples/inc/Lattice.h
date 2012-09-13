#ifndef LATTICE_H_
#define LATTICE_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   Lattice.h
//! @brief  Definition of Lattice class
//! @author Scientific Computing Group at FRM II
//! @date   Jul 12, 2012

#include "Types.h"
#include "Coordinate3D.h"
#include "ISelectionRule.h"
#include "TRange.h"

#include <vector>

//- -------------------------------------------------------------------
//! @class Lattice
//! @brief Definition of Lattice with three basis vectors
//- -------------------------------------------------------------------
class Lattice
{
public:
    Lattice();
    Lattice(const kvector_t &a1, const kvector_t &a2, const kvector_t &a3);
    Lattice(const Lattice &lattice);
    ~Lattice();

    //! initialize cached data
    void initialize() const;

    //! get basis vector a
    kvector_t getBasisVectorA() const { return m_a1; }

    //! get basis vector b
    kvector_t getBasisVectorB() const { return m_a2; }

    //! get basis vector c
    kvector_t getBasisVectorC() const { return m_a3; }

    //! get the volume of the unit cell
    double getVolume() const;

    //! get the reciprocal basis vectors
    void getReciprocalLatticeBasis(kvector_t &b1, kvector_t &b2, kvector_t &b3) const;

    //! get the nearest lattice point from a given vector
    Coordinate3D<int> getNearestLatticeVectorCoordinates(const kvector_t &vector_in) const;

    //! get the nearest reciprocal lattice point from a given vector
    Coordinate3D<int> getNearestReciprocalLatticeVectorCoordinates(const kvector_t &vector_in) const;

    //! get a list of lattice vectors within a specified distance of a given vector
    std::vector<kvector_t> getLatticeVectorsWithinRadius(
            const kvector_t &input_vector, double radius) const;

    //! get a list of reciprocal lattice vectors within a specified distance of a given vector
    std::vector<kvector_t> getReciprocalLatticeVectorsWithinRadius(
            const kvector_t &input_vector, double radius) const;

    //! get a list of rotation angles within a specified range that hit a maximal set of small Bragg peaks
    std::vector<double> collectBraggAngles(size_t size, double max_radius, const TRange<double> &phi_range, const TRange<double> &z_range) const;

    //! set a selection rule for the reciprocal vectors
    void setSelectionRule(ISelectionRule *p_selection_rule) {
        if (mp_selection_rule != p_selection_rule) {
            delete mp_selection_rule;
            mp_selection_rule = p_selection_rule;
        }
    }

    static Lattice createFCCLattice(double a);

    static Lattice createTrigonalLattice(double a, double c);

private:
    Lattice &operator=(const Lattice &lattice);
    std::vector<kvector_t> getVectorsWithinRadius(const kvector_t &input_vector,
            const Coordinate3D<int> &nearest_coords, double radius,
            const kvector_t &v1, const kvector_t &v2, const kvector_t &v3,
            const kvector_t &rec1, const kvector_t &rec2, const kvector_t &rec3) const;
    void computeReciprocalVectors() const;
    void computeInverseLatticeVectors() const;
    void computeInverseReciprocalLatticeVectors() const;
    static void computeInverseVectors(const kvector_t &v1, const kvector_t &v2, const kvector_t &v3, kvector_t &o1, kvector_t &o2, kvector_t &o3);
    ISelectionRule *mp_selection_rule;
    kvector_t m_a1, m_a2, m_a3; //!< Basis vectors in real space
    mutable kvector_t m_b1, m_b2, m_b3; //!< Cache of basis vectors in reciprocal space
    mutable kvector_t m_amin1, m_amin2, m_amin3, m_bmin1, m_bmin2, m_bmin3; //!< Cache of inverse vectors for calculation of coordinates
    mutable bool m_cache_ok, m_is_zero; //!< Boolean indicating if the reciprocal vectors are already initialized in the cache
};


#endif /* LATTICE_H_ */
