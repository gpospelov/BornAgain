#include "Lattice.h"

#include "gsl/gsl_matrix.h"
#include "gsl/gsl_vector.h"
#include "gsl/gsl_linalg.h"

Lattice::Lattice()
: m_cache_ok(false)
{
}

Lattice::Lattice(const kvector_t& a1, const kvector_t& a2, const kvector_t& a3)
: m_a1(a1)
, m_a2(a2)
, m_a3(a3)
, m_cache_ok(false)
{
}

Lattice::~Lattice()
{
}

double Lattice::getVolume() const
{
    return std::abs(DotProduct(m_a1, CrossProduct(m_a2, m_a3)));
}

void Lattice::getReciprocalLatticeBasis(kvector_t& b1, kvector_t& b2,
        kvector_t& b3) const
{
    if (!m_cache_ok) {
        computeReciprocalVectors();
    }
    b1 = m_b1;
    b2 = m_b2;
    b3 = m_b3;
    return;
}

std::vector<kvector_t> Lattice::getLatticeVectorsWithinRadius(
        const kvector_t& input_vector, double radius) const
{
    computeReciprocalVectors();
    return getVectorsWithinRadius(input_vector, radius, m_a1, m_a2, m_a3, m_b1, m_b2, m_b3);
}

std::vector<kvector_t> Lattice::getReciprocalLatticeVectorsWithinRadius(
        const kvector_t& input_vector, double radius) const
{
    computeReciprocalVectors();
    return getVectorsWithinRadius(input_vector, radius, m_b1, m_b2, m_b3, m_a1, m_a2, m_a3);

}

Lattice Lattice::createFCCLattice(double a)
{
    double b = a/2.0;
    kvector_t a1(0.0, b, b);
    kvector_t a2(b, 0.0, b);
    kvector_t a3(b, b, 0.0);
    return Lattice(a1, a2, a3);
}

Lattice Lattice::createTrigonalLattice(double a, double c)
{
    kvector_t a1(a, 0.0, 0.0);
    kvector_t a2(-a/2.0, std::sqrt(3.0)*a/2.0, 0);
    kvector_t a3(0.0, 0.0, c);
    return Lattice(a1, a2, a3);
}

void Lattice::computeReciprocalVectors() const
{
    kvector_t a23 = CrossProduct(m_a2, m_a3);
    kvector_t a31 = CrossProduct(m_a3, m_a1);
    kvector_t a12 = CrossProduct(m_a1, m_a2);
    m_b1 = 2*M_PI/DotProduct(m_a1, a23)*a23;
    m_b2 = 2*M_PI/DotProduct(m_a2, a31)*a31;
    m_b3 = 2*M_PI/DotProduct(m_a3, a12)*a12;
    m_cache_ok = true;
}

Coordinate3D<int> Lattice::getNearestLatticeVectorCoordinates(const kvector_t &vector_in) const
{
    return getNearestVectorCoordinates(vector_in, m_a1, m_a2, m_a3);
}

Coordinate3D<int> Lattice::getNearestReciprocalLatticeVectorCoordinates(const kvector_t &vector_in) const
{
    return getNearestVectorCoordinates(vector_in, m_b1, m_b2, m_b3);
}

Coordinate3D<int> Lattice::getNearestVectorCoordinates(const kvector_t &in, const kvector_t &a1,
        const kvector_t &a2, const kvector_t &a3) const
{
    gsl_matrix* p_basisMatrix = gsl_matrix_alloc(3, 3);

    gsl_matrix_set(p_basisMatrix, 0, 0, a1.x());
    gsl_matrix_set(p_basisMatrix, 0, 1, a2.x());
    gsl_matrix_set(p_basisMatrix, 0, 2, a3.x());

    gsl_matrix_set(p_basisMatrix, 1, 0, a1.y());
    gsl_matrix_set(p_basisMatrix, 1, 1, a2.y());
    gsl_matrix_set(p_basisMatrix, 1, 2, a3.y());

    gsl_matrix_set(p_basisMatrix, 2, 0, a1.z());
    gsl_matrix_set(p_basisMatrix, 2, 1, a2.z());
    gsl_matrix_set(p_basisMatrix, 2, 2, a3.z());

    gsl_vector* p_pointVector = gsl_vector_alloc(3);

    gsl_vector_set(p_pointVector, 0, in.x());
    gsl_vector_set(p_pointVector, 1, in.y());
    gsl_vector_set(p_pointVector, 2, in.z());

    gsl_vector* p_coordinates = gsl_vector_alloc(3);
    int s;
    gsl_permutation* p_perm = gsl_permutation_alloc (3);
    gsl_linalg_LU_decomp (p_basisMatrix, p_perm, &s);
    gsl_linalg_LU_solve (p_basisMatrix, p_perm, p_pointVector, p_coordinates);

    int c1 = (int)std::floor(gsl_vector_get(p_coordinates, 0) + 0.5);
    int c2 = (int)std::floor(gsl_vector_get(p_coordinates, 1) + 0.5);
    int c3 = (int)std::floor(gsl_vector_get(p_coordinates, 2) + 0.5);

    gsl_permutation_free(p_perm);
    gsl_vector_free(p_pointVector);
    gsl_vector_free(p_coordinates);
    gsl_matrix_free(p_basisMatrix);

    return Coordinate3D<int>(c1, c2, c3);
}

std::vector<kvector_t> Lattice::getVectorsWithinRadius(
        const kvector_t& input_vector, double radius, const kvector_t& v1,
        const kvector_t& v2, const kvector_t& v3, const kvector_t& rec1,
        const kvector_t& rec2, const kvector_t& rec3) const
{
    int max_X = (int)std::floor( rec1.mag()*radius/(2*M_PI) );
    int max_Y = (int)std::floor( rec2.mag()*radius/(2*M_PI) );
    int max_Z = (int)std::floor( rec3.mag()*radius/(2*M_PI) );

    Coordinate3D<int> nearestPointCoordinates = getNearestVectorCoordinates(input_vector, v1, v2, v3);
    std::vector<kvector_t> result;
    for (int index_X = -max_X; index_X <= max_X; ++index_X)
    {
        for (int index_Y = -max_Y; index_Y <= max_Y; ++index_Y)
        {
            for (int index_Z = -max_Z; index_Z <= max_Z; ++index_Z)
            {
                Coordinate3D<int> coords(index_X + nearestPointCoordinates[0],
                        index_Y + nearestPointCoordinates[1], index_Z + nearestPointCoordinates[2]);
                kvector_t latticePoint = coords[0]*v1 + coords[1]*v2 + coords[2]*v3;
                if ((latticePoint - input_vector).mag() <= radius)
                {
                    result.push_back(latticePoint);
                }
            }
        }
    }
    return result;
}

