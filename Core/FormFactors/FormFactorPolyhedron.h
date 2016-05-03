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

    kvector_t E() const { return m_E; }
    kvector_t R() const { return m_R; }
    complex_t qE( cvector_t q ) const { return m_E.dot(q); }
    complex_t qR( cvector_t q ) const { return m_R.dot(q); }

    complex_t contrib(int m, cvector_t prevec, cvector_t qpa) const;

private:
    kvector_t m_E; //!< vector pointing from mid of edge to upper vertex
    kvector_t m_R; //!< position vector of edge midpoint
};


//! A polygon, for form factor computation.

class PolyhedralFace {
public:
    static double diameter( const std::vector<kvector_t>& V );
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits( double _qpa, int _n );
#endif

    PolyhedralFace( const std::vector<kvector_t>& _V=std::vector<kvector_t>(), bool _sym_S2=false );

    double area() const { return m_area; }
    double pyramidalVolume() const { return m_rperp*m_area/3; }
    double radius3d() const { return m_radius_3d; }
    complex_t ff_n( int m, const cvector_t q ) const;
    complex_t ff( const cvector_t q, const bool sym_Ci ) const;
    complex_t ff_2D( const cvector_t qpa ) const;
    void assert_Ci( const PolyhedralFace& other ) const;

private:
    static double qpa_limit_series; //!< determines when use power series
    static int n_limit_series;

    bool sym_S2; //!< if true, then edges obtainable by inversion are not provided
    std::vector<PolyhedralEdge> edges;
    double m_area;
    kvector_t m_normal; //!< normal vector of this polygon's plane
    double m_rperp; //!< distance of this polygon's plane from the origin, along 'm_normal'
    double m_radius_2d; //!< radius of enclosing cylinder
    double m_radius_3d; //!< radius of enclosing sphere

    void decompose_q( const cvector_t q, complex_t& qperp, cvector_t& qpa ) const;
    complex_t ff_n_core( int m, const cvector_t qpa ) const;
};


//! A polyhedron, for form factor computation.

class FormFactorPolyhedron : public IFormFactorBorn {
public:
#ifdef POLYHEDRAL_DIAGNOSTIC
    static void setLimits( double _q, int _n );
#endif

    class TopologyFace {
    public:
        std::vector<int> vertexIndices;
        bool symmetry_S2;
    };
    typedef std::vector<TopologyFace> Topology;

    FormFactorPolyhedron() {}

    virtual complex_t evaluate_for_q(const cvector_t q ) const final;
    virtual double getVolume() const final { return m_volume; }
    virtual double getRadius() const final { return m_radius; }
    void assert_platonic() const;

protected:
    double m_z_origin;
    bool m_sym_Ci; //!< if true, then faces obtainable by inversion are not provided

    void setPolyhedron( const Topology& topology, double z_origin, bool sym_Ci,
                        const std::vector<kvector_t>& vertices );

private:
    static double q_limit_series; //!< determines when to use power series
    static int n_limit_series;

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
    virtual double getRadius() const final { return std::sqrt(m_base->area()); }

protected:
    std::unique_ptr<PolyhedralFace> m_base;
    double m_height;
};

#endif // FORMFACTORPOLYHEDRON_H
