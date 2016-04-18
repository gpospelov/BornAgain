// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPolyhedron.h
//! @brief     Defines class FormFactorPolyhedron, and auxiliary classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPOLYHEDRON_H
#define FORMFACTORPOLYHEDRON_H

#include<complex>
#include "BasicVector3D.h"
typedef std::complex<double> complex_t;
typedef Geometry::BasicVector3D<complex_t> cvector_t;
typedef Geometry::BasicVector3D<double> kvector_t;

#include "IFormFactorBorn.h"

//! One edge of a polygon, for form factor computation.

class PolyhedralEdge {
public:
    PolyhedralEdge( const kvector_t _Vlow, const kvector_t _Vhig );
    kvector_t E; //!< vector pointing from mid of edge to upper vertex
    kvector_t R; //!< position vector of edge midpoint
    complex_t contrib(int m, cvector_t prevec, cvector_t qpa) const;
};


//! A polygon, for form factor computation.

class PolyhedralFace {
public:
    PolyhedralFace( const std::vector<kvector_t>& _V=std::vector<kvector_t>(), bool _sym_S2=false );
    double radius_3d; //!< radius of enclosing sphere
    double getArea() const;
    double getPyramidalVolume() const;
    complex_t ff_n( int m, const cvector_t q ) const;
    complex_t ff( const cvector_t q, const bool sym_Ci ) const;
    complex_t ff_2D( const cvector_t qpa ) const;
    void assert_Ci( const PolyhedralFace& other ) const;
private:
    static const double qpa_limit_series; //!< determines when use power series
    bool sym_S2; //!< if true, then edges obtainable by inversion are not provided
    std::vector<PolyhedralEdge> edges;
    double area;
    kvector_t normal; //!< normal vector of this polygon's plane
    double rperp; //!< distance of this polygon's plane from the origin, along 'normal'
    double radius_2d; //!< radius of enclosing cylinder
    void decompose_q( const cvector_t q, complex_t& qperp, cvector_t& qpa ) const;
    complex_t ff_n_core( int m, const cvector_t qpa ) const;
};


//! A polyhedron, for form factor computation.

class FormFactorPolyhedron : public IFormFactorBorn {
public:
    FormFactorPolyhedron( const std::vector<PolyhedralFace>& _faces,
                          const double _z_origin, const bool _sym_Ci=false );
    virtual complex_t evaluate_for_q(const cvector_t q ) const final;
    double getVolume() const { return volume; }
    void assert_platonic() const;
private:
    double z_origin;
    bool sym_Ci; //!< if true, then faces obtainable by inversion are not provided
    double radius;
    double volume;
    static const double q_limit_series;
    std::vector<PolyhedralFace> faces;
    complex_t evaluate_centered( const cvector_t q ) const;
};


//! A prism with a polygonal base, for form factor computation.

class FormFactorPolygonalPrism : public IFormFactorBorn {
public:
    FormFactorPolygonalPrism( const PolyhedralFace& _base, const double _height );
    virtual complex_t evaluate_for_q(const cvector_t q ) const final;
    double getVolume() const;
    double getHeight() const;
protected:
    PolyhedralFace m_base;
    double m_height;
};


#ifdef POLYHEDRAL_DIAGNOSTIC
//! Information about the latest form factor evaluation. Not thread-safe.
//! Used only by external test program.
class Diagnosis {
public:
    int maxOrder;
    int nExpandedFaces;
    bool operator!=( const Diagnosis& other ) const {
        return maxOrder!=other.maxOrder || nExpandedFaces!=other.nExpandedFaces; }
    friend std::ostream& operator<< (std::ostream& stream, const Diagnosis& diag) {
        return stream<<" ["<<diag.nExpandedFaces<<":"<<diag.maxOrder<<"]";
    }
};
#endif

#endif // FORMFACTORPOLYHEDRON_H
