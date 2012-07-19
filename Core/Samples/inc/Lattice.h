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
    ~Lattice();

    //! get basis vector a
    kvector_t getBasisVectorA() { return m_a1; }

    //! get basis vector b
    kvector_t getBasisVectorB() { return m_a2; }

    //! get basis vector c
    kvector_t getBasisVectorC() { return m_a3; }

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

    static Lattice createFCCLattice(double a);

    static Lattice createTrigonalLattice(double a, double c);

private:
    // This is a naive algorithm which will not work for skewed lattice bases (see Closest Vector Problem for more information)
    Coordinate3D<int> getNearestVectorCoordinates(const kvector_t &in, const kvector_t &a1,
            const kvector_t &a2, const kvector_t &a3) const;
    std::vector<kvector_t> getVectorsWithinRadius(const kvector_t &input_vector,
            double radius, const kvector_t &v1, const kvector_t &v2, const kvector_t &v3,
            const kvector_t &rec1, const kvector_t &rec2, const kvector_t &rec3) const;
    void computeReciprocalVectors() const;
    kvector_t m_a1, m_a2, m_a3; //!< Basis vectors in real space
    mutable kvector_t m_b1, m_b2, m_b3; //!< Cache of basis vectors in reciprocal space
    mutable bool m_cache_ok; //!< Boolean indicating if the reciprocal vectors are already initialized in the cache
};


#endif /* LATTICE_H_ */
