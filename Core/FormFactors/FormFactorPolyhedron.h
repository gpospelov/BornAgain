// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/src/FormFactorPolyhedron.h
//! @brief     Declares class FormFactorPolyhedron, FormFactorPrism, and auxiliary classes.
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
#include<memory>
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
    static double diameter( const std::vector<kvector_t>& V );
    PolyhedralFace( const std::vector<kvector_t>& _V=std::vector<kvector_t>(), bool _sym_S2=false );
    double m_radius_3d; //!< radius of enclosing sphere
    double getArea() const;
    double getPyramidalVolume() const;
    complex_t ff_n( int m, const cvector_t q ) const;
    complex_t ff( const cvector_t q, const bool sym_Ci ) const;
    complex_t ff_2D( const cvector_t qpa ) const;
    void assert_Ci( const PolyhedralFace& other ) const;
    static double qpa_limit_series; //!< determines when use power series
    static int n_limit_series;
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits( double _qpa, int _n ) { qpa_limit_series=_qpa; n_limit_series=_n; }
#endif

private:
    bool sym_S2; //!< if true, then edges obtainable by inversion are not provided
    std::vector<PolyhedralEdge> edges;
    double m_area;
    kvector_t m_normal; //!< normal vector of this polygon's plane
    double m_rperp; //!< distance of this polygon's plane from the origin, along 'm_normal'
    double m_radius_2d; //!< radius of enclosing cylinder
    void decompose_q( const cvector_t q, complex_t& qperp, cvector_t& qpa ) const;
    complex_t ff_n_core( int m, const cvector_t qpa ) const;
};


//! A polyhedron, for form factor computation.

class FormFactorPolyhedron : public IFormFactorBorn {
public:
    class TopologyFace {
    public:
        std::vector<int> vertexIndices;
        bool symmetry_S2;
    };
    typedef std::vector<TopologyFace> Topology;
    virtual const Topology& getTopology() const = 0;
    FormFactorPolyhedron() {}
    virtual complex_t evaluate_for_q(const cvector_t q ) const final;
    virtual double getVolume() const final { return m_volume; }
    virtual double getRadius() const final { return m_radius; }
    void assert_platonic() const;
    static double q_limit_series; //!< determines when to use power series
    static int n_limit_series;
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits( double _q, int _n ) { q_limit_series=_q; n_limit_series=_n; }
#endif

protected:
    double m_z_origin;
    bool m_sym_Ci; //!< if true, then faces obtainable by inversion are not provided
    void setVertices( const std::vector<kvector_t>& vertices );
    void precompute();

private:
    std::vector<PolyhedralFace> m_faces;
    double m_radius;
    double m_volume;
    complex_t evaluate_centered( const cvector_t q ) const;
};


//! A prism with a polygonal base, for form factor computation.

class FormFactorPolygonalPrism : public IFormFactorBorn {
public:
    FormFactorPolygonalPrism( const double height );
    virtual complex_t evaluate_for_q(const cvector_t q ) const final;
    double getVolume() const;
    double getHeight() const { return m_height; }
    virtual double getRadius() const final { return std::sqrt(m_base->getArea()); }
protected:
    std::unique_ptr<PolyhedralFace> m_base;
    double m_height;
};

#endif // FORMFACTORPOLYHEDRON_H
